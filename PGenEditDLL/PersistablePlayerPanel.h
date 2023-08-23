#pragma once
#include "pch.h"
#include "main.h"

class PersistablePlayerPanel
{
public:
    virtual bool persist(Json& json) = 0;
    virtual bool unpersist(const Json& json) = 0;
};

