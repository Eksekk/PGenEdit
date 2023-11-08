#pragma once
#include "main.h"
#include "Player.h"
class GeneratorGuiBase
{
public:
	virtual bool readFromJson(const Json& json) = 0;
	virtual bool writeToJson(Json& json) const = 0;
	virtual Json writeToJsonR() const; // R - return
	virtual void copyFrom(const GeneratorGuiBase& source);
	virtual bool hasSameSettingsAs(const GeneratorGuiBase& other) const = 0;
	virtual void updateSettingsFromLinked() = 0;
	virtual void updateLinkedSettings() = 0;

	// copy constructor, copy assignment operator, comparison operator? -- NO COMPARISON OPERATOR, because I feel
	// having same settings won't necessarily be being equal

	virtual ~GeneratorGuiBase();
};
