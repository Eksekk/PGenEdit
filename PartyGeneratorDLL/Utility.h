#pragma once
#include "pch.h"
#include "main.h"
#include <vector>

template<typename T>
bool existsInVector(const std::vector<T>& vec, const T& val);

template<typename T>
const T& mmv(const T& e6, const T& e7, const T& e8);

template<typename T>
T& mmv(T& e6, T& e7, T& e8);

template<template<typename, typename...> typename Container, typename... Extra>
wxString concatWxStrings(const Container<wxString, Extra...>& container, const wxString& separator = "\n");

std::string tolowerStr(const std::string& source);

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