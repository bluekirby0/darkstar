/*
===========================================================================

  Copyright (c) 2010-2014 Darkstar Dev Teams

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see http://www.gnu.org/licenses/

  This file is part of DarkStar-server source code.

===========================================================================
*/

#include <string.h>
#include "weapon_skill.h"

CWeaponSkill::CWeaponSkill(uint16 id)
{
	PROFILE_FUNC();
	m_ID = id;

	m_AnimationId = 0;
	m_AOE         = 0;
	m_Skilllevel  = 0;
	m_TypeID      = 0;
	m_Range       = 0;
	m_PrimarySkillchain   = SC_NONE;
    m_SecondarySkillchain = SC_NONE;
    m_TertiarySkillchain  = SC_NONE;
    m_mainOnly = 0;

	memset(m_Job, 0, sizeof(m_Job));
}

void CWeaponSkill::setID(uint16 id)
{
	PROFILE_FUNC();
	m_ID = id;
}

void CWeaponSkill::setType(uint8 type)
{
	PROFILE_FUNC();
	m_TypeID = type;
}

bool CWeaponSkill::isAoE()
{
	PROFILE_FUNC();
    return m_AOE == 2;
}

bool CWeaponSkill::mainOnly()
{
	PROFILE_FUNC();
    return m_mainOnly;
}

void CWeaponSkill::setMainOnly(uint8 main)
{
	PROFILE_FUNC();
    m_mainOnly = main;
}

void CWeaponSkill::setJob(int8* jobs)
{
	PROFILE_FUNC();
	memcpy(&m_Job[1], jobs, 22);
}

void CWeaponSkill::setSkillLevel(uint16 level)
{
	PROFILE_FUNC();
	m_Skilllevel = level;
}

const int8* CWeaponSkill::getName()
{
	PROFILE_FUNC();
	return m_name.c_str();
}

void CWeaponSkill::setElement(uint8 element)
{
	PROFILE_FUNC();
    m_Element = element;
}

void CWeaponSkill::setPrimarySkillchain(uint8 skillchain)
{
	PROFILE_FUNC();
	m_PrimarySkillchain = skillchain;
}

void CWeaponSkill::setSecondarySkillchain(uint8 skillchain)
{
	PROFILE_FUNC();
    m_SecondarySkillchain = skillchain;
}

void CWeaponSkill::setTertiarySkillchain(uint8 skillchain)
{
	PROFILE_FUNC();
    m_TertiarySkillchain = skillchain;
}

void CWeaponSkill::setName(int8* name)
{
	PROFILE_FUNC();
	m_name.clear();
	m_name.insert(0,name);
}

void CWeaponSkill::setAnimationId(int8 id)
{
	PROFILE_FUNC();
	m_AnimationId = id;
}

void CWeaponSkill::setAoe(uint8 aoe)
{
	PROFILE_FUNC();
	m_AOE = aoe;
}

void CWeaponSkill::setRange(uint8 range)
{
	PROFILE_FUNC();
	m_Range = range;
}

uint16 CWeaponSkill::getID()
{
	PROFILE_FUNC();
	return m_ID;
}

uint8 CWeaponSkill::getType()
{
	PROFILE_FUNC();
	return m_TypeID;
}

uint8 CWeaponSkill::getJob(JOBTYPE job)
{
	PROFILE_FUNC();
	return m_Job[job];
}

uint16 CWeaponSkill::getSkillLevel()
{
	PROFILE_FUNC();
	return m_Skilllevel;
}

uint8 CWeaponSkill::getElement()
{
	PROFILE_FUNC();
	return m_Element;
}

bool CWeaponSkill::isElemental()
{
	PROFILE_FUNC();
    return m_Element != 0;
}

uint8 CWeaponSkill::getAnimationId()
{
	PROFILE_FUNC();
	return m_AnimationId;
}

uint8 CWeaponSkill::getAoe()
{
	PROFILE_FUNC();
	return m_AOE;
}

uint8 CWeaponSkill::getRange()
{
	PROFILE_FUNC();
	return m_Range;
}

uint8 CWeaponSkill::getPrimarySkillchain()
{
	PROFILE_FUNC();
    return m_PrimarySkillchain;
}

uint8 CWeaponSkill::getSecondarySkillchain()
{
	PROFILE_FUNC();
    return m_SecondarySkillchain;
}

uint8 CWeaponSkill::getTertiarySkillchain()
{
	PROFILE_FUNC();
    return m_TertiarySkillchain;
}