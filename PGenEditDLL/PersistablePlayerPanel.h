#pragma once
#include "pch.h"
#include "main.h"

class PersistablePlayerPanel
{
    virtual bool persist(Json& json) = 0;
    virtual bool unpersist(Json& json) = 0;
};

