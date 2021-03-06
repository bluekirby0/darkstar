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

#include "item_puppet.h"

CItemPuppet::CItemPuppet(uint16 id) : CItem(id)
{
	PROFILE_FUNC();
	setType(ITEM_PUPPET);
}

CItemPuppet::~CItemPuppet()
{
	PROFILE_FUNC();
}

uint8 CItemPuppet::getEquipSlot()
{
	PROFILE_FUNC();
    return m_equipSlot;
}
void CItemPuppet::setEquipSlot(uint32 slot)
{
	PROFILE_FUNC();
    m_equipSlot = slot;
}
uint32 CItemPuppet::getElementSlots()
{
	PROFILE_FUNC();
    return m_elementSlots;
}
void CItemPuppet::setElementSlots(uint32 slots)
{
	PROFILE_FUNC();
    m_elementSlots = slots;
}