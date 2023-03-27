#include "pch.h"
#include "main.h"
#include "GeneratorDataBase.h"

void GeneratorDataBase::randomize()
{
}

Json GeneratorDataBase::writeToJsonR()
{
    Json j;
    writeToJson(j);
    return j;
}

GeneratorDataBase::GeneratorDataBase(const GeneratorDataBase& other)
{
    // assert(false); // shouldn't be ever called - use subclass copy ctor
}

GeneratorDataBase::~GeneratorDataBase() {}