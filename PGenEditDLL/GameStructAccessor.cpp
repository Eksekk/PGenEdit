#include "pch.h"
#include "GameStructAccessor.h"

GameStructAccessor* gameAccessor = nullptr;

GameStructAccessor::~GameStructAccessor() {}

#pragma warning(push)
#pragma warning(disable: 6001) // null pointer dereference

template<typename Game>
HWND TemplatedGameStructAccessor<Game>::getWindowHandle()
{
	return reinterpret_cast<HWND>(game->windowHandle);
}

#pragma warning(pop)

template class TemplatedGameStructAccessor<mm6::Game>;
template class TemplatedGameStructAccessor<mm7::Game>;
template class TemplatedGameStructAccessor<mm8::Game>;