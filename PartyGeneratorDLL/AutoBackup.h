#pragma once
#include "pch.h"
#include "main.h"

// automatically backups variables from constructor
// and restores them in destructor
template<typename... Args>
class AutoBackup
{
	std::tuple<std::decay_t<std::reference_wrapper<Args>>...> refs;
	std::tuple<std::decay_t<Args>...> vals;

public:
	AutoBackup(Args&&... args);
	~AutoBackup();
};

template<typename... Args>
AutoBackup<Args...>::AutoBackup(Args&&... args)
	: refs(std::reference_wrapper<std::decay_t<Args>>(args)...),
	vals(static_cast<std::remove_reference_t<Args>>(args)...)
{
	
}

template<typename... Args>
AutoBackup<Args...>::~AutoBackup()
{
	refs = std::move(vals);
}