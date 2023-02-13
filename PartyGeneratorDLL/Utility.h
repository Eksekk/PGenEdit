#pragma once
#include "pch.h"
#include "main.h"
#include <vector>
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

// TODO: replace with initializer_list
template<typename Vector>
Vector mergeVectors(const Vector& first, const Vector& second)
{
	size_t n = first.size();
	auto out = first;
	out.resize(n + second.size());
	for (int i = 0; i < second.size(); ++i)
	{
		out[n + i] = second[i];
	}
	return out;
}

template<typename Vector, typename... Vectors>
Vector mergeVectors(const Vector& first, const Vector& second, const Vectors&... vectors)
{
	return mergeVectors(mergeVectors(first, second), vectors...);
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

struct Bounds
{
	int64_t low, high;
};

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
	}
	default:
	{
		wxLogError("Unknown size (%d) in getBounds()\n%s", size);
		wxLog::FlushActive();
		return Bounds{ 0, 0 };
	}

	}
	return Bounds{ low, high };
}

template<typename T>
bool boundsCheck(T&& value, int64_t low, int64_t high, bool clamp = true)
{
	bool error = value < low || value > high;
	if (error)
	{
		wxLogError("Value %d out of bounds [%d, %d]", value, low, high);
		wxLog::FlushActive();
	}
	if (clamp)
	{
		/*
				wxASSERT_MSG(
					// remove reference is required because otherwise numeric_limits can't bind to rvalue reference
					low >= std::numeric_limits<std::remove_reference_t<T>>::min() &&
					high <= std::numeric_limits<std::remove_reference_t<T>>::max()
					, wxString::Format("Clamp bounds [%lld, %lld] too wide for value of type %s", low, high, typeid(std::decay_t<T>).name())
				);
		*/
		low = std::max(low, (int64_t)std::numeric_limits<std::remove_reference_t<T>>::min());
		high = std::min(high, (int64_t)std::numeric_limits<std::remove_reference_t<T>>::max());
		value = std::clamp(value, (T)low, (T)high);
	}
	return !error;
}

template<typename T>
bool boundsCheck(T&& value, int size, bool clamp = true)
{
	auto [low, high] = getBounds(size);
	return boundsCheck(value, low, high, clamp)
}

template<typename T>
using checkBounds = boundsCheck<T>;