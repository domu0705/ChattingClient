// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


class UUserWidgetManager;
class USocketManager;
class UPlayerInfo;


class CHATTINGCLIENT_API UChattingClientManager
{
private:
	static UChattingClientManager* ChattingClientManager;

	UUserWidgetManager* UserWidgetManager;
	USocketManager* SocketManager;
	UPlayerInfo* PlayerInfo;

public:
	UChattingClientManager();
	~UChattingClientManager();
	
	static UChattingClientManager* GetInstance() {
		static UChattingClientManager s;
		return &s;
	}

	void SetSocket(USocketManager* socketManager);
	USocketManager* GetSocket();
	void SetPlayerInfo(UPlayerInfo* playerInfo);
	UPlayerInfo* GetPlayerInfo();
	void SetUserWidgetManager(UUserWidgetManager* userWidgetManager);
};
