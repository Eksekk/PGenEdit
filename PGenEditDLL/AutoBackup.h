#pragma once
#include "main.h"

// automatically backups variables from constructor
// and restores them in destructor
template<typename... Args>
class AutoBackup
{
	std::tuple<Args&...> refs;
	std::tuple<Args...> vals; // lack of reference is important

public:
	AutoBackup(Args&... args);
	~AutoBackup();
};

template<typename... Args>
AutoBackup<Args...>::AutoBackup(Args&... args)
	: refs(std::tie(args...)),
	vals(Args(args)...)
{
	
}

template<typename... Args>
AutoBackup<Args...>::~AutoBackup()
{
	refs = std::move(vals);
}