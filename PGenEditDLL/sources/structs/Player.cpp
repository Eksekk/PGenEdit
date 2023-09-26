#pragma once
#include "pch.h"
#include "main.h"
#include "Common.h"

int mm6::Player::removeFromInventory(/*Slot*/)
{
	return 0;
}

int mm6::Player::getBaseArmorClass()
{
	return 0;
}

int mm6::Player::getArmorClass()
{
	return 0;
}

int mm6::Player::getBaseAge()
{
	return 0;
}

int mm6::Player::getBaseMight()
{
	return 0;
}

int mm6::Player::recover(/*ByAmount*/)
{
	return 0;
}

int mm6::Player::getBasePersonality()
{
	return 0;
}

int mm6::Player::getBaseEndurance()
{
	return 0;
}

int mm6::Player::getBaseAccuracy()
{
	return 0;
}

int mm6::Player::getBaseSpeed()
{
	return 0;
}

int mm6::Player::getBaseLuck()
{
	return 0;
}

int mm6::Player::getBaseLevel()
{
	return 0;
}

int mm6::Player::getLevel()
{
	return 0;
}

int mm6::Player::getMight()
{
	return 0;
}

int mm6::Player::getIntellect()
{
	return 0;
}

int mm6::Player::getPersonality()
{
	return 0;
}

int mm6::Player::getEndurance()
{
	return 0;
}

int mm6::Player::getAccuracy()
{
	return 0;
}

int mm6::Player::getSpeed()
{
	return 0;
}

int mm6::Player::getLuck()
{
	return 0;
}

int mm6::Player::getMeleeAttack(/*IgnoreExtraHand [MM7+] = false*/)
{
	return 0;
}

int mm6::Player::calcMeleeDamage(/*JustWeaponDamage = false, IgnoreExtraHand = false, MonsterId = -1*/)
{
	return 0;
}

int mm6::Player::getRangedAttack()
{
	return 0;
}

int mm6::Player::calcRangedDamage(/*MonsterId = -1*/)
{
	return 0;
}

bool mm6::Player::isConscious()
{
	return false;
}

bool mm6::Player::calcHitOrMiss(/*Monster:structs.MapMonster, Range = 0, Bonus = 0*/)
{
	return false;
}

int mm6::Player::setRecoveryDelayRaw(/*Delay*/)
{
	return 0;
}

int mm6::Player::getAge()
{
	return 0;
}

char* mm6::Player::getMeleeDamageRangeText()
{
	return nullptr;
}

char* mm6::Player::getRangedDamageRangeText()
{
	return nullptr;
}

int mm6::Player::canTrain()
{
	return 0;
}

int mm6::Player::getFullHP()
{
	return 0;
}

int mm6::Player::doDamage(/*Damage, DamageKind:const.Damage = const.Damage.Phys*/)
{
	return 0;
}

int mm6::Player::addHP(/*Amount*/)
{
	return 0;
}

int mm6::Player::getFullHitPoints()
{
	return 0;
}

int mm6::Player::getFullSpellPoints()
{
	return 0;
}

int mm6::Player::getFullSP()
{
	return 0;
}

int mm6::Player::calcStatBonusByItems(/*Stat:const.Stats, IgnoreExtraHand [MM7+] = false*/)
{
	return 0;
}

int mm6::Player::calcStatBonusByMagic(/*Stat:const.Stats*/)
{
	return 0;
}

int mm6::Player::calcStatBonusBySkills(/*Stat:const.Stats*/)
{
	return 0;
}

int mm6::Player::getBaseMagicResistance()
{
	return 0;
}

int mm6::Player::getAttackDelay(/*Shoot = false*/)
{
	return 0;
}

int mm6::Player::doBadThing(/*Thing:const.MonsterBonus, Monster:structs.MapMonster[MM7+]*/)
{
	return 0;
}

int mm6::Player::getMerchantTotalSkill()
{
	return 0;
}

int mm6::Player::getDisarmTrapTotalSkill()
{
	return 0;
}

int mm6::Player::getDiplomacyTotalSkill()
{
	return 0;
}

int mm6::Player::getBaseColdResistance()
{
	return 0;
}

int mm6::Player::getBaseIntellect()
{
	return 0;
}

int mm6::Player::resetToClass()
{
	return 0;
}

int mm6::Player::addHitPoints()
{
	return 0;
}

int mm6::Player::getBaseFireResistance()
{
	return 0;
}

int mm6::Player::getBaseElectricityResistance()
{
	return 0;
}

int mm6::Player::showFaceExpression(/*Expression, Time = 0*/)
{
	return 0;
}

int mm6::Player::getBasePoisonResistance()
{
	return 0;
}

int mm6::Player::showFaceAnimation(/*Animation:const.FaceAnimation*/)
{
	return 0;
}

int mm6::Player::getFireResistance()
{
	return 0;
}

int mm6::Player::getElectricityResistance()
{
	return 0;
}

int mm6::Player::getColdResistance()
{
	return 0;
}

int mm6::Player::getPoisonResistance()
{
	return 0;
}

int mm6::Player::getMagicResistance()
{
	return 0;
}


int mm7::Player::recover(/*ByAmount*/)
{
	return 0;
}

char* mm7::Player::getMeleeDamageRangeText()
{
	return nullptr;
}

char* mm7::Player::getRangedDamageRangeText()
{
	return nullptr;
}

int mm7::Player::canTrain()
{
	return 0;
}

int mm7::Player::showFaceExpression(/*Expression, Time = 0*/)
{
	return 0;
}

int mm7::Player::doDamage(/*Damage, DamageKind:const.Damage = const.Damage.Phys*/)
{
	return 0;
}

int mm7::Player::showFaceAnimation(/*Animation:const.FaceAnimation*/)
{
	return 0;
}

bool mm7::Player::wearsItem(/*ItemNum, Slot:const.ItemSlot = 16*/)
{
	return false;
}

int mm7::Player::doBadThing(/*Thing:const.MonsterBonus, Monster:structs.MapMonster[MM7+]*/)
{
	return 0;
}

int mm7::Player::addCondition(/*Condition:const.Condition, CanResist = false*/)
{
	return 0;
}

int mm7::Player::getSex(/*BasedOnVoice[MM8] = false*/)
{
	return 0;
}

int mm7::Player::getFullHP()
{
	return 0;
}

int mm7::Player::getMainCondition()
{
	return 0;
}

int mm7::Player::addHitPoints()
{
	return 0;
}

int mm7::Player::getFullSP()
{
	return 0;
}

int mm7::Player::resetToClass()
{
	return 0;
}

int mm7::Player::getBaseMight()
{
	return 0;
}

int mm7::Player::getBasePersonality()
{
	return 0;
}

int mm7::Player::getBaseEndurance()
{
	return 0;
}

int mm7::Player::calcMeleeDamage(/*JustWeaponDamage = false, IgnoreExtraHand = false, MonsterId = -1*/)
{
	return 0;
}

int mm7::Player::calcRangedDamage(/*MonsterId = -1*/)
{
	return 0;
}

bool mm7::Player::calcHitOrMiss(/*Monster:structs.MapMonster, Range = 0, Bonus = 0*/)
{
	return false;
}

int mm7::Player::addHP(/*Amount*/)
{
	return 0;
}

int mm7::Player::getRangedDamageMin()
{
	return 0;
}

int mm7::Player::getLearningTotalSkill()
{
	return 0;
}

int mm7::Player::getPerceptionTotalSkill()
{
	return 0;
}

int mm7::Player::getMerchantTotalSkill()
{
	return 0;
}

int mm7::Player::calcStatBonusByItems(/*Stat:const.Stats, IgnoreExtraHand [MM7+] = false*/)
{
	return 0;
}

int mm7::Player::calcStatBonusByMagic(/*Stat:const.Stats*/)
{
	return 0;
}

int mm7::Player::calcStatBonusBySkills(/*Stat:const.Stats*/)
{
	return 0;
}

int mm7::Player::getSkill(/*Skill:const.Skills*/)
{
	return 0;
}

int mm7::Player::getAttackDelay(/*Shoot = false*/)
{
	return 0;
}

int mm7::Player::getFullHitPoints()
{
	return 0;
}

int mm7::Player::getFullSpellPoints()
{
	return 0;
}

int mm7::Player::getDisarmTrapTotalSkill()
{
	return 0;
}

int mm7::Player::getMeleeDamageMin()
{
	return 0;
}

int mm7::Player::getMeleeDamageMax()
{
	return 0;
}

bool mm7::Player::isConscious()
{
	return false;
}

int mm7::Player::getRangedDamageMax()
{
	return 0;
}

int mm7::Player::getBaseResistance(/*Res:const.Damage*/)
{
	return 0;
}

int mm7::Player::getBaseIntellect()
{
	return 0;
}

int mm7::Player::getResistance(/*Res:const.Damage*/)
{
	return 0;
}

int mm7::Player::hasItemBonus(/*Bonus2*/)
{
	return 0;
}

int mm7::Player::getBaseAccuracy()
{
	return 0;
}

int mm7::Player::getBaseSpeed()
{
	return 0;
}

int mm7::Player::getBaseLuck()
{
	return 0;
}

int mm7::Player::getBaseLevel()
{
	return 0;
}

int mm7::Player::getLevel()
{
	return 0;
}

int mm7::Player::getMight()
{
	return 0;
}

int mm7::Player::getIntellect()
{
	return 0;
}

int mm7::Player::getPersonality()
{
	return 0;
}

int mm7::Player::getEndurance()
{
	return 0;
}

int mm7::Player::getAccuracy()
{
	return 0;
}

int mm7::Player::getSpeed()
{
	return 0;
}

int mm7::Player::getLuck()
{
	return 0;
}

int mm7::Player::getMeleeAttack(/*IgnoreExtraHand [MM7+] = false*/)
{
	return 0;
}

int mm7::Player::setRecoveryDelayRaw(/*Delay*/)
{
	return 0;
}

int mm7::Player::removeFromInventory(/*Slot*/)
{
	return 0;
}

int mm7::Player::getRace()
{
	return 0;
}

int mm7::Player::getRangedAttack()
{
	return 0;
}

int mm7::Player::getBaseArmorClass()
{
	return 0;
}

int mm7::Player::getArmorClass()
{
	return 0;
}

int mm7::Player::getBaseAge()
{
	return 0;
}

int mm7::Player::getAge()
{
	return 0;
}


int mm8::Player::getMeleeDamageMin()
{
	return 0;
}

int mm8::Player::showFaceAnimation(/*Animation:const.FaceAnimation*/)
{
	return 0;
}

int mm8::Player::getIntellect()
{
	return 0;
}

int mm8::Player::getAge()
{
	return 0;
}

int mm8::Player::getBaseResistance(/*Res:const.Damage*/)
{
	return 0;
}

int mm8::Player::calcStatBonusBySkills(/*Stat:const.Stats*/)
{
	return 0;
}

int mm8::Player::getBaseLevel()
{
	return 0;
}

int mm8::Player::showFaceExpression(/*Expression, Time = 0*/)
{
	return 0;
}

int mm8::Player::getFullHitPoints()
{
	return 0;
}

int mm8::Player::doBadThing(/*Thing:const.MonsterBonus, Monster:structs.MapMonster[MM7+]*/)
{
	return 0;
}

int mm8::Player::getBaseLuck()
{
	return 0;
}

int mm8::Player::getRangedAttack()
{
	return 0;
}

int mm8::Player::doDamage(/*Damage, DamageKind:const.Damage = const.Damage.Phys*/)
{
	return 0;
}

int mm8::Player::canTrain()
{
	return 0;
}

int mm8::Player::getMerchantTotalSkill()
{
	return 0;
}

int mm8::Player::getRangedDamageMin()
{
	return 0;
}

int mm8::Player::addCondition(/*Condition:const.Condition, CanResist = false*/)
{
	return 0;
}

int mm8::Player::getPerceptionTotalSkill()
{
	return 0;
}

int mm8::Player::getLearningTotalSkill()
{
	return 0;
}

int mm8::Player::getMainCondition()
{
	return 0;
}

int mm8::Player::getFullSP()
{
	return 0;
}

int mm8::Player::getDisarmTrapTotalSkill()
{
	return 0;
}

bool mm8::Player::calcHitOrMiss(/*Monster:structs.MapMonster, Range = 0, Bonus = 0*/)
{
	return false;
}

int mm8::Player::calcRangedDamage(/*MonsterId = -1*/)
{
	return 0;
}

int mm8::Player::recover(/*ByAmount*/)
{
	return 0;
}

int mm8::Player::getStartingClass()
{
	return 0;
}

int mm8::Player::getBaseIntellect()
{
	return 0;
}

int mm8::Player::calcStatBonusByItems(/*Stat:const.Stats, IgnoreExtraHand [MM7+] = false*/)
{
	return 0;
}

bool mm8::Player::wearsItem(/*ItemNum, Slot:const.ItemSlot = 16*/)
{
	return false;
}

int mm8::Player::getFullSpellPoints()
{
	return 0;
}

int mm8::Player::getAttackDelay(/*Shoot = false*/)
{
	return 0;
}

int mm8::Player::hasItemBonus(/*Bonus2*/)
{
	return 0;
}

int mm8::Player::calcMeleeDamage(/*JustWeaponDamage = false, IgnoreExtraHand = false, MonsterId = -1*/)
{
	return 0;
}

int mm8::Player::getResistance(/*Res:const.Damage*/)
{
	return 0;
}

int mm8::Player::getAccuracy()
{
	return 0;
}

int mm8::Player::getBaseMight()
{
	return 0;
}

int mm8::Player::getSex(/*BasedOnVoice[MM8] = false*/)
{
	return 0;
}

char* mm8::Player::getRangedDamageRangeText()
{
	return nullptr;
}

int mm8::Player::getMeleeDamageMax()
{
	return 0;
}

int mm8::Player::getRangedDamageMax()
{
	return 0;
}

int mm8::Player::getBaseSpeed()
{
	return 0;
}

int mm8::Player::getBaseAccuracy()
{
	return 0;
}

int mm8::Player::getMeleeAttack(/*IgnoreExtraHand [MM7+] = false*/)
{
	return 0;
}

int mm8::Player::addHP(/*Amount*/)
{
	return 0;
}

int mm8::Player::addHitPoints()
{
	return 0;
}

int mm8::Player::getBaseArmorClass()
{
	return 0;
}

int mm8::Player::getBaseAge()
{
	return 0;
}

int mm8::Player::getMight()
{
	return 0;
}

int mm8::Player::getSkill(/*Skill:const.Skills*/)
{
	return 0;
}

int mm8::Player::getSpeed()
{
	return 0;
}

int mm8::Player::getBasePersonality()
{
	return 0;
}

bool mm8::Player::isConscious()
{
	return false;
}

int mm8::Player::removeFromInventory(/*Slot*/)
{
	return 0;
}

int mm8::Player::getBaseEndurance()
{
	return 0;
}

int mm8::Player::getEndurance()
{
	return 0;
}

int mm8::Player::calcStatBonusByMagic(/*Stat:const.Stats*/)
{
	return 0;
}

int mm8::Player::setRecoveryDelayRaw(/*Delay*/)
{
	return 0;
}

int mm8::Player::getPersonality()
{
	return 0;
}

char* mm8::Player::getMeleeDamageRangeText()
{
	return nullptr;
}

int mm8::Player::getLevel()
{
	return 0;
}

int mm8::Player::getFullHP()
{
	return 0;
}

int mm8::Player::getArmorClass()
{
	return 0;
}

int mm8::Player::getLuck()
{
	return 0;
}

