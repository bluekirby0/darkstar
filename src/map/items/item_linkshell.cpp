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

#include "../../common/socket.h"

#include "item_linkshell.h"


CItemLinkshell::CItemLinkshell(uint16 id) : CItem(id)
{
	PROFILE_FUNC();
	setType(ITEM_LINKSHELL);

    m_LinkshellID = 0;

	WBUFW(&m_LSColor,0) = 0;
}

CItemLinkshell::~CItemLinkshell()
{
	PROFILE_FUNC();
}

uint32 CItemLinkshell::GetLSID()
{
	PROFILE_FUNC();
    return m_LinkshellID;
}

void CItemLinkshell::SetLSID(uint32 lsid)
{
	PROFILE_FUNC();
    m_LinkshellID = lsid;
}

LSTYPE CItemLinkshell::GetLSType()
{
	PROFILE_FUNC();
    return (LSTYPE)(getID() - 0x200);
}

lscolor_t CItemLinkshell::GetLSColor()
{
	PROFILE_FUNC();
	return m_LSColor;
}

uint16 CItemLinkshell::GetLSRawColor()
{
	PROFILE_FUNC();
    return RBUFW(&m_LSColor,0);
}

void CItemLinkshell::SetLSColor(uint16 color)
{
	PROFILE_FUNC();
	WBUFW(&m_LSColor,0) = color;
}