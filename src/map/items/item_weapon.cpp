﻿/*
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
#include "../entities/battleentity.h"
#include "../utils/charutils.h"
#include "../utils/itemutils.h"
#include "../utils/battleutils.h"

#include "item_weapon.h"


/************************************************************************
*                                                                       *
*                                                                       *
*                                                                       *
************************************************************************/

CItemWeapon::CItemWeapon(uint16 id) : CItemArmor(id)
{
	PROFILE_FUNC();
	setType(ITEM_WEAPON);

	m_skillType		= SKILL_NON;
	m_subSkillType	= SUBSKILL_XBO;
	m_damage		= 0;
    m_effect		= 0;
	m_dmgType		= DAMAGE_NONE;
	m_delay			= 8000;
	m_baseDelay		= 8000;		//this should only be needed for mobs (specifically mnks)
    m_maxHit		= 0;
    m_ranged		= false;
    m_twoHanded		= false;
	m_unlockId		= 0;
}

CItemWeapon::~CItemWeapon() {
	PROFILE_FUNC();
}

void CItemWeapon::resetDelay()
{
	PROFILE_FUNC();
    setDelay(getBaseDelay());
}

/************************************************************************
*                                                                       *
*  Оружие для атаки с дистанции (Range)                                 *
*                                                                       *
************************************************************************/

bool CItemWeapon::isThrowing()
{
	PROFILE_FUNC();
    return m_ranged && getSkillType() == SKILL_THR;
}

bool CItemWeapon::isRanged()
{
	PROFILE_FUNC();
    return m_ranged;
}

/************************************************************************
*                                                                       *
*  Двуручное оружие                                                     *
*                                                                       *
************************************************************************/

bool CItemWeapon::isTwoHanded()
{
	PROFILE_FUNC();
    return m_twoHanded;
}


/************************************************************************
*                                                                       *
*  get unlockable property                                              *
*                                                                       *
************************************************************************/

bool CItemWeapon::isUnlockable()
{
	PROFILE_FUNC();
    if(m_skillType == SKILL_NON) return false;

	return ( m_unlockId > 0 ? true : false );
}


/************************************************************************
*                                                                       *
*   Устанавливаем тип оружия и флаг isTwoHanded                         *
*                                                                       *
************************************************************************/

void CItemWeapon::setSkillType(uint8 skillType)
{
	PROFILE_FUNC();
    switch (skillType)
    {
	    case SKILL_GSD:
	    case SKILL_GAX:
	    case SKILL_SYH:
	    case SKILL_POL:
	    case SKILL_GKT:
	    case SKILL_STF:
            m_twoHanded = true;
		break;
        case SKILL_ARC:
        case SKILL_MRK:
        case SKILL_THR:
            m_ranged = true;
        break;
	}
	m_skillType = skillType;
}

uint8 CItemWeapon::getSkillType()
{
	PROFILE_FUNC();
	return m_skillType;
}

/************************************************************************
*                                                                       *
*   Set/get sub skillType.  Used for guns vs crossbows and other		*
*	exclusives									                        *
*                                                                       *
************************************************************************/

void CItemWeapon::setSubSkillType(uint8 subSkillType)
{
	PROFILE_FUNC();
	m_subSkillType = subSkillType;
}

uint8 CItemWeapon::getSubSkillType()
{
	PROFILE_FUNC();
	return m_subSkillType;
}

/************************************************************************
*																		*
*  Устанавливаем время задержки оружия. Сразу переводим значение в млс.	*
*  Все математические операции происходят с целыми числами, именно по	*
*  этому порядок действий очень важен, чтобы не потерять часть данных.	*
*																		*
************************************************************************/

void CItemWeapon::setDelay(uint16 delay)
{
	PROFILE_FUNC();
	m_delay = delay;
}

int16 CItemWeapon::getDelay()
{
	PROFILE_FUNC();
	return m_delay;
}

/************************************************************************
*																		*
*  Set/get the un-adjusted delay of the weapon							*
*  This is to fix delay adjustments of mobs and is not intended for		*
*  use outside of zoneutils/mobutils									*
*																		*
************************************************************************/

void CItemWeapon::setBaseDelay(uint16 delay)
{
	PROFILE_FUNC();
	m_baseDelay = delay;
}

int16 CItemWeapon::getBaseDelay()
{
	PROFILE_FUNC();
	return m_baseDelay;
}
/************************************************************************
*                                                                       *
*  get unlock id		                                                *
*                                                                       *
************************************************************************/

uint16 CItemWeapon::getUnlockId()
{
	PROFILE_FUNC();
	return m_unlockId;
}

/************************************************************************
*                                                                       *
*                                                                       *
*                                                                       *
************************************************************************/

void CItemWeapon::setDamage(uint16 damage)
{
	PROFILE_FUNC();
	m_damage = damage;
}

uint16 CItemWeapon::getDamage()
{
	PROFILE_FUNC();
	return m_damage;
}

/************************************************************************
*                                                                       *
*                                                                       *
*                                                                       *
************************************************************************/

void CItemWeapon::setDmgType(uint16 dmgType)
{
	PROFILE_FUNC();
	m_dmgType = dmgType;
}

uint16 CItemWeapon::getDmgType()
{
	PROFILE_FUNC();
	return m_dmgType;
}

/************************************************************************
*                                                                       *
*  Дополнительный урон от оружия (fire, water и т.д.)                   *
*                                                                       *
************************************************************************/

void CItemWeapon::setAdditionalEffect(uint8 effect)
{
	PROFILE_FUNC();
    m_effect = effect;
}

uint8 CItemWeapon::getAdditionalEffect()
{
	PROFILE_FUNC();
    return m_effect;
}


/************************************************************************
*                                                                       *
*  set unlockable property of weapon			                        *
*                                                                       *
************************************************************************/

void CItemWeapon::setUnlockable(uint16 unlockId)
{
	PROFILE_FUNC();
    m_unlockId = unlockId;
}

/************************************************************************
*                                                                       *
*  Максимально возможное количество ударов оружием                      *
*                                                                       *
************************************************************************/

void CItemWeapon::setMaxHit(uint8 hit)
{
	PROFILE_FUNC();
    m_maxHit = dsp_min(hit, 8);
}

/************************************************************************
*                                                                       *
*  Рассчет количества ударов                                            *
*                                                                       *
************************************************************************/

uint8 CItemWeapon::getHitCount()
{
	PROFILE_FUNC();
	return battleutils::getHitCount(m_maxHit);
}


//Blunt = MOD_HANDTOHAND, MOD_CLUB, MOD_STAFF
//Slashing = MOD_AXE, MOD_GREATAXE, MOD_GREATSWORD, MOD_SWORD, MOD_SCYTHE, MOD_KATANA, MOD_GREATKATANA
//Piercing = MOD_DAGGER, MOD_POLEARM, MOD_ARCHERY, MOD_MARKSMANSHIP

//Hand-to-Hand est un type de Blunt, qui est pourquoi MNK est efficace contre les Undead (Corse et Skeleton).
//Je ne sais pas ce que vous entendez par Impact et Range? MOD_THROWING pourrait aller dans aucun d'eux parce qu'il ya différents types d'armes.
//Par exemple, Boomerangs sont Blunt, Chakrams sont Slashing, et Shurikens sont Piercing.