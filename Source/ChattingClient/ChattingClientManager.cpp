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

	UE_LOG(LogTemp, Log, TEXT("SetSocket success @@@@@@@@@@@@@@"));
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

	UE_LOG(LogTemp, Log, TEXT("@@@ UChattingClientManager::SetPlayerInfo() | playerInfo"));
	PlayerInfo = playerInfo;
}

UPlayerInfo* UChattingClientManager::GetPlayerInfo()
{
	return PlayerInfo;
}

/*
UUserWidgetManager* UChattingClientManager::GetUserWidgetManager()
{
	return UserWidgetManager;
}
*/