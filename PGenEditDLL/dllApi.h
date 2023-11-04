#pragma once
#include "pch.h"
#include "main.h"

// will be used for using accessors after json data has been initialized, when it is being initialized, they don't exist yet
// could make dllApi.cpp directly call GameData function, but decided to do generic callbacks solution
extern std::vector<SimpleCallback> postInitCallbacks;
void addPostInitCallback(SimpleCallback callback);
extern bool initialized;