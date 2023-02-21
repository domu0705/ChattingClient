// Fill out your copyright notice in the Description page of Project Settings.


#include "ChattingClientManager.h"
#include "UserWidgetManager.h"
#include "SocketManager.h"

UChattingClientManager::UChattingClientManager()
{
}

UChattingClientManager::~UChattingClientManager()
{
}

void  UChattingClientManager::SetSocket(USocketManager* socketManager)
{
	if (socketManager)
	{
		UE_LOG(LogTemp, Log, TEXT("SetSocket success @@@@@@@@@@@@@@"));
		SocketManager = socketManager;
	}
}


void  UChattingClientManager::SetUserWidgetManager(UUserWidgetManager* userWidgettManager)
{
	UserWidgetManager = userWidgettManager;
}


USocketManager* UChattingClientManager::GetSocket()
{
	return SocketManager;
}
/*
UUserWidgetManager* UChattingClientManager::GetUserWidgetManager()
{
	return UserWidgetManager;
}
*/