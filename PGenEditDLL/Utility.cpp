#include "pch.h"
#include "main.h"
#include "Utility.h"
#include "Asserter.h"

// string functions

namespace
{
	namespace rttrOrig = ::rttr;
}

std::string stringToLower(const std::string& source)
{
	std::string out = source;
	for (char& c : out)
	{
		c = std::tolower(c);
	}
	return out;
}

std::string stringToUpper(const std::string& source)
{
	std::string out = source;
	for (char& c : out)
	{
		c = std::toupper(c);
	}
	return out;
}

std::vector<std::string> stringSplit(const std::string& text, const std::string& delimiter, bool ignoreCase)
{
	std::string useText = ignoreCase ? stringToLower(text) : text;
	std::string useDelimiter = ignoreCase ? stringToLower(delimiter) : delimiter;
	std::vector<std::string> strings;
	size_t pos = 0, foundPos;
	while ((foundPos = useText.find(useDelimiter, pos)) != std::string::npos)
	{
		strings.push_back(text.substr(pos, foundPos - pos));
		pos = foundPos + useDelimiter.size();
	}
	strings.push_back(text.substr(pos));
	return strings;
}

std::vector<std::string> stringSplit(const std::string& text, char delimiter, bool ignoreCase)
{
	std::string s;
	s.push_back(delimiter);
	return stringSplit(text, s, ignoreCase);
}

std::vector<std::string> stringSplitRegex(const std::string& text, const std::string& regex, bool ignoreCase)
{
	std::vector<std::string> strings;
	std::regex rgx = ignoreCase ? std::regex(regex, std::regex_constants::icase) : std::regex(regex);
	std::sregex_token_iterator iter(text.begin(), text.end(), rgx, -1);
	std::sregex_token_iterator end;
	auto originalIter = text.begin();
	for (; iter != end; ++iter)
	{
		strings.push_back(*iter);
		originalIter = iter->second;
	}

	// Add the remaining part of the text if any
	if (originalIter != text.end())
	{
		strings.push_back(std::string(originalIter, text.end()));
	}

	return strings;
}

std::string stringRep(const std::string& str, int n)
{
	if (n < 0)
	{
		wxLogError(__FUNCTION__ ": n must be >= 0, got %d", n);
		return str;
	}
	else if (n == 0)
	{
		return "";
	}
	std::string ret = "";
	ret.reserve(str.size() * n);
	for (int i = 0; i < n; ++i)
	{
		ret.append(str);
	}
	return ret;
}

wxString getTimeStr()
{
	auto endTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	return wxString(std::ctime(&endTime));
}

// json functions
void jsonEnsureIsObject(Json& json)
{
	json = !json.is_object() ? Json::object() : json;
}

void jsonEnsureIsArray(Json& json)
{
	json = !json.is_array() ? Json::array() : json;
}

int indexInVector(const std::vector<int64_t>& vec, const int& val)
{
	return indexInVector<int64_t>(vec, (int64_t)val);
}

bool existsInVector(const std::vector<int64_t>& vec, const int& val)
{
	return existsInVector<int64_t>(vec, (int64_t)val);
}

std::string stringReplace(const std::string& str, const std::string& replaceWhat, const std::string& replacement, bool plain /*= true*/)
{
	// TODO: support replacement backreferences if using regex (for example replaceWhat string = "abc$1,$2" and substitute value of referenced capture group)
	std::string newStr;
	if (plain)
	{
		// important: no int, or infinite loop happens?
		size_t pos = -1, afterEndOfLastMatch = 0;
		while ((pos = str.find(replaceWhat, pos + 1)) != std::string::npos)
		{
			int skipped = (int)pos - (int)afterEndOfLastMatch;
			if (skipped > 0)
			{
				newStr += str.substr(afterEndOfLastMatch, skipped);
			}
			newStr += replacement;
			pos += replaceWhat.size() - 1;
			afterEndOfLastMatch = pos + 1;
		}
		newStr += str.substr(afterEndOfLastMatch);
		return newStr;
	}
	else
	{
		// replace with regex, handling capture group substitution, that is $0, $1 etc.
		std::regex re(replaceWhat);
		return std::regex_replace(str, re, replacement);
	}
}

std::string stringReplace(const std::string& str, const std::string& replaceWhat, const StringReplaceFuncType& func)
{
	std::string newStr;
	std::regex regex(replaceWhat);
	std::sregex_iterator itr(str.begin(), str.end(), regex);
	std::sregex_iterator end;
	int afterEndOfLastMatch = 0;
	while (itr != end)
	{
		const std::smatch& match = *itr;
		if (match.position() > afterEndOfLastMatch)
		{
			newStr += str.substr(afterEndOfLastMatch, match.position() - afterEndOfLastMatch);
		}
		newStr += func(match);
		afterEndOfLastMatch = match.position() + match[0].str().size();
		++itr;
	}
	newStr += str.substr(afterEndOfLastMatch);
	return newStr;
}

// wxWidgets functions
// sets font color of passed window to red/black/green, depending on current value and threshold
void redBlackGreenTextThreshold(wxWindow* win, int value, int threshold)
{
	if (value < threshold)
	{
		win->SetOwnForegroundColour(*wxRED);
	}
	else if (value > threshold)
	{
		win->SetOwnForegroundColour(wxColour(0x00b02f)); // different color, because default green is too bright and hard to read
	}
	else
	{
		win->SetOwnForegroundColour(*wxBLACK);
	}
}

// misc functions
Bounds getBounds(int size)
{
	static const uint64_t
		u1_max = std::numeric_limits<uint8_t>::max(),
		u2_max = std::numeric_limits<uint16_t>::max(),
		u4_max = std::numeric_limits<uint32_t>::max();

	static const int64_t
		i1_min = std::numeric_limits<int8_t>::min(),
		i2_min = std::numeric_limits<int16_t>::min(),
		i4_min = std::numeric_limits<int32_t>::min(),
		i1_max = std::numeric_limits<int8_t>::max(),
		i2_max = std::numeric_limits<int16_t>::max(),
		i4_max = std::numeric_limits<int32_t>::max();

	int64_t low, high;

	bool uns = size > 0;
	switch (std::abs(size))
	{
	case 1:
	{
		low = uns ? 0 : i1_min;
		high = uns ? u1_max : i1_max;
		break;
	}
	case 2:
	{
		low = uns ? 0 : i2_min;
		high = uns ? u2_max : i2_max;
		break;
	}
	case 4:
	{
		low = uns ? 0 : i4_min;
		high = uns ? u4_max : i4_max;
		break;
	}
	case 8:
	{
		low = 0;
		high = u4_max;
		wxLogError("8-byte bounds are not implemented yet");
		wxLog::FlushActive();
		break;
	}
	default:
	{
		wxLogError("Unknown size (%d) in getBounds()", size);
		wxLog::FlushActive();
		return Bounds{ 0, 0 };
	}

	}
	return Bounds{ low, high };
}

std::string to_string(const std::string& str)
{
	return str;
}

template<typename... Types>
class variant_wrapper
{
	using VariantType = std::variant<Types...>;
	VariantType var;

public:
	// operator -> can be used to access members of the contained object
	VariantType* operator->()
	{
		return &var;
	}
	template<typename T>
	variant_wrapper(T&& t) : var(std::forward<T>(t)) {}

	template<typename T>
	bool is() const
	{
		return std::holds_alternative<T>(var);
	}

	template<typename T>
	T& get()
	{
		return std::get<T>(var);
	}

	template<typename T>
	const T& get() const
	{
		return std::get<T>(var);
	}
	template<typename T>
	T get_or(T&& t) const
	{
		return std::get_if<T>(&var) ? std::get<T>(var) : std::forward<T>(t);
	}

	template<typename T, std::enable_if_t<std::is_default_constructible_v<T>, bool> = true>
	T get_or() const
	{
		return std::get_if<T>(&var) ? std::get<T>(var) : T();
	}
};

std::pair<rttrOrig::constructor, bool> util::rttr::getMaybeWrappedConstructor(rttrOrig::constructor ctor)
{
	// PROBLEM: we might or might not be passed a "wrapper constructor", which returns a shared_ptr to the object
	// should work, constructor always returns instance of the class, so we can just check if it's the same as declaring type
	const bool isWrapper = ctor.get_instantiated_type() != ctor.get_declaring_type();
	if (isWrapper)
	{
		// unwrap
		std::vector<rttrOrig::type> types;
		for (auto&& param : ctor.get_parameter_infos())
		{
			types.push_back(param.get_type());
		}
		rttrOrig::type unwrapped = rttrOrig::type::get<void*>(); // dummy value
		rttrOrig::type inst = ctor.get_instantiated_type();
		if (inst.is_wrapper())
		{
			unwrapped = inst.get_wrapped_type().get_raw_type();
		}
		else if (inst.is_sequential_container())
		{
			__debugbreak(); // is this even possible?
			auto args = inst.get_template_arguments();
			wxASSERT_MSG(args.size() >= 1, std::format("Sequential container '{}' has {} template arguments, expected at least 1", inst, args.size()));
			unwrapped = util::misc::getNthRangeElement(args, 0);

		}
		else if (inst.is_associative_container())
		{
			__debugbreak(); // is this even possible?
			auto args = inst.get_template_arguments();
			// support key-only associative containers
			wxASSERT_MSG(args.size() >= 1, std::format("Associative container '{}' has {} template arguments, expected at least 1", inst, args.size()));
			if (args.size() == 1) // key-only
			{
				unwrapped = util::misc::getNthRangeElement(args, 0);
			}
			else // key-value
			{
				unwrapped = util::misc::getNthRangeElement(args, 1);
			}
		}
		else
		{
			__debugbreak(); // shouldn't happen?
			unwrapped = inst;
		}
		auto ctor2 = unwrapped.get_constructor(types);
		wxASSERT_MSG(ctor2.is_valid(), std::format("Couldn't find wrapped constructor of type '{}' with types: {}", ctor.get_instantiated_type(), types));
		return std::make_pair(ctor2, true);
	}
	else
	{
		return std::make_pair(ctor, false);
	}
}

GUID util::guid::create()
{
	GUID g;
	HRESULT ret = CoCreateGuid(&g);
	if (FAILED(ret))
	{
		char buffer[500];
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, HRESULT_CODE(ret), 0, buffer, 500, NULL);
		throw std::runtime_error("Failed to create GUID: " + std::string(buffer));
	}
	return g;
}

std::string util::guid::toString(const GUID& guid)
{
	char buffer[40];
	sprintf_s(buffer, 40, "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
	return std::string(buffer);
}

std::string util::guid::newGuidString()
{
	return toString(create());
}
