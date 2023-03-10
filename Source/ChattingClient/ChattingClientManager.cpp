// Fill out your copyright notice in the Description page of Project Settings.


#include "ChattingClientManager.h"
#include "UserWidgetManager.h"
#include "SocketManager.h"
#include "PlayerInfo.h"


UChattingClientManager::UChattingClientManager()
{
}

UChattingClientManager::~UChattingClientManager()
{
}

void  UChattingClientManager::SetSocket(USocketManager* socketManager)
{
	if (!socketManager)
		return;
	SocketManager = socketManager;
}


void  UChattingClientManager::SetUserWidgetManager(UUserWidgetManager* userWidgettManager)
{
	UserWidgetManager = userWidgettManager;
}

USocketManager* UChattingClientManager::GetSocket()
{
	return SocketManager;
}

void  UChattingClientManager::SetPlayerInfo(UPlayerInfo* playerInfo)
{
	if (!playerInfo)
		return;
	PlayerInfo = playerInfo;
}

UPlayerInfo* UChattingClientManager::GetPlayerInfo()
{
	return PlayerInfo;
}
