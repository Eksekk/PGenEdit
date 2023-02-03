#include "pch.h"
#include "GeneratorGuiBase.h"

Json GeneratorGuiBase::writeToJsonR() const
{
	Json j;
	writeToJson(j);
	return j;
}

void GeneratorGuiBase::copyFrom(const GeneratorGuiBase& source)
{
	Json j;
	source.writeToJson(j);
	readFromJson(j);
}

GeneratorGuiBase::~GeneratorGuiBase()
{

}
