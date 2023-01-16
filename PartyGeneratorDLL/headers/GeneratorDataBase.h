#pragma once
#include "pch.h"
#include "main.h"
#include "Player.h"
class GeneratorDataBase
{
public:
    virtual bool readFromJson(const Json& json) = 0;
    virtual bool writeToJson(Json& json) = 0;
    virtual void setDefaults() = 0;
    virtual void randomize() = 0;
    virtual void copyFrom(const GeneratorDataBase& source) = 0;

    GeneratorDataBase() {};
    virtual ~GeneratorDataBase();
};