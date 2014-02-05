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

#include "mobskill_state.h"
#include "../../mobskill.h"
#include "../../entities/mobentity.h"

CMobSkillState::CMobSkillState(CBattleEntity* PEntity, CTargetFind* PTargetFind)
: CState(PEntity, PTargetFind)
{
	PROFILE_FUNC();
  m_PMob = (CMobEntity*)PEntity;

  m_PMobSkill = NULL;
  m_startTime = 0;
  m_useTime = 0;
}

CMobSkill* CMobSkillState::PickSkill(PICKSKILL pickFlags = PICKSKILL_RANDOM)
{
	PROFILE_FUNC();
  // pick and return a random skill
  return NULL;
}

bool CMobSkillState::CanUseSkill(CMobSkill* PMobSkill, CBattleEntity* PTarget)
{
	PROFILE_FUNC();
  return false;
}

bool CMobSkillState::CanUseTwoHour(CBattleEntity* PTarget, JOBTYPE job)
{
	PROFILE_FUNC();
  return false;
}

STATESTATUS CMobSkillState::UseSkill(CMobSkill* PMobSkill, CBattleEntity* PTarget)
{
	PROFILE_FUNC();
  return STATESTATUS_ERROR;
}

STATESTATUS CMobSkillState::UseTwoHour(CBattleEntity* PTarget, JOBTYPE job)
{
	PROFILE_FUNC();
  return STATESTATUS_ERROR;
}

void CMobSkillState::InterruptSkill()
{
	PROFILE_FUNC();

}

void CMobSkillState::FinishSkill()
{
	PROFILE_FUNC();

}

STATESTATUS CMobSkillState::Update(uint32 tick)
{
	PROFILE_FUNC();
  if(CState::Update(tick) == STATESTATUS_ERROR || !CheckValidTarget(m_PTarget))
  {
    return STATESTATUS_ERROR;
  }

  if(m_startTime == 0) m_startTime = tick;

  if(tick - m_startTime >= m_useTime)
  {
    if(!ValidUse())
    {
      return STATESTATUS_INTERRUPT;
    }
    else
    {
      return STATESTATUS_FINISH;
    }
  }

  return STATESTATUS_TICK;
}

void CMobSkillState::Clear()
{
	PROFILE_FUNC();
  CState::Clear();

  m_PMobSkill = NULL;
}

CMobSkill* CMobSkillState::GetSkill()
{
	PROFILE_FUNC();
  return m_PMobSkill;
}

bool CMobSkillState::IsUsing()
{
	PROFILE_FUNC();
  return m_PMobSkill != NULL;
}

bool CMobSkillState::ValidUse()
{
	PROFILE_FUNC();
  return true;
}