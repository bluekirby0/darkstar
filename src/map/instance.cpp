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

#include "instance.h"

#include "../common/timer.h"
#include "entities/charentity.h"
#include "entities/mobentity.h"
#include "entities/baseentity.h"
#include "packets/fade_out.h"
#include "packets/entity_update.h"
#include "packets/position.h"
#include "packets/message_basic.h"
#include "lua/luautils.h"
#include "utils/zoneutils.h"


CInstance::CInstance(CInstanceHandler* hand, uint16 id, INSTANCETYPE type){
	PROFILE_FUNC();
	m_Type = type;
	m_BcnmID = id;
	m_Handler = hand;
	locked = false;
	m_FastestTime = 3600;
	m_DynaUniqueID = 0;
	treasureChestSpawned = false;
	fightTick = 0;
	m_entrance = 0;
}

uint16 CInstance::getID(){
	PROFILE_FUNC();
	return m_BcnmID;
}

uint8 CInstance::getInstanceNumber(){
	PROFILE_FUNC();
	return m_InstanceNumber;
}

uint32 CInstance::getTimeLimit(){
	PROFILE_FUNC();
	return m_TimeLimit;
}

INSTANCETYPE CInstance::getType()
{
	PROFILE_FUNC();
	return m_Type;
}

uint16 CInstance::getZoneId(){
	PROFILE_FUNC();
	return m_ZoneID;
}

uint8 CInstance::getMaxParticipants(){
	PROFILE_FUNC();
	return m_MaxParticipants;
}

uint8 CInstance::getMaxPlayerInBCNM(){
	PROFILE_FUNC();
	return m_PlayerList.size();
}

uint8 CInstance::getLevelCap(){
	PROFILE_FUNC();
	return m_LevelCap;
}

uint16 CInstance::getLootId(){
	PROFILE_FUNC();
	return m_LootId;
}

uint32 CInstance::getStartTime(){
	PROFILE_FUNC();
	return m_StartTime;
}

uint32 CInstance::getDeadTime(){
	PROFILE_FUNC();
	return m_AllDeadTime;
}

const int8* CInstance::getBcnmName(){
	PROFILE_FUNC();
	return m_name.c_str();
}

uint8 CInstance::getEntrance(){
	PROFILE_FUNC();
	return m_entrance;
}

void CInstance::setBcnmName(int8* name){
	PROFILE_FUNC();
	m_name.clear();
	m_name.insert(0,name);
}

void CInstance::setTimeLimit(uint32 time){
	PROFILE_FUNC();
	m_TimeLimit = time;
}

void CInstance::setDeadTime(uint32 time){
	PROFILE_FUNC();
	m_AllDeadTime = time;
}

void CInstance::setInstanceNumber(uint8 instance){
	PROFILE_FUNC();
	m_InstanceNumber = instance;
}

void CInstance::setZoneId(uint16 zone){
	PROFILE_FUNC();
	m_ZoneID = zone;
}

void CInstance::setMaxParticipants(uint8 max){
	PROFILE_FUNC();
	m_MaxParticipants = max;
}

void CInstance::setLevelCap(uint8 cap){
	PROFILE_FUNC();
	m_LevelCap = cap;
}

void CInstance::setLootId(uint16 id){
	PROFILE_FUNC();
	m_LootId = id;
}

void CInstance::setEntrance(uint8 entrance){
	PROFILE_FUNC();
	m_entrance = entrance;
}

//========================PLAYER FUNCTIONS=============================================//

void CInstance::enableSubJob(){
	PROFILE_FUNC();
	if(m_PlayerList.size()==0){
		ShowWarning("instance:enableSubjob - No players in battlefield!\n");
		return;
	}
	for(int i=0; i<m_PlayerList.size(); i++){
		m_PlayerList.at(i)->StatusEffectContainer->DelStatusEffectsByFlag(EFFECT_SJ_RESTRICTION);
	}
}

void CInstance::disableSubJob(){
	PROFILE_FUNC();
	if(m_PlayerList.size()==0){
		ShowWarning("instance:disableSubjob - No players in battlefield!\n");
		return;
	}
	for(int i=0; i<m_PlayerList.size(); i++){
		m_PlayerList.at(i)->StatusEffectContainer->AddStatusEffect(new CStatusEffect(EFFECT_SJ_RESTRICTION,0,m_PlayerList.at(i)->GetSJob(),0,0),true);
	}
}

uint8 CInstance::getPlayerMainJob(){
	PROFILE_FUNC();
	if(m_PlayerList.size()==0){
		ShowWarning("instance:getPlayerMainJob - No players in battlefield!\n");
		return 1;
	}
	return m_PlayerList.at(0)->GetMJob();
}

uint8 CInstance::getPlayerMainLevel(){
	PROFILE_FUNC();
	if(m_PlayerList.size()==0){
		ShowWarning("instance:getPlayerMainLevel - No players in battlefield!\n");
		return 1;
	}
	return m_PlayerList.at(0)->GetMLevel();
}

void CInstance::capPlayerToBCNM(){ //adjust player's level to the appropriate cap and remove buffs
	PROFILE_FUNC();
	if(m_PlayerList.size()==0){
		ShowWarning("instance:getPlayerMainLevel - No players in battlefield!\n");
		return;
	}
	uint8 cap = getLevelCap();
	if(cap != 0)
	{
		for(int i=0; i<m_PlayerList.size(); i++)
		{
			m_PlayerList.at(i)->StatusEffectContainer->DelStatusEffectsByFlag(EFFECTFLAG_DISPELABLE);
			m_PlayerList.at(i)->StatusEffectContainer->DelStatusEffectsByFlag(EFFECTFLAG_ON_ZONE);
			m_PlayerList.at(i)->StatusEffectContainer->AddStatusEffect(new CStatusEffect(EFFECT_LEVEL_RESTRICTION,0,cap,0,0),true);
		}
	}
}


bool CInstance::isPlayerInBcnm(CCharEntity* PChar){
	PROFILE_FUNC();
	for(int i=0; i<m_PlayerList.size(); i++){
		if(PChar->id == m_PlayerList.at(i)->id){
			return PChar->m_insideBCNM;
		}
	}
	return false;
}

void CInstance::pushMessageToAllInBcnm(uint16 msg, uint16 param){
	PROFILE_FUNC();
	for(int i=0; i<m_PlayerList.size(); i++){
		if(m_PlayerList.at(i)->m_lastBcnmTimePrompt != param){
			m_PlayerList.at(i)->pushPacket(new CMessageBasicPacket(m_PlayerList.at(i),m_PlayerList.at(i),param,0,msg));
			m_PlayerList.at(i)->m_lastBcnmTimePrompt = param;
		}
	}
}

bool CInstance::addPlayerToBcnm(CCharEntity* PChar){
	PROFILE_FUNC();
	//split to get the reason for debugging
	if(m_PlayerList.size() >= m_MaxParticipants){
		ShowDebug("Cannot add %s to BCNM list, max size reached.\n",PChar->GetName());return false;
	}
	if(PChar->StatusEffectContainer->HasStatusEffect(EFFECT_BATTLEFIELD)){
		ShowDebug("Cannot add %s to BCNM list, they have BC effect.\n",PChar->GetName());return false;
	}
	if(PChar->getZone() != m_ZoneID){
		ShowDebug("Cannot add %s to BCNM list, not in right zone.\n",PChar->GetName());return false;
	}

	m_PlayerList.push_back(PChar);
	PChar->StatusEffectContainer->AddStatusEffect(new CStatusEffect(EFFECT_BATTLEFIELD,EFFECT_BATTLEFIELD,this->m_BcnmID,0,0),true);
	this->capPlayerToBCNM();
	return true;
}

bool CInstance::delPlayerFromBcnm(CCharEntity* PChar){
	PROFILE_FUNC();
	for(int i=0; i<m_PlayerList.size(); i++){
		if(m_PlayerList.at(i)->id == PChar->id){
			PChar->m_insideBCNM = false;
			PChar->StatusEffectContainer->DelStatusEffectSilent(EFFECT_SJ_RESTRICTION);
			PChar->StatusEffectContainer->DelStatusEffectSilent(EFFECT_BATTLEFIELD);
			PChar->StatusEffectContainer->DelStatusEffectSilent(EFFECT_LEVEL_RESTRICTION);
			PChar->PBattleAI->SetCurrentAction(ACTION_DISENGAGE);
			clearPlayerEnmity(PChar);
			m_PlayerList.erase(m_PlayerList.begin()+i);
			return true;
		}
	}
	return false;
}

bool CInstance::enterBcnm(CCharEntity* PChar){
	PROFILE_FUNC();
	for(int i=0; i<m_PlayerList.size(); i++){
		if(m_PlayerList.at(i)->id == PChar->id){
			if(PChar->m_insideBCNM){ShowWarning("%s is already inside a BCNM!\n",PChar->GetName());}
			PChar->m_insideBCNM = true;
			ShowDebug("Entered ID %i Instance %i \n",this->m_BcnmID,this->m_InstanceNumber);
			//callback to lua
			luautils::OnBcnmEnter(PChar,this);
			return true;
		}
	}
	return false;
}

bool CInstance::isValidPlayerForBcnm(CCharEntity* PChar){
	PROFILE_FUNC();
	for(int i=0; i<m_PlayerList.size(); i++){
		if(PChar->id == m_PlayerList.at(i)->id){
			return true;
		}
	}
	return false;
}

bool CInstance::allPlayersDead(){
	PROFILE_FUNC();
	if(m_PlayerList.size()==0){ShowWarning("instance:allPlayersDead : No players in list!\n");}

	for(int i=0; i<m_PlayerList.size();i++){
		if(!m_PlayerList.at(i)->isDead()){
			return false;
		}
	}
	return true;
}

//==================BCNM FUNCTIONS=====================================================//

void CInstance::lockBcnm(){
	PROFILE_FUNC();
	for(int i=0; i<m_PlayerList.size(); i++){
		if(!m_PlayerList.at(i)->m_insideBCNM){
			ShowDebug("Removing %s from the valid players list for BCNMID %i Instance %i \n",m_PlayerList.at(i)->GetName(),
				this->m_BcnmID,this->m_InstanceNumber);
			if(this->delPlayerFromBcnm(m_PlayerList.at(i))){i--;}
		}
	}
}

void CInstance::init(){
	PROFILE_FUNC();
	//reload from sql
	instanceutils::spawnMonstersForBcnm(this);
	m_StartTime = gettick();
	m_AllDeadTime = 0;
}

void CInstance::addEnemy(CMobEntity* PMob, uint8 condition){
	PROFILE_FUNC();
	m_EnemyList.push_back(PMob);
	if (condition & CONDITION_WIN_REQUIREMENT)
	{
		MobVictoryCondition_t mobCondition = {PMob, false};
		m_EnemyVictoryList.push_back(mobCondition);
	}
}

void CInstance::addNpc(CBaseEntity* PNpc){
	PROFILE_FUNC();
	m_NpcList.push_back(PNpc);
}

bool CInstance::allEnemiesDefeated(){
	PROFILE_FUNC();
	bool allDefeated = true;
	for(int i=0; i<m_EnemyVictoryList.size(); i++){
		if(m_EnemyVictoryList.at(i).MobEntity->PBattleAI->GetCurrentAction() >= 20 && m_EnemyVictoryList.at(i).MobEntity->PBattleAI->GetCurrentAction() <= 23){
			m_EnemyVictoryList.at(i).killed = true;
		}
		if(m_EnemyVictoryList.at(i).killed == false){
			allDefeated = false;
		}
	}
	return allDefeated;
}

bool CInstance::isPlayersFighting(){
	PROFILE_FUNC();
	for(int i=0; i<m_EnemyList.size(); i++){
		if(m_EnemyList.at(i)->PEnmityContainer->GetHighestEnmity() != NULL){
			return true;
		}
	}
	return false;
}

bool CInstance::isReserved(){
	PROFILE_FUNC();
	if(m_PlayerList.size()>0){return true;}
	return false;
}

void CInstance::cleanup(){
	PROFILE_FUNC();
	ShowDebug("bcnm cleanup id:%i inst:%i \n",this->getID(),this->getInstanceNumber());
	//wipe enmity from all mobs in list if needed
	for(int i=0; i<m_EnemyList.size(); i++){
		m_EnemyList.at(i)->PBattleAI->SetCurrentAction(ACTION_DESPAWN);
	}
	//wipe mob list
	m_EnemyList.clear();

	//make chest vanish (if any)
	for(int i=0; i<m_NpcList.size(); i++){
		m_NpcList.at(i)->loc.zone->PushPacket(m_NpcList.at(i), CHAR_INRANGE, new CFadeOutPacket(m_NpcList.at(i)));
		m_NpcList.at(i)->animation = ANIMATION_DEATH;
		m_NpcList.at(i)->status = STATUS_UPDATE;
		m_NpcList.at(i)->loc.zone->PushPacket(m_NpcList.at(i), CHAR_INRANGE, new CEntityUpdatePacket(m_NpcList.at(i), ENTITY_UPDATE));
	}
	//wipe npc list
	m_NpcList.clear();

	locked = false;
	//delete instance
	if(m_Handler==NULL){
		ShowError("Instance handler is NULL from Instance BCNM %i Inst %i \n",m_BcnmID,m_InstanceNumber);
	}

	m_Handler->wipeInstance(this);
	delete this;
}

void CInstance::beforeCleanup(){
	PROFILE_FUNC();
	if(!(m_RuleMask & RULES_ALLOW_SUBJOBS)){
		// enable subjob
		enableSubJob();
	}
}

bool CInstance::winBcnm(){
	PROFILE_FUNC();
	beforeCleanup();
	for(int i=0; i<m_PlayerList.size(); i++){
		luautils::OnBcnmLeave(m_PlayerList.at(i),this,LEAVE_WIN);
		if(this->delPlayerFromBcnm(m_PlayerList.at(i))){i--;}
	}
	cleanup();
	return true;
}

bool CInstance::spawnTreasureChest(){
	PROFILE_FUNC();
	instanceutils::spawnTreasureForBcnm(this);
	return true;
}

void CInstance::OpenChestinBcnm(){
	PROFILE_FUNC();
	instanceutils::getChestItems(this);
}

/* apparently not used in bcnm
void CInstance::getHighestTHforBcnm(){
	instanceutils::getHighestTHforBcnm(this);
}*/

bool CInstance::loseBcnm(){
	PROFILE_FUNC();
	beforeCleanup();
	for(int i=0; i<m_PlayerList.size(); i++){
		luautils::OnBcnmLeave(m_PlayerList.at(i),this,LEAVE_LOSE);
		if(this->delPlayerFromBcnm(m_PlayerList.at(i))){i--;}
	}

	cleanup();
	return true;
}

bool CInstance::isEnemyBelowHPP(uint8 hpp){
	PROFILE_FUNC();
	for(int i=0; i<m_EnemyList.size(); i++){
		if(m_EnemyList.at(i)->GetHPP()>hpp){
			return false;
		}
	}
	return true;
}

//========================DYNAMIS FUNCTIONS=============================================//

//Create dynamis unique ID for player can't cheat by leaving a dynamis before the end and enter the next
void CInstance::setDynaUniqueID(){
	PROFILE_FUNC();
	m_DynaUniqueID = m_BcnmID + m_StartTime;
	printf("uniqueid core: %u",m_DynaUniqueID);
}

uint16 CInstance::getDynaUniqueID(){
	PROFILE_FUNC();
	return m_DynaUniqueID;
}

//Add player to dynamis
bool CInstance::addPlayerToDynamis(CCharEntity* PChar){
	PROFILE_FUNC();
	//split to get the reason for debugging
	if(m_PlayerList.size() >= m_MaxParticipants){
		ShowDebug("Cannot add %s to Dynamis list, max size reached.\n",PChar->GetName());return false;
	}
	if(PChar->StatusEffectContainer->HasStatusEffect(EFFECT_DYNAMIS, 0) || PChar->StatusEffectContainer->HasStatusEffect(EFFECT_BATTLEFIELD)){
		ShowDebug("Cannot add %s to Dynamis list, they have BC effect.\n",PChar->GetName());return false;
	}
	if(PChar->getZone() != m_ZoneID){
		ShowDebug("Cannot add %s to Dynamis list, not in right zone.\n",PChar->GetName());return false;
	}

	m_PlayerList.push_back(PChar);
	PChar->StatusEffectContainer->AddStatusEffect(new CStatusEffect(EFFECT_DYNAMIS,0,this->m_BcnmID,0,0),true);
	return true;
}

//Add time on dynamis instance
void CInstance::addTimeLimit(uint32 time){
	PROFILE_FUNC();
	m_TimeLimit += time;
}

bool CInstance::finishDynamis(){
	PROFILE_FUNC();
	for(int i=0; i<m_PlayerList.size(); i++){
		luautils::OnBcnmLeave(m_PlayerList.at(i),this,LEAVE_LOSE);
		if(this->delPlayerFromDynamis(m_PlayerList.at(i))){i--;}
	}

	cleanupDynamis();
	return true;
}

void CInstance::cleanupDynamis(){
	PROFILE_FUNC();
	ShowDebug("Dynamis cleanup id:%i \n",this->getID());

	//get all mob of this dyna zone
	const int8* fmtQuery = "SELECT msp.mobid \
						    FROM mob_spawn_points msp \
							LEFT JOIN mob_groups mg ON mg.groupid = msp.groupid \
							WHERE zoneid = %u";

	int32 ret = Sql_Query(SqlHandle, fmtQuery, this->getZoneId());

	if (ret == SQL_ERROR || Sql_NumRows(SqlHandle) == 0) {
		ShowError("Dynamis cleanup : SQL error - Cannot find any ID for Dyna %i \n",this->getID());
	}else{
		while(Sql_NextRow(SqlHandle) == SQL_SUCCESS)
		{
			uint32 mobid = Sql_GetUIntData(SqlHandle,0);
			CMobEntity* PMob = (CMobEntity*)zoneutils::GetEntity(mobid, TYPE_MOB);

			if(PMob != NULL)
				PMob->PBattleAI->SetCurrentAction(ACTION_FADE_OUT);
		}
	}

	//wipe mob list
	m_EnemyList.clear();
	m_MobList.clear();

	//delete instance
	if(m_Handler==NULL){
		ShowError("Instance handler is NULL from Dynamis Instance %i \n",m_BcnmID);
	}
	m_Handler->wipeInstance(this);
	delete this;
}

bool CInstance::delPlayerFromDynamis(CCharEntity* PChar){
	PROFILE_FUNC();
	for(int i=0; i<m_PlayerList.size(); i++){
		if(m_PlayerList.at(i)->id == PChar->id){
			PChar->m_insideBCNM = false;
			PChar->StatusEffectContainer->DelStatusEffectSilent(EFFECT_DYNAMIS);
			PChar->PBattleAI->SetCurrentAction(ACTION_DISENGAGE);
			m_PlayerList.erase(m_PlayerList.begin()+i);
			return true;
		}
	}
	return false;
}

void CInstance::addMonsterInList(CMobEntity* PMob)
{
	PROFILE_FUNC();
	m_MobList.push_back(PMob);
}

bool CInstance::isMonsterInList(CMobEntity* PMob)
{
	PROFILE_FUNC();
	for(int i=0; i < m_MobList.size(); i++)
	{
		if(PMob->id == m_MobList.at(i)->id)
		{
			return true;
		}
	}
	return false;
}

void CInstance::clearPlayerEnmity(CCharEntity* PChar)
{
	PROFILE_FUNC();
	for (std::vector<CMobEntity*>::iterator it = m_MobList.begin() ; it != m_MobList.end(); ++it)
	{
		CMobEntity* PMob = *it;

		PMob->PEnmityContainer->Clear(PChar->id);
	}
}