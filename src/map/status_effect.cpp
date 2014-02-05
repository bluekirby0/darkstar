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

#include "../common/utils.h"

#include "entities/battleentity.h"
#include "status_effect.h"


CStatusEffect::CStatusEffect(EFFECT id, uint16 icon, uint16 power, uint32 tick, uint32 duration, uint32 subid, uint16 subPower, uint16 tier)
{
	PROFILE_FUNC();
	m_StatusID = id;
    m_Type     = 0;
	m_SubID	   = subid;
    m_Icon     = icon;
	m_Power	   = power;
    m_SubPower = subPower;
    m_Tier     = tier;
	m_Flag	   = EFFECTFLAG_NONE;
	m_TickTime = tick * 1000;
	m_Duration = duration * 1000;
    m_POwner = NULL;
}

CStatusEffect::~CStatusEffect()
{
	PROFILE_FUNC();
	for (uint32 i = 0; i < modList.size(); ++i)
	{
		delete modList.at(i);
	}
}

const int8* CStatusEffect::GetName()
{
	PROFILE_FUNC();
	return m_Name.c_str();
}

void CStatusEffect::SetOwner(CBattleEntity* Owner)
{
	PROFILE_FUNC();
    m_POwner = Owner;
}

EFFECT CStatusEffect::GetStatusID()
{
	PROFILE_FUNC();
	return m_StatusID;
}

CBattleEntity* CStatusEffect::GetOwner()
{
	PROFILE_FUNC();
	return m_POwner;
}

uint32 CStatusEffect::GetSubID()
{
	PROFILE_FUNC();
	return m_SubID;
}

uint16 CStatusEffect::GetType()
{
	PROFILE_FUNC();
    return m_Type;
}

uint16 CStatusEffect::GetIcon()
{
	PROFILE_FUNC();
	return m_Icon;
}

uint16 CStatusEffect::GetPower()
{
	PROFILE_FUNC();
	return m_Power;
}

uint16 CStatusEffect::GetSubPower()
{
	PROFILE_FUNC();
    return m_SubPower;
}

uint16 CStatusEffect::GetTier()
{
	PROFILE_FUNC();
    return m_Tier;
}

uint16 CStatusEffect::GetFlag()
{
	PROFILE_FUNC();
	return m_Flag;
}

uint32 CStatusEffect::GetTickTime()
{
	PROFILE_FUNC();
	return m_TickTime;
}

uint32 CStatusEffect::GetDuration()
{
	PROFILE_FUNC();
	return m_Duration;
}

uint32 CStatusEffect::GetStartTime()
{
	PROFILE_FUNC();
	return m_StartTime;
}

uint32 CStatusEffect::GetLastTick()
{
	PROFILE_FUNC();
	return m_LastTick;
}

void CStatusEffect::SetFlag(uint16 Flag)
{
	PROFILE_FUNC();
    m_Flag |= Flag;
}

void CStatusEffect::SetIcon(uint16 Icon)
{
	PROFILE_FUNC();
    DSP_DEBUG_BREAK_IF(m_POwner == NULL);

	m_Icon = Icon;
    m_POwner->StatusEffectContainer->UpdateStatusIcons();
}

void CStatusEffect::SetType(uint16 Type)
{
	PROFILE_FUNC();
    m_Type = Type;
}

void CStatusEffect::SetPower(uint16 Power)
{
	PROFILE_FUNC();
	m_Power = Power;
}

void CStatusEffect::SetSubPower(uint16 subPower)
{
	PROFILE_FUNC();
    m_SubPower = subPower;
}

void CStatusEffect::SetTier(uint16 tier)
{
	PROFILE_FUNC();
    m_Tier = tier;
}

void CStatusEffect::SetDuration(uint32 Duration)
{
	PROFILE_FUNC();
	m_Duration = Duration;
}

void CStatusEffect::SetStartTime(uint32 StartTime)
{
	PROFILE_FUNC();
	m_LastTick  = StartTime;
	m_StartTime = StartTime;
}

void CStatusEffect::SetLastTick(uint32 LastTick)
{
	PROFILE_FUNC();
	m_LastTick = LastTick;
}

void CStatusEffect::SetTickTime(uint32 tick)
{
	PROFILE_FUNC();
	m_TickTime = tick;
}

void CStatusEffect::SetName(const int8* name)
{
	PROFILE_FUNC();
	m_Name.clear();
	m_Name.insert(0,name);
}

void CStatusEffect::SetName(string_t name)
{
	PROFILE_FUNC();
	m_Name = name;
}

void CStatusEffect::addMod(uint16 modType, int16 amount)
{
	PROFILE_FUNC();
	for (uint32 i = 0; i < modList.size(); ++i)
	{
		if (modList.at(i)->getModID() == modType)
		{
			modList.at(i)->setModAmount(modList.at(i)->getModAmount() + amount);
			return;
		}
	}
	modList.push_back(new CModifier(modType, amount));
}