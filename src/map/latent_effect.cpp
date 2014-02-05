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

#include "entities/battleentity.h"

#include "latent_effect.h"
#include "entities/charentity.h"

CLatentEffect::CLatentEffect(LATENT conditionsId, uint16 conditionsValue, uint8 slot, uint16 modValue, int16 modPower)
{
	PROFILE_FUNC();
    m_ConditionsID      = conditionsId;
    m_ConditionsValue   = conditionsValue;
    m_SlotID            = slot;
    m_ModValue          = modValue;
    m_ModPower          = modPower;
    m_Activated         = false;
}

CLatentEffect::~CLatentEffect()
{
	PROFILE_FUNC();
}

LATENT CLatentEffect::GetConditionsID()
{
	PROFILE_FUNC();
    return m_ConditionsID;
}

uint16 CLatentEffect::GetConditionsValue()
{
	PROFILE_FUNC();
    return m_ConditionsValue;
}

uint8 CLatentEffect::GetSlot()
{
	PROFILE_FUNC();
    return m_SlotID;
}

uint16 CLatentEffect::GetModValue()
{
	PROFILE_FUNC();
    return m_ModValue;
}

int16 CLatentEffect::GetModPower()
{
	PROFILE_FUNC();
    return m_ModPower;
}

bool CLatentEffect::IsActivated()
{
	PROFILE_FUNC();
    return m_Activated;
}

CBattleEntity* CLatentEffect::GetOwner()
{
	PROFILE_FUNC();
    return m_POwner;
}

void CLatentEffect::SetConditionsId(LATENT id)
{
	PROFILE_FUNC();
    m_ConditionsID = id;
}

void CLatentEffect::SetConditionsValue(uint16 value)
{
	PROFILE_FUNC();
    m_ConditionsValue = value;
}

void CLatentEffect::SetSlot(uint8 slot)
{
	PROFILE_FUNC();
    m_SlotID = slot;
}

void CLatentEffect::SetModValue(uint16 value)
{
	PROFILE_FUNC();
    m_ModValue = value;
}

void CLatentEffect::SetModPower(int16 power)
{
	PROFILE_FUNC();
    m_ModPower = power;
}

void CLatentEffect::Activate()
{
	PROFILE_FUNC();
    if( !IsActivated() )
    {
        //additional effect/dmg latents add mod to weapon, not player
        if (GetModValue() == MOD_ADDITIONAL_EFFECT || GetModValue() == MOD_DMG)
        {
            CCharEntity* PChar = (CCharEntity*)m_POwner;
            CItemWeapon* weapon = (CItemWeapon*)PChar->getStorage(LOC_INVENTORY)->GetItem(PChar->equip[GetSlot()]);

            weapon->addModifier(new CModifier(GetModValue(), GetModPower()));
        }
        else
        {
            m_POwner->addModifier(m_ModValue, m_ModPower);
        }

        m_Activated = true;
        //printf("LATENT ACTIVATED: %d, Current value: %d\n", m_ModValue, m_POwner->getMod(m_ModValue));
    }
}

void CLatentEffect::Deactivate()
{
	PROFILE_FUNC();
    if( IsActivated() )
    {
        //remove the modifier from weapon, not player
        if (GetModValue() == MOD_ADDITIONAL_EFFECT || GetModValue() == MOD_DMG)
        {
            CCharEntity* PChar = (CCharEntity*)m_POwner;
            CItemWeapon* weapon = (CItemWeapon*)PChar->getStorage(LOC_INVENTORY)->GetItem(PChar->equip[GetSlot()]);

            int16 modPower = GetModPower();

            if (weapon != NULL && (weapon->isType(ITEM_ARMOR) || weapon->isType(ITEM_WEAPON)))
            {
                if (GetModValue() == MOD_ADDITIONAL_EFFECT)
                {
                    for (uint8 i = 0; i < weapon->modList.size(); ++i)
                    {
                        //ensure the additional effect is fully removed from the weapon
                        if (weapon->modList.at(i)->getModID() == MOD_ADDITIONAL_EFFECT)
                        {
                            weapon->modList.at(i)->setModAmount(0);
                        }
                    }
                }
                else
                {
                    weapon->addModifier(new CModifier(GetModValue(), -modPower));
                }
            }

        }
        else
        {
            m_POwner->delModifier(m_ModValue, m_ModPower);
        }

        m_Activated = false;
        //printf("LATENT DEACTIVATED: %d\n", m_ModValue);
    }
}

void CLatentEffect::SetOwner(CBattleEntity* Owner)
{
	PROFILE_FUNC();
    m_POwner = Owner;
}
