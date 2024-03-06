#pragma once
#include "main.h"
#include "PlayerSkill.h"

extern int MMVER;

// string functions

std::string stringToLower(const std::string& source);

std::vector<std::string> stringSplit(const std::string& text, const std::string& delimiter, bool ignoreCase = true);
std::vector<std::string> stringSplit(const std::string& text, char delimiter, bool ignoreCase = true);

wxString stringRep(const wxString& str, int n = 1);

wxString getTimeStr();

template<typename T>
wxString my_to_string(const T& t)
{
	return wxString().operator<<(t); // sorry for clever code, couldn't help myself!
	// we are calling operator<< (which inserts argument into string) on temporary string,
	// taking advantage that it returns modified string (intended to allow chaining,
	// like str << "x" << "y" << 5)
}

/// <summary>
/// Concatenates the elements of a container into a single string using the specified separator.
/// </summary>
/// <typeparam name="Container">The type of the container.</typeparam>
/// <typeparam name="String">The type of the elements in the container.</typeparam>
/// <typeparam name="Extra">Additional template parameters for the container.</typeparam>
/// <param name="container">The container of strings to concatenate.</param>
/// <param name="separator">The separator to use between concatenated strings (default is "\n").</param>
/// <returns>The concatenated string.</returns>
template<template<typename, typename, typename...> typename Container, typename String, typename... Extra>
String stringConcat(const Container<String, Extra...>& container, const std::string& separator = "\n")
{
	String s = "";
	const int size = container.size();
	int i = 0;
	for (const auto& val : container)
	{
		s += val;
		if (i++ < size - 1)
		{
			s += separator;
		}
	}
	return s;
}

/// <summary>
/// Converts the elements of the given container to a string and concatenates them using the specified separator.
/// </summary>
/// <typeparam name="Container">The type of the container template.</typeparam>
/// <typeparam name="ValType">The type of the elements in the container.</typeparam>
/// <typeparam name="Extra">Additional template parameters for the container.</typeparam>
/// <param name="container">The container whose elements are to be converted and concatenated.</param>
/// <param name="separator">The separator used to concatenate the elements (default is "\n").</param>
/// <returns>A string containing the converted and concatenated elements of the container.</returns>
template<template<typename, typename, typename...> typename Container, typename ValType, typename... Extra>
std::string convertAndConcat(const Container<ValType, Extra...>& container, const std::string& separator = "\n")
{
	std::string s = "";
	const int size = container.size();
	int i = 0;
	for (const auto& val : container)
	{
		s += std::format("{}", val);
		if (i++ < size - 1)
		{
			s += separator;
		}
	}
	return s;
}

using StringReplaceFuncType = std::function<std::string(const std::smatch&)>;

// replaces all occurences of plain string or regex pattern in provided string
std::string stringReplace(const std::string& str, const std::string& replaceWhat, const std::string& replacement, bool plain = true);

// replaces all occurences of regex pattern, using value obtained from callback function as replacement
std::string stringReplace(const std::string& str, const std::string& replaceWhat, const StringReplaceFuncType& func);

template<size_t size>
std::string stringFromArray(const std::array<char, size>& arr)
{
	return std::string(arr.data(), size);
}

// wxWidgets functions

void redBlackGreenTextThreshold(wxWindow* win, int value, int threshold);

// json functions

// if argument is "null", converts it to empty object
void jsonEnsureIsObject(Json& json);
void jsonEnsureIsArray(Json& json);

// misc functions

template<typename T>
int indexInVector(const std::vector<T>& vec, const T& val)
{
	for (size_t i = 0; i < vec.size(); ++i)
	{
		if (vec[i] == val)
		{
			return i;
		}
	}
	return -1;
}

// HACK: I created this explicit specialization to deal with the case where T is int64_t, because otherwise the above function would be ambiguous (this happens for example when searching for integer value in all valid skill ids, because they're int64_t as of now)
// could have changed all function signatures to accept int64_t instead of int, or convert inside function and use the converted value, but it's much more effort and pollutes the code
// so, this handles that exact case and I don't need to do anything else
int indexInVector(const std::vector<int64_t>& vec, const int& val);

template<typename T>
bool existsInVector(const std::vector<T>& vec, const T& val)
{
	return indexInVector(vec, val) != -1;
}

// HACK: see above indexInVector specialization for more details
bool existsInVector(const std::vector<int64_t>& vec, const int& val);

template<typename Container, typename Val>
	requires std::random_access_iterator<typename Container::iterator> // index usually makes sense only in random access containers
int indexInContainer(const Container& container, const Val& val)
{
	int i = 0;
	for (const auto& v : container)
	{
		if (v == val)
		{
			return i;
		}
	}
	return -1;
}

template<typename Container, typename Val>
	requires std::random_access_iterator<typename Container::iterator> // index usually makes sense only in random access containers
bool existsInContainer(const Container& container, const Val& val)
{
	return indexInContainer(container, val) != -1;
}

// returns a new vector with the sorted elements of the original vector
template<typename Container>
Container sorted(const Container& c, std::function<bool(typename Container::value_type, typename Container::value_type)> comp = std::less<typename Container::value_type>())
{
	Container out = c;
	std::sort(out.begin(), out.end(), comp);
	return out;
}

template<typename Vector>
Vector mergeVectors(std::initializer_list<Vector> list)
{
	size_t n = 0;
	for (auto& vec : list)
	{
		n += vec.size();
	}
	Vector out;
	out.reserve(n);
	for (auto& vec : list)
	{
		out.insert(out.end(), vec.begin(), vec.end());
	}
	return out;
}

template<template<typename, typename, typename...> typename Map, typename Key, typename Value, typename... Extra>
Map<Value, Key> invertMap(const Map<Key, Value, Extra...>& map)
{
	Map<Value, Key> outMap;
	for (const auto& [key, value] : map)
	{
		outMap[value] = key;
	}
	return outMap;
}

template<typename T>
T&& mmv(T&& e6, T&& e7, T&& e8)
{
	if (MMVER == 6)
	{
		return std::forward<T>(e6);
	}
	else if (MMVER == 7)
	{
		return std::forward<T>(e7);
	}
	else if (MMVER == 8)
	{
		return std::forward<T>(e8);
	}
	else
	{
		throw std::runtime_error(std::format("Invalid MM version ({})!", MMVER));
	}
}

template<typename Vector>
constexpr Vector compileTimeMergeVectors(std::initializer_list<Vector> list)
{
	Vector out;
	for (auto& vec : list)
	{
		out.insert(out.end(), vec.begin(), vec.end());
	}
	return out;
}

struct InventoryPosition
{
	int x, y;
	inline bool isInvalid() const
	{
		return x == -1 || y == -1;
	}
	inline bool isValid() const
	{
		return !isInvalid();
	}
	static inline InventoryPosition invalid()
	{
		return { -1, -1 };
	}
};

struct BaseBonus
{
	int base, bonus;
};

struct ItemInInventoryData
{
	InventoryPosition pos;
	int itemsArrayIndex;

	ItemInInventoryData(InventoryPosition pos, int itemsArrayIndex)
		: pos(pos), itemsArrayIndex(itemsArrayIndex)
	{
	}
};

struct ItemInInventoryDataWithItem
{
	InventoryPosition pos;
	int itemsArrayIndex;
	mm7::Item item;

	ItemInInventoryDataWithItem(InventoryPosition pos, int itemsArrayIndex, const mm7::Item& item)
		: pos(pos), itemsArrayIndex(itemsArrayIndex), item(item)
	{
	}
};

struct Bounds
{
	int64_t low, high;
};

Bounds getBounds(int size);

template<int size>
const Bounds boundsBySize = getBounds(size);

template<typename T>
const Bounds boundsByType{ 1000, 0 }; // error at runtime, "= delete" doesn't work
template<>
const Bounds boundsByType<uint8_t> = { 0, 255 };
template<>
const Bounds boundsByType<int8_t> = { -128, 127 };
template<>
const Bounds boundsByType<uint16_t> = { 0, 65535 };
template<>
const Bounds boundsByType<int16_t> = { -32768, 32767 };
template<>
const Bounds boundsByType<uint32_t> = { 0, 4294967295 };
template<>
const Bounds boundsByType<int32_t> = { -2147483648, 2147483647 };

// TODO causes runtime errors - boundsByType<int8_t> is {0, 0}
/*
template<>
const Bounds boundsByType<uint8_t> = boundsBySize<1>;
template<>
const Bounds boundsByType<int8_t> = boundsBySize<-1>;
template<>
const Bounds boundsByType<uint16_t> = boundsBySize<2>;
template<>
const Bounds boundsByType<int16_t> = boundsBySize<-2>;
template<>
const Bounds boundsByType<uint32_t> = boundsBySize<4>;
template<>
const Bounds boundsByType<int32_t> = boundsBySize<-4>;*/

template<typename T>
bool boundsCheck(T&& value, int64_t low, int64_t high, bool clamp = true)
{
	if (low > high)
	{
		wxLogError("Invalid bounds [%lld, %lld]", low, high);
		wxLog::FlushActive();
		return false;
	}
	bool error = value < low || value > high;
	if (error)
	{
		wxLogError("Value %s out of bounds [%lld, %lld]", std::to_string(value), low, high);
		wxLog::FlushActive();
	}
	if (clamp)
	{
		/*
			wxASSERT_MSG(
				low >= std::numeric_limits<std::remove_reference_t<T>>::min() &&
				high <= std::numeric_limits<std::remove_reference_t<T>>::max()
				, wxString::Format("Clamp bounds [%lld, %lld] too wide for value of type %s", low, high, typeid(std::decay_t<T>).name())
			);
		*/

		// remove reference is required because otherwise numeric_limits can't bind to rvalue reference
		low = std::max(low, (int64_t)std::numeric_limits<std::remove_reference_t<T>>::min());
		high = std::min(high, (int64_t)std::numeric_limits<std::remove_reference_t<T>>::max());
		value = std::clamp(value, (T)low, (T)high);
	}
	return !error;
}

template<typename T>
bool boundsCheck(T&& value, const Bounds& b, bool clamp = true)
{
	return boundsCheck(std::forward<T>(value), b.low, b.high, clamp);
}

template<typename T>
bool boundsCheck(T&& value, int size, bool clamp = true)
{
	auto [low, high] = getBounds(size);
	// yay, my first real usecase for std::forward! code breaks without it
	return boundsCheck(std::forward<T>(value), low, high, clamp);
}

// show deduced type (compile-time error)
template <typename T>
struct deduced_type;

template<typename T>
void showDeducedType(T&&)
{

	deduced_type<T>::show;
}

template<typename T>
void showDeducedType(const T&&)
{

	deduced_type<T>::show;
}

// don't know the exact terminology, but it needs to be "potentially-evaluated" if invalid constexpr if branch is entered, so can't be function
// static_assert(false) always fails
// TODO: support custom message
#define COMPILE_TIME_CONSTEXPR_IF_ERROR() ((void(*)())0x5)("a")

// to avoid ambiguity with std::to_string
std::string to_string(const std::string& str);

// allows to use std::format with std::pair
// TODO: support more types
namespace std
{
	template<typename T, typename U>
	struct formatter<std::pair<T, U>>
	{
		template<typename ParseContext>
		constexpr auto parse(ParseContext& ctx)
		{
			return ctx.begin();
		}

		template<typename FormatContext>
		auto format(const std::pair<T, U>& pair, FormatContext& ctx) const
		{
			return format_to(ctx.out(), "({}, {})", pair.first, pair.second);
		}
	};
}

template<typename T, typename U>
std::string to_string(const std::pair<T, U>& pair)
{
	// using std::to_string; // ADL
	return std::format("{}", pair);
}

// TODO: support associative containers
template<template<typename, typename, typename...> typename Container, typename T, typename... Extra>
std::string containerToString(const Container<T, Extra...>& container, const std::string& separator = ", ")
{
	std::string s = "";
	const int size = container.size();
	int i = 0;
	for (const auto& val : container)
	{
		//using std::to_string; // ADL
		s += std::format("{}", val);
		if (i++ < size - 1)
		{
			s += separator;
		}
	}
	return "{ " + s + " }";
}

template<typename T, size_t S>
std::string containerToString(const std::array<T, S>& container, const std::string& separator = ", ")
{
	return containerToString(std::vector<T>(container.begin(), container.end()), separator);
}

// put all functions into relevant namespaces
namespace util
{
	namespace string
	{
		static constexpr auto toLower = stringToLower;
		static constexpr auto rep = stringRep;
		template<size_t size>
		static constexpr auto fromArray = stringFromArray<size>;
		// not using single parameter pack here to show template argument readable names in IDE

		// DOESN'T DO TYPE DEDUCTION!
// 		template<template<typename, typename, typename...> typename Container, typename String, typename... Extra>
// 		static constexpr auto concat = stringConcat<Container, String, Extra...>;
// 		template<template<typename, typename, typename...> typename Container, typename ValType, typename... Extra>
// 		static constexpr auto convertAndConcat = &convertAndConcat<Container, ValType, Extra...>;
		using ::stringConcat;
		using ::convertAndConcat;
		static constexpr std::vector<std::string>(*split)(const std::string& text, const std::string& delimiter, bool ignoreCase) = stringSplit;
		static constexpr std::vector<std::string>(*splitChar)(const std::string& text, char delimiter, bool ignoreCase) = stringSplit;
		using ::containerToString;
	}

	namespace wx
	{
		static constexpr auto redBlackGreenTextThreshold = ::redBlackGreenTextThreshold;
	}

	namespace json
	{
		static constexpr auto ensureIsObject = jsonEnsureIsObject;
		static constexpr auto ensureIsArray = jsonEnsureIsArray;
	}

	namespace container
	{
		using ::mergeVectors;
// 		template<template<typename, typename, typename...> typename Map, typename Key, typename Value, typename... Extra>
// 		static constexpr auto invertMap = ::invertMap<Map, Key, Value, Extra...>;
		using ::invertMap;
// 		template<typename T>
// 		static constexpr auto existsInVector = ::existsInVector<T>
		using ::existsInVector;
// 		template<typename T>
// 		static constexpr auto indexInVector = ::indexInVector<T>;
		using ::indexInVector;
// 		template<typename Container, typename Val>
// 		static constexpr auto existsInContainer = ::existsInContainer<Container, Val>;
		using ::existsInContainer;
		//template<typename Container, typename Val>
		//static constexpr auto indexInContainer = ::indexInContainer<Container, Val>;
		using ::indexInContainer;
		//template<typename Vector>
		//static constexpr auto compileTimeMergeVectors = ::compileTimeMergeVectors<Vector>;
		using ::compileTimeMergeVectors;
		// 		template<typename T, size_t S>
		// 		static constexpr std::string(*toString)(const std::array<T, S>& container, const std::string& separator) = ::containerToString<T, S>;
		// template<template<typename, typename, typename...> typename Container, typename T, typename... Extra>
		// 		static constexpr std::string(*toString)(const Container<T, Extra...>& container, const std::string& separator) = ::containerToString<Container, T, Extra...>;

				// "overload templated function pointers" (the above doesn't work)
// 		template<typename... Args>
// 		static constexpr auto toString = ::containerToString<Args...>;
		using ::containerToString;
		using ::sorted;

	}

	namespace guid
	{
		GUID create();
		std::string toString(const GUID& guid);
		std::string newGuidString();
	}

	namespace misc
	{
		template<typename T>
		static constexpr auto mmv = ::mmv<T>;
		static constexpr auto getTimeStr = ::getTimeStr;
		template<typename T>
		static constexpr auto boundsCheck = ::boundsCheck<T>;
		template<typename T>
		static constexpr auto showDeducedType = ::showDeducedType<T>;
		namespace
		{
			template<typename T>
			concept hasSize = requires(T t)
			{
				{ t.size() } -> std::convertible_to<size_t>;
			};
		}
		// works on containers without random access iterators
		template<typename R>
		auto getNthRangeElement(R&& range, size_t n)
		{
			wxASSERT_MSG(n >= 0, "Index out of range");
			if constexpr (hasSize<R>)
			{
				wxASSERT_MSG(n < range.size(), "Index out of range");
			}
			auto it = range.begin();
			std::advance(it, n);
			return *it;
		}
	}

	// TODO: change file Reflection.h to use new qualified name
	namespace rttr
	{
		namespace
		{
			namespace rttrOrig = ::rttr;
		}

		// returns a constructor, which might potentially be wrapped by another one, such as to return a shared_ptr to the object, and a bool, which is true if constructor was unwrapped
		std::pair<rttrOrig::constructor, bool> getMaybeWrappedConstructor(rttrOrig::constructor ctor);
	}
}
