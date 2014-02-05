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

#include "map.h"
#include "spell.h"
#include "blue_spell.h"
#include "utils/blueutils.h"


CSpell::CSpell(uint16 id)
{
	PROFILE_FUNC();
	m_ID = id;

    m_radius          = 0;
	m_mpCost            = 0;
	m_castTime          = 0;
	m_recastTime        = 0;
	m_animation         = 0;
    m_AOE             = 0;
    m_animationTime     = 0;
    m_skillType         = 0;
    m_zoneMisc          = 0;
    m_message           = 0;
    m_DefaultMessage    = 0;
    m_MagicBurstMessage = 0;
    m_element           = 0;
	m_spellGroup        = SPELLGROUP_NONE;
    m_meritId           = 0;
    m_requirements      = 0;

	memset(m_job, 0, sizeof(m_job));
}

void CSpell::resetMessage()
{
	PROFILE_FUNC();
    setMessage(getDefaultMessage());
}

void CSpell::setTotalTargets(uint16 total)
{
	PROFILE_FUNC();
    m_totalTargets = total;
}

uint16 CSpell::getTotalTargets()
{
	PROFILE_FUNC();
    return m_totalTargets;
}

void CSpell::setID(uint16 id)
{
	PROFILE_FUNC();
	m_ID = id;
}

uint16 CSpell::getID()
{
	PROFILE_FUNC();
    return m_ID;
}

uint8 CSpell::getJob(JOBTYPE JobID)
{
	PROFILE_FUNC();
	return (m_job[JobID] == CANNOT_USE_SPELL ? 255 : m_job[JobID]);
}

void CSpell::setJob(int8* jobs)
{
	PROFILE_FUNC();
	memcpy(&m_job[1], jobs, 22);
}

uint32 CSpell::getCastTime()
{
	PROFILE_FUNC();
	return m_castTime;
}

void CSpell::setCastTime(uint32 CastTime)
{
	PROFILE_FUNC();
	m_castTime = CastTime;
}

uint32 CSpell::getRecastTime()
{
	PROFILE_FUNC();
	return m_recastTime;
}

void CSpell::setRecastTime(uint32 RecastTime)
{
	PROFILE_FUNC();
	m_recastTime = RecastTime;
}

const int8* CSpell::getName()
{
	PROFILE_FUNC();
	return m_name.c_str();
}

void CSpell::setName(int8* name)
{
	PROFILE_FUNC();
	m_name.clear();
	m_name.insert(0,name);
}

SPELLGROUP CSpell::getSpellGroup()
{
	PROFILE_FUNC();
	return m_spellGroup;
}

void CSpell::setSpellGroup(SPELLGROUP SpellGroup)
{
	PROFILE_FUNC();
	m_spellGroup = SpellGroup;
}

uint8 CSpell::getSkillType()
{
	PROFILE_FUNC();
    return m_skillType;
}

void CSpell::setSkillType(uint8 SkillType)
{
	PROFILE_FUNC();
    m_skillType = SkillType;
}

bool CSpell::isBuff()
{
	PROFILE_FUNC();
    return (getValidTarget() & TARGET_SELF) && !(getValidTarget() & TARGET_ENEMY);
}

bool CSpell::tookEffect()
{
	PROFILE_FUNC();
    if(m_message == 75 || m_message == 284 || m_message == 283 || m_message == 85){
        return false;
    }
    return true;
}

bool CSpell::hasMPCost()
{
	PROFILE_FUNC();
    return m_spellGroup != SPELLGROUP_SONG && m_spellGroup != SPELLGROUP_NINJUTSU;
}

bool CSpell::isHeal()
{
	PROFILE_FUNC();
    return (getValidTarget() & TARGET_SELF) && getSkillType() == SKILL_HEA || m_ID == 549 || m_ID == 578 || m_ID == 581 || m_ID == 593;
}

bool CSpell::isNa()
{
	PROFILE_FUNC();
    return m_ID >= 14 && m_ID <= 20;
}

bool CSpell::canHitShadow()
{
	PROFILE_FUNC();
    return m_ID != 244 && canTargetEnemy();
}

bool CSpell::dealsDamage()
{
	PROFILE_FUNC();
    //damage or drain hp
    return m_message==2 || m_message==227;
}

uint8 CSpell::getRadius()
{
	PROFILE_FUNC();
    return m_radius;
}

uint16 CSpell::getZoneMisc()
{
	PROFILE_FUNC();
    return m_zoneMisc;
}

void CSpell::setZoneMisc(uint16 Misc)
{
	PROFILE_FUNC();
    m_zoneMisc = Misc;
}

uint16 CSpell::getAnimationID()
{
	PROFILE_FUNC();
	return m_animation;
}

void CSpell::setAnimationID(uint16 AnimationID)
{
	PROFILE_FUNC();
	m_animation = AnimationID;
}

uint16 CSpell::getAnimationTime()
{
	PROFILE_FUNC();
    return m_animationTime;
}

void CSpell::setAnimationTime(uint16 AnimationTime)
{
	PROFILE_FUNC();
    m_animationTime = AnimationTime;
}

uint16 CSpell::getMPCost()
{
	PROFILE_FUNC();
	return m_mpCost;
}

void CSpell::setMPCost(uint16 MP)
{
	PROFILE_FUNC();
	m_mpCost = MP;
}

bool CSpell::canTargetEnemy()
{
	PROFILE_FUNC();
    return (getValidTarget() & TARGET_ENEMY) && !(getValidTarget() & TARGET_SELF);
}

uint8 CSpell::getAOE()
{
	PROFILE_FUNC();
	return m_AOE;
}

void CSpell::setAOE(uint8 AOE)
{
	PROFILE_FUNC();
	m_AOE = AOE;
}

uint16 CSpell::getBase()
{
	PROFILE_FUNC();
	return m_base;
}

void CSpell::setBase(uint16 base)
{
	PROFILE_FUNC();
	m_base = base;
}

uint8 CSpell::getValidTarget()
{
	PROFILE_FUNC();
	return m_ValidTarget;
}

void CSpell::setValidTarget(uint8 ValidTarget)
{
	PROFILE_FUNC();
	m_ValidTarget = ValidTarget;
}

float CSpell::getMultiplier()
{
	PROFILE_FUNC();
	return m_multiplier;
}

void CSpell::setMultiplier(float multiplier)
{
	PROFILE_FUNC();
	m_multiplier = multiplier;
}

uint16 CSpell::getMessage()
{
	PROFILE_FUNC();
    return m_message;
}

uint16 CSpell::getAoEMessage()
{
	PROFILE_FUNC();
    switch(m_message){
        case 93: // vanishes
            return 273;
        case 85: // resists
            return 284;
        case 230: //casts gain the effect of
            return 266; // gains the effect of
        case 236: // is blind
            // return 203;
            return 277;
            // 279
        case 237: //if its a damage spell msg and is hitting the 2nd+ target
        return 278;
        case 2: //if its a damage spell msg and is hitting the 2nd+ target
            return 264;
        default:
            return m_message;
    }
}

void CSpell::setMessage(uint16 message)
{
	PROFILE_FUNC();
    m_message = message;
}

uint16 CSpell::getDefaultMessage()
{
	PROFILE_FUNC();
    return m_DefaultMessage;
}

void CSpell::setDefaultMessage(uint16 message)
{
	PROFILE_FUNC();
    m_DefaultMessage = message;
}

uint16 CSpell::getMagicBurstMessage()
{
	PROFILE_FUNC();
    return m_MagicBurstMessage;
}

void CSpell::setMagicBurstMessage(uint16 message)
{
	PROFILE_FUNC();
    m_MagicBurstMessage = message;
}

uint16 CSpell::getElement()
{
	PROFILE_FUNC();
	return m_element;
}

void CSpell::setElement(uint16 element)
{
	PROFILE_FUNC();
	m_element = element;
}

void CSpell::setCE(uint16 ce)
{
	PROFILE_FUNC();
	m_CE = ce;
}

uint16 CSpell::getCE()
{
	PROFILE_FUNC();
	return m_CE;
}

void CSpell::setRadius(uint8 radius)
{
	PROFILE_FUNC();
    m_radius = radius;
}

void CSpell::setVE(uint16 ve)
{
	PROFILE_FUNC();
	m_VE = ve;
}

uint16 CSpell::getVE()
{
	PROFILE_FUNC();
	return m_VE;
}

void CSpell::setModifiedRecast(uint32 mrec)
{
	PROFILE_FUNC();
	m_modifiedRecastTime = mrec;
}

uint32 CSpell::getModifiedRecast()
{
	PROFILE_FUNC();
	return m_modifiedRecastTime;
}

uint8 CSpell::getRequirements()
{
	PROFILE_FUNC();
	return m_requirements;
}

void CSpell::setRequirements(uint8 requirements)
{
	PROFILE_FUNC();
	m_requirements = requirements;
}

uint16 CSpell::getMeritId()
{
	PROFILE_FUNC();
	return m_meritId;
}

void CSpell::setMeritId(uint16 meritId)
{
	PROFILE_FUNC();
	m_meritId = meritId;
}

/************************************************************************
*                                                                       *
*  Реализация namespase для работы с заклинаниями                       *
*                                                                       *
************************************************************************/

namespace spell
{
    CSpell* PSpellList[MAX_SPELL_ID]; // список заклинаний
	std::map<uint16, uint16> PMobSkillToBlueSpell[256]; // maps the skill id (key) to spell id (value).

    /************************************************************************
    *                                                                       *
    *  Загружаем список заклинаний                                          *
    *                                                                       *
    ************************************************************************/

    void LoadSpellList()
    {
		PROFILE_FUNC();
	    memset(PSpellList, 0, sizeof(PSpellList));

	    const int8* Query = "SELECT spellid, name, jobs, `group`, validTargets, skill, castTime, recastTime, animation, animationTime, mpCost, \
					         AOE, base, element, zonemisc, multiplier, message, magicBurstMessage, CE, VE, requirements \
							 FROM spell_list \
							 WHERE spellid < %u;";

	    int32 ret = Sql_Query(SqlHandle, Query, MAX_SPELL_ID);

	    if( ret != SQL_ERROR && Sql_NumRows(SqlHandle) != 0)
	    {
		    while(Sql_NextRow(SqlHandle) == SQL_SUCCESS)
		    {
			    CSpell* PSpell = NULL;

                uint16 id = Sql_GetUIntData(SqlHandle,0);

                if (id > 0x200)
                {
                    PSpell = new CBlueSpell(id);
                }
                else
                {
                    PSpell = new CSpell(id);
                }

			    PSpell->setName(Sql_GetData(SqlHandle,1));
			    PSpell->setJob(Sql_GetData(SqlHandle,2));
			    PSpell->setSpellGroup((SPELLGROUP)Sql_GetIntData(SqlHandle,3));
			    PSpell->setValidTarget(Sql_GetIntData(SqlHandle,4));
                PSpell->setSkillType(Sql_GetIntData(SqlHandle,5));
			    PSpell->setCastTime(Sql_GetIntData(SqlHandle,6));
			    PSpell->setRecastTime(Sql_GetIntData(SqlHandle,7));
			    PSpell->setAnimationID(Sql_GetIntData(SqlHandle,8));
                PSpell->setAnimationTime(Sql_GetIntData(SqlHandle,9));
			    PSpell->setMPCost(Sql_GetIntData(SqlHandle,10));
			    PSpell->setAOE(Sql_GetIntData(SqlHandle,11));
			    PSpell->setBase(Sql_GetIntData(SqlHandle,12));
			    PSpell->setElement(Sql_GetIntData(SqlHandle,13));
                PSpell->setZoneMisc(Sql_GetIntData(SqlHandle,14));
			    PSpell->setMultiplier(Sql_GetIntData(SqlHandle,15));
                PSpell->setMessage(Sql_GetIntData(SqlHandle,16));
                PSpell->setDefaultMessage(Sql_GetIntData(SqlHandle,16));
                PSpell->setMagicBurstMessage(Sql_GetIntData(SqlHandle,17));
			    PSpell->setCE(Sql_GetIntData(SqlHandle,18));
			    PSpell->setVE(Sql_GetIntData(SqlHandle,19));
                PSpell->setRequirements(Sql_GetIntData(SqlHandle,20));

                if(PSpell->getAOE())
                {
                    // default radius
                    PSpell->setRadius(10);
                }

			    PSpellList[PSpell->getID()] = PSpell;
		    }
	    }

		const int8* blueQuery = "SELECT spellid, mob_skill_id, set_points, trait_category, trait_category_weight, primary_sc, secondary_sc \
							 FROM blue_spell_list;";

	    ret = Sql_Query(SqlHandle, blueQuery);

	    if( ret != SQL_ERROR && Sql_NumRows(SqlHandle) != 0)
	    {
			while(Sql_NextRow(SqlHandle) == SQL_SUCCESS)
		    {
				// Sanity check the spell ID
				uint16 spellId = Sql_GetIntData(SqlHandle,0);
				if (spellId > MAX_SPELL_ID || spellId < 0x200) {
                    ShowWarning("Tried to load a blue magic spell with ID %u which is higher than the max (%u) or less than 0x200!\n", spellId, MAX_SPELL_ID);
                    continue;
                }

                if(PSpellList[spellId] == NULL)
                {
					ShowWarning("spell::LoadSpellList Tried to load NULL blue spell (%u)\n", spellId);
                    continue;
                }

				((CBlueSpell*)PSpellList[spellId])->setMonsterSkillId(Sql_GetIntData(SqlHandle,1));
                ((CBlueSpell*)PSpellList[spellId])->setSetPoints(Sql_GetIntData(SqlHandle,2));
                ((CBlueSpell*)PSpellList[spellId])->setTraitCategory(Sql_GetIntData(SqlHandle,3));
                ((CBlueSpell*)PSpellList[spellId])->setTraitWeight(Sql_GetIntData(SqlHandle,4));
                ((CBlueSpell*)PSpellList[spellId])->setPrimarySkillchain(Sql_GetIntData(SqlHandle,5));
                ((CBlueSpell*)PSpellList[spellId])->setSecondarySkillchain(Sql_GetIntData(SqlHandle,6));
				PMobSkillToBlueSpell->insert(std::make_pair(Sql_GetIntData(SqlHandle,1), spellId));
			}
		}
	    ret = Sql_Query(SqlHandle,"SELECT spellId, modId, value FROM blue_spell_mods WHERE spellId IN (SELECT spellId FROM spell_list LEFT JOIN blue_spell_list USING (spellId))");

	    if( ret != SQL_ERROR && Sql_NumRows(SqlHandle) != 0)
	    {
		    while(Sql_NextRow(SqlHandle) == SQL_SUCCESS)
		    {
			    uint16 spellId = (uint16)Sql_GetUIntData(SqlHandle,0);
			    uint16 modID  = (uint16)Sql_GetUIntData(SqlHandle,1);
			    int16  value  = (int16) Sql_GetIntData (SqlHandle,2);

			    if (!(spellId > MAX_SPELL_ID) && (PSpellList[spellId] != NULL) && spellId > 0x200)
			    {
                    ((CBlueSpell*)PSpellList[spellId])->addModifier(new CModifier(modID,value));
			    }
		    }
	    }

	    ret = Sql_Query(SqlHandle,"SELECT spellId, meritId FROM spell_list INNER JOIN merits ON spell_list.name = merits.name;");

	    if( ret != SQL_ERROR && Sql_NumRows(SqlHandle) != 0)
	    {
		    while(Sql_NextRow(SqlHandle) == SQL_SUCCESS)
		    {
			    uint16 spellId = (uint16)Sql_GetUIntData(SqlHandle,0);

			    if (!(spellId > MAX_SPELL_ID) && (PSpellList[spellId] != NULL))
			    {
                    PSpellList[spellId]->setMeritId(Sql_GetUIntData(SqlHandle,1));
			    }
		    }
	    }
    }

	CSpell* GetSpellByMonsterSkillId(uint16 SkillID) {
		PROFILE_FUNC();
		std::map<uint16,uint16>::iterator it = PMobSkillToBlueSpell->find(SkillID);
		if (it == PMobSkillToBlueSpell->end()) {
			return NULL;
		}
		else {
			uint16 spellId = it->second;
			if (spellId > MAX_SPELL_ID) {
				ShowError("Resolved spell ID from mob skill %u is out of spell range (%u)\n",SkillID,spellId);
				return NULL;
			}
			return PSpellList[spellId];
		}
	}

    /************************************************************************
    *                                                                       *
    *  Get Spell By ID                                                      *
    *                                                                       *
    ************************************************************************/

    CSpell* GetSpell(uint16 SpellID)
	{
		PROFILE_FUNC();
	    if (SpellID < MAX_SPELL_ID)
	    {
		    return PSpellList[SpellID];
	    }
	    ShowFatalError(CL_RED"SpellID <%u> out of range\n" CL_RESET, SpellID);
	    return NULL;
    }

    /************************************************************************
    *                                                                       *
    *  Check If user can cast spell                                         *
    *                                                                       *
    ************************************************************************/

    bool CanUseSpell(CBattleEntity* PCaster, uint16 SpellID)
	{
		PROFILE_FUNC();
        bool usable = false;
        CSpell* spell = GetSpell(SpellID);
	    if (spell != NULL)
	    {
		    uint8 JobMLVL = spell->getJob(PCaster->GetMJob());
		    uint8 JobSLVL = spell->getJob(PCaster->GetSJob());
            uint8 requirements = spell->getRequirements();

		    if(PCaster->GetMLevel() >= JobMLVL)
            {
                if (requirements & SPELLREQ_TABULA_RASA && PCaster->StatusEffectContainer->HasStatusEffect(EFFECT_TABULA_RASA))
                {
                    usable = true;
                }
                if (requirements & SPELLREQ_ADDENDUM_BLACK && PCaster->GetMJob() == JOB_SCH)
                {
                    if(PCaster->StatusEffectContainer->HasStatusEffect(EFFECT_ADDENDUM_BLACK) || PCaster->StatusEffectContainer->HasStatusEffect(EFFECT_ENLIGHTENMENT))
                    {
                        usable = true;
                    }
                }
                else if (requirements & SPELLREQ_ADDENDUM_WHITE && PCaster->GetMJob() == JOB_SCH)
                {
                    if (PCaster->StatusEffectContainer->HasStatusEffect(EFFECT_ADDENDUM_WHITE) || PCaster->StatusEffectContainer->HasStatusEffect(EFFECT_ENLIGHTENMENT))
                    {
                        usable = true;
                    }
                }
                else if (SpellID > 0x200)
                {
                    if (PCaster->objtype == TYPE_PC)
                    {
                        usable = blueutils::IsSpellSet((CCharEntity*)PCaster, (CBlueSpell*)spell);
                    }
                    else
                    {
                        usable = true;
                    }
                }
                else
                {
                    usable = true;
                }
            }
            if(PCaster->GetSLevel() >= JobSLVL)
            {
                if (requirements & SPELLREQ_TABULA_RASA && PCaster->StatusEffectContainer->HasStatusEffect(EFFECT_TABULA_RASA))
                {
                    usable = true;
                }
                if(requirements & SPELLREQ_ADDENDUM_BLACK && PCaster->GetSJob() == JOB_SCH)
                {
                    if(PCaster->StatusEffectContainer->HasStatusEffect(EFFECT_ADDENDUM_BLACK))
                    {
                        usable = true;
                    }
                }
                else if (requirements & SPELLREQ_ADDENDUM_WHITE && PCaster->GetSJob() == JOB_SCH)
                {
                    if (PCaster->StatusEffectContainer->HasStatusEffect(EFFECT_ADDENDUM_WHITE))
                    {
                        usable = true;
                    }
                }
                else if (SpellID > 0x200)
                {
                    if (PCaster->objtype == TYPE_PC)
                    {
                        usable = blueutils::IsSpellSet((CCharEntity*)PCaster, (CBlueSpell*)spell);
                    }
                    else
                    {
                        usable = true;
                    }
                }
                else
                {
                    usable = true;
                }
            }
	    }
	    return usable;
    }

	// This is a utility method for mobutils, when we want to work out if we can give monsters a spell
	// but they are on an odd job (e.g. PLDs getting -ga3)
	bool CanUseSpellWith(uint16 spellId, JOBTYPE job, uint8 level)
	{
		PROFILE_FUNC();
		if (GetSpell(spellId) != NULL)
	    {
		    uint8 jobMLevel = PSpellList[spellId]->getJob(job);

		    return level > jobMLevel;
	    }
	    return false;
	}

    float GetSpellRadius(CSpell* spell, CBattleEntity* entity)
	{
		PROFILE_FUNC();
        float total = spell->getRadius();

        // brd gets bonus radius from string skill
        if(spell->getSpellGroup() == SPELLGROUP_SONG && (spell->getValidTarget() & TARGET_SELF)){
            // TODO: make sure you have string intru equiped for player
            if(entity->objtype == TYPE_MOB || entity->GetMJob() == JOB_BRD){
                total += ((float)entity->GetSkill(SKILL_STR) / 276) * 10;
            }
        }

        if(total > 20){
            total = 20;
        }

        return total;
    }

};
