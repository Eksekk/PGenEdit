#pragma once
#include "pch.h"
#include "main.h"

// automatically backups variables from constructor
// and restores them in destructor
template<typename... Args>
class AutoBackup
{
	std::tuple<std::reference_wrapper<Args>...> refs;
	std::tuple<Args&&...> vals; // rvalue reference is important

public:
	AutoBackup(Args&... args);
	~AutoBackup();
};

template<typename... Args>
AutoBackup<Args...>::AutoBackup(Args&... args)
	: refs(std::reference_wrapper<Args>(args)...),
	vals(Args(args)...)
{
	
}

template<typename... Args>
AutoBackup<Args...>::~AutoBackup()
{
	refs = vals;
}