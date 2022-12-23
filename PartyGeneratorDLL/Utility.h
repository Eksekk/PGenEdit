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