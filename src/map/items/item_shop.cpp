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

#include "item_shop.h"


CItemShop::CItemShop(uint16 id) : CItem(id)
{
	PROFILE_FUNC();
	// SetType(ITEM_SHOP);

	m_MinPrice = 0;
	m_MaxPrice = 0;

	m_DailyIncrease = false;
}

CItemShop::~CItemShop()
{
	PROFILE_FUNC();
}

uint32 CItemShop::getMinPrice()
{
	PROFILE_FUNC();
	return m_MinPrice;
}


uint32 CItemShop::getMaxPrice()
{
	PROFILE_FUNC();
	return m_MaxPrice;
}

bool CItemShop::IsInMenu()
{
	PROFILE_FUNC();
    return getQuantity() != 0;
}

bool CItemShop::IsDailyIncrease()
{
	PROFILE_FUNC();
	return m_DailyIncrease;
}

void CItemShop::setMinPrice(uint32 price)
{
	PROFILE_FUNC();
	m_MinPrice = price;
}

void CItemShop::setMaxPrice(uint32 price)
{
	PROFILE_FUNC();
	m_MaxPrice = price;
}

void CItemShop::setDailyIncrease(uint16 increase)
{
	PROFILE_FUNC();
    m_DailyIncrease = increase;
}

uint16 CItemShop::getDailyIncrease()
{
	PROFILE_FUNC();
    return m_DailyIncrease;
}

void CItemShop::setInitialQuantity(uint16 increase)
{
	PROFILE_FUNC();
    m_InitialQuantity = increase;
}

uint16 CItemShop::getInitialQuantity()
{
	PROFILE_FUNC();
    return m_InitialQuantity;
}