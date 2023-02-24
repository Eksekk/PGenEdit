#pragma once
#include "pch.h"
#include "main.h"
#include "Enum_const.h"

struct SkillValue
{
	int level, mastery;

	bool operator==(const SkillValue& other) const;
	bool operator!=(const SkillValue& other) const;
	bool isZero() const;
	std::string toString() const;
};

SkillValue splitSkill(int skill);
int joinSkill(SkillValue skill);
wxString& operator<<(wxString& str, const SkillValue& val);

class PlayerSkill;
struct PlayerSkillValue
{
	PlayerSkill* skill;
	SkillValue value;
};

enum SkillType
{
	SKILL_GENERIC = 0, // see above
	SKILL_MELEE,
	SKILL_RANGED,
	SKILL_DEFENSIVE,
	SKILL_MAGIC,
	SKILL_UTILITY,
	SKILL_TYPE_COUNT
};

extern const std::unordered_map<std::string, int> skillTypeEnumStringToId;
extern const std::unordered_map<int, std::string> skillTypeEnumIdToString;

enum SkillCategory
{
	SKILLCAT_WEAPON = 0,
	SKILLCAT_ARMOR,
	SKILLCAT_MAGIC,
	SKILLCAT_MISC
};

extern const std::unordered_map<std::string, int> skillCategoryEnumStringToId;
extern const std::unordered_map<int, std::string> skillCategoryEnumIdToString;

enum SkillSpecial // don't make hundreds of skill types, instead associate additional property with certain skills
{
	SKSPC_NONE = 0,
	SKSPC_BLASTER,
	SKSPC_SHIELD,
	SKSPC_ELEMENTAL,
	SKSPC_SELF,
	SKSPC_MAGIC_EXCLUSIVE,
	SKSPC_MEDITATION,
	SKSPC_RACE_SKILL
};

extern const std::unordered_map<std::string, int> skillSpecialEnumStringToId;
extern const std::unordered_map<int, std::string> skillSpecialEnumIdToString;

[[nodiscard]] int skillpointsSpentForSkill(SkillValue sv);

class PlayerSkill
{
public:
	int id;
	std::string name;
	std::vector<SkillType> types;
	SkillSpecial special;
	SkillCategory category;
	std::array<int, 5> trainCost;
	std::unordered_map<int, Mastery> maxMasteryByClass; // <class, mastery>
	std::unordered_map<int, double> affinityByPlayerType;
	bool doNotGenerate; // for skills like diplomacy in mm7 (yes, it exists ingame)

	int getFullTrainCostForMastery(Mastery m);
	int getFullTrainCostForMastery(SkillValue sv);
	int getFullTrainCostForMastery(int m);

	PlayerSkill();
};