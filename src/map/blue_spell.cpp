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

#include "blue_spell.h"

CBlueSpell::CBlueSpell(uint16 id) : CSpell(id)
{
	PROFILE_FUNC();
	m_monsterSkillId = 0;
    m_setPoints      = 0;
    m_ecosystem      = 0;
    m_traitCategory  = 0;
    m_traitWeight    = 0;
}

uint16 CBlueSpell::getMonsterSkillId()
{
	PROFILE_FUNC();
	return m_monsterSkillId;
}

void CBlueSpell::setMonsterSkillId(uint16 skillid)
{
	PROFILE_FUNC();
	m_monsterSkillId = skillid;
}

uint8 CBlueSpell::getSetPoints()
{
	PROFILE_FUNC();
	return m_setPoints;
}

void CBlueSpell::setSetPoints(uint8 setpoints)
{
	PROFILE_FUNC();
	m_setPoints = setpoints;
}

uint8 CBlueSpell::getEcosystem()
{
	PROFILE_FUNC();
	return m_ecosystem;
}

void CBlueSpell::setEcosystem(uint8 ecosystem)
{
	PROFILE_FUNC();
	m_ecosystem = ecosystem;
}

uint8 CBlueSpell::getTraitCategory()
{
	PROFILE_FUNC();
	return m_traitCategory;
}

void CBlueSpell::setTraitCategory(uint8 category)
{
	PROFILE_FUNC();
	m_traitCategory = category;
}

uint8 CBlueSpell::getTraitWeight()
{
	PROFILE_FUNC();
	return m_traitWeight;
}

void CBlueSpell::setTraitWeight(uint8 weight)
{
	PROFILE_FUNC();
	m_traitWeight = weight;
}

uint8 CBlueSpell::getPrimarySkillchain()
{
	PROFILE_FUNC();
    return m_PrimarySkillchain;
}

void CBlueSpell::setPrimarySkillchain(uint8 sc)
{
	PROFILE_FUNC();
    m_PrimarySkillchain = sc;
}

uint8 CBlueSpell::getSecondarySkillchain()
{
	PROFILE_FUNC();
    return m_SecondarySkillchain;
}

void CBlueSpell::setSecondarySkillchain(uint8 sc)
{
	PROFILE_FUNC();
    m_SecondarySkillchain = sc;
}

void CBlueSpell::addModifier(CModifier* modifier)
{
	PROFILE_FUNC();
    modList.push_back(modifier);
}

