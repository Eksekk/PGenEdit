#pragma once
#include "pch.h"
#include "main.h"
#include "PlayerSkill.h"
extern int MMVER;

template<typename T>
bool existsInVector(const std::vector<T>& vec, const T& val)
{
	for (int i = 0; i < vec.size(); ++i)
	{
		if (vec[i] == val)
		{
			return true;
		}
	}
	return false;
}

template<typename T>
int indexInVector(const std::vector<T>& vec, const T& val)
{
	for (int i = 0; i < vec.size(); ++i)
	{
		if (vec[i] == val)
		{
			return i;
		}
	}
	return -1;
}

template<typename T>
const T& mmv(const T& e6, const T& e7, const T& e8)
{
	if (MMVER == 6)
	{
		return e6;
	}
	else if (MMVER == 7)
	{
		return e7;
	}
	else if (MMVER == 8)
	{
		return e8;
	}
	else
	{
		throw std::runtime_error(std::format("Invalid MM version ({})!", MMVER));
	}
}

template<template<typename, typename...> typename Container, typename... Extra>
wxString concatWxStrings(const Container<wxString, Extra...>& container, const wxString& separator = "\n")
{
	wxString s;
	const size_t size = container.size();
	int i = 0;
	for (const auto& val : container)
	{
		s << val;
		if (i++ < size - 1)
		{
			s << separator;
		}
	}
	return s;
}

std::string tolowerStr(const std::string& source);

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
	for (auto& vec: list)
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

wxString getTimeStr();

struct BaseBonus
{
	int base, bonus;
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
void showDeducedType(T&&) {

	deduced_type<T>::show;
}

wxString rep(const wxString& str, int n = 1);

template<typename T>
wxString my_to_string(const T& t)
{
	return wxString().operator<<(t); // sorry for clever code, couldn't help myself!
	// we are calling operator<< (which inserts argument into string) on temporary string,
	// taking advantage that it returns modified string (intended to allow chaining,
	// like str << "x" << "y" << 5)
}

class Profiler
{
	std::chrono::time_point<std::chrono::steady_clock> profilingStart;
	std::chrono::time_point<std::chrono::steady_clock> profilingEnd;
	std::string action;

	std::chrono::time_point<std::chrono::steady_clock> aggregateStart;
	std::chrono::time_point<std::chrono::steady_clock> aggregateEnd;
	std::chrono::nanoseconds aggregateTime;
	std::chrono::nanoseconds aggregateMaxDuration;
	int aggregateMaxDurationIndex;
	std::string aggregateAction;
	int aggregateCount;
public:
	bool profilingNow;
	void start(const std::string& action);
	void end();
	wxString getDurationStr();
	void startAggregate(const std::string& action);
	void endAggregate();
	void startAggregatePart();
	void endAggregatePart();
	wxString getAggregateDurationStr();

	Profiler();
};

void redBlackGreenTextThreshold(wxWindow* win, int value, int threshold);