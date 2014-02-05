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

#include "item.h"
#include "../../common/utils.h"

/************************************************************************
*                                                                       *
*                                                                       *
*                                                                       *
************************************************************************/

CItem::CItem(uint16 id)
{
	PROFILE_FUNC();
    m_id = id;
	
    m_subid      = 0;
    m_type       = 0;
    m_subtype    = 0;
    m_reserve    = 0;
    m_quantity   = 0;
    m_stackSize  = 0;
    m_BasePrice  = 0;
    m_CharPrice  = 0;
    m_ahCat      = 0;
    m_flag       = 0;
	m_wornItem	 = 0;
    m_sent       = false;

    m_slotID     = -1;
    m_locationID = -1;
}

CItem::~CItem()
{
	PROFILE_FUNC();
}

/************************************************************************
*                                                                       *
*  Уникальный номер предмета                                            *
*                                                                       *
************************************************************************/
	
void CItem::setID(uint16 id)
{
	PROFILE_FUNC();
	m_id = id;
}

uint16 CItem::getID()
{
	PROFILE_FUNC();
	return m_id;
}

/************************************************************************
*                                                                       *
*                                                                       *
*                                                                       *
************************************************************************/

void CItem::setSubID(uint16 subid)
{
	PROFILE_FUNC();
	m_subid = subid;
}

uint16 CItem::getSubID()
{
	PROFILE_FUNC();
	return m_subid;
}

/************************************************************************
*                                                                       *
*  Параметр, определяющий характеристики предмета                       *
*                                                                       *
************************************************************************/

void CItem::setFlag(uint16 flag)
{
	PROFILE_FUNC();
	m_flag = flag;
}

uint16 CItem::getFlag()
{
	PROFILE_FUNC();
	return m_flag;
}

/************************************************************************
*                                                                       *
*                                                                       *
*                                                                       *
************************************************************************/

void CItem::setAHCat(uint8 ahCat)
{
	PROFILE_FUNC();
	m_ahCat = ahCat;
}

uint8 CItem::getAHCat()
{
	PROFILE_FUNC();
	return m_ahCat;
}

/************************************************************************
*                                                                       *
*                                                                       *
*                                                                       *
************************************************************************/

void CItem::setType(uint8 type)
{
	PROFILE_FUNC();
	m_type |= type;
}

bool CItem::isType(ITEM_TYPE type)
{
	PROFILE_FUNC();
	return (m_type & type);
}

/************************************************************************
*                                                                       *
*                                                                       *
*                                                                       *
************************************************************************/

void CItem::setSubType(uint8 subtype)
{
	PROFILE_FUNC();
	m_subtype = (subtype > 128 ? m_subtype & subtype : m_subtype | subtype);
}

bool CItem::isSubType(ITEM_SUBTYPE subtype)
{
	PROFILE_FUNC();
	return (m_subtype & subtype);
}

/************************************************************************
*                                                                       *
*  Зарезервированное количество предметов в пачке                       *
*                                                                       *
************************************************************************/

void CItem::setReserve(uint32 reserve)
{
	PROFILE_FUNC();
    m_reserve = (reserve < m_quantity ? reserve : m_quantity);
}

uint32 CItem::getReserve()
{
	PROFILE_FUNC();
    return m_reserve;
}

/************************************************************************
*                                                                       *
*  Текущее количество предметов в пачке                                 *
*                                                                       *
************************************************************************/

void CItem::setQuantity(uint32 quantity)
{
	PROFILE_FUNC();
	m_quantity = (quantity < m_stackSize ? quantity : m_stackSize);
}

uint32 CItem::getQuantity()
{
	PROFILE_FUNC();
	return m_quantity;
}

/************************************************************************
*                                                                       *
*  Максимальное количество предметов в пачке                            *
*                                                                       *
************************************************************************/

void CItem::setStackSize(uint32 stackSize)
{
	PROFILE_FUNC();
	m_stackSize = stackSize;
}

uint32 CItem::getStackSize()
{
	PROFILE_FUNC();
	return m_stackSize;
}

/************************************************************************
*                                                                       *
*                                                                       *
*                                                                       *
************************************************************************/

void CItem::setBasePrice(uint32 BasePrice)
{
	PROFILE_FUNC();
	m_BasePrice = BasePrice;
}

uint32 CItem::getBasePrice()
{
	PROFILE_FUNC();
	return m_BasePrice;
}

/************************************************************************
*                                                                       *
*                                                                       *
*                                                                       *
************************************************************************/

void CItem::setCharPrice(uint32 CharPrice)
{
	PROFILE_FUNC();
    if (!(m_flag & ITEM_FLAG_EX)) m_CharPrice = CharPrice;
}

uint32 CItem::getCharPrice()
{
	PROFILE_FUNC();
    return m_CharPrice;
}

/************************************************************************
*                                                                       *
*  Название предмета                                                    *
*                                                                       *
************************************************************************/

const int8* CItem::getName()
{
	PROFILE_FUNC();
	return m_name.c_str();
}

void CItem::setName(int8* name)
{
	PROFILE_FUNC();
	m_name.clear();
	m_name.insert(0,name);
}

/************************************************************************
*                                                                       *
*                                                                       *
*                                                                       *
************************************************************************/

const int8* CItem::getSender()
{
	PROFILE_FUNC();
    return m_send.c_str();
}

void CItem::setSender(int8* sender)
{
	PROFILE_FUNC();
    m_send.clear();
    m_send.insert(0,sender);
}

/************************************************************************
*                                                                       *
*                                                                       *
*                                                                       *
************************************************************************/

const int8* CItem::getReceiver()
{
	PROFILE_FUNC();
    return m_recv.c_str();
}

void CItem::setReceiver(int8* receiver)
{
	PROFILE_FUNC();
    m_recv.clear();
    m_recv.insert(0,receiver);
}

/************************************************************************
*                                                                       *
*                                                                       *
*                                                                       *
************************************************************************/

const int8* CItem::getSignature()
{
	PROFILE_FUNC();
	return m_sign.c_str();
}

void CItem::setSignature(int8* signature)
{
	PROFILE_FUNC();
	m_sign.clear();
	m_sign.insert(0,signature);
}

/************************************************************************
*                                                                       *
*                                                                       *
*                                                                       *
************************************************************************/

uint8 CItem::getLocationID()
{
	PROFILE_FUNC();
	return m_locationID;
}

void CItem::setLocationID(uint8 locationID)
{
	PROFILE_FUNC();
	m_locationID = locationID;
}

/************************************************************************
*                                                                       *
*                                                                       *
*                                                                       *
************************************************************************/

uint8 CItem::getSlotID()
{
	PROFILE_FUNC();
	return m_slotID;
}
	
void CItem::setSlotID(uint8 slotID)
{
	PROFILE_FUNC();
	m_slotID = slotID;
}

/************************************************************************
*                                                                       *
*  Function for BCNM item of Maat Testimony                             *
*                                                                       *
************************************************************************/
	
void CItem::setWornItem(uint8 mode)
{
	PROFILE_FUNC();
	m_wornItem = mode;
}

uint8 CItem::getWornItem()
{
	PROFILE_FUNC();
	return m_wornItem;
}

/************************************************************************
*                                                                       *
*  Sent (via send/delivery box)                                         *
*                                                                       *
************************************************************************/
	
void CItem::setSent(bool sent)
{
	PROFILE_FUNC();
	m_sent = sent;
}

bool CItem::isSent()
{
	PROFILE_FUNC();
	return m_sent;
}