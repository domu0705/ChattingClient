// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UUserWidgetManager;
class USocketManager;

class CHATTINGCLIENT_API UChattingClientManager
{
public:
	UChattingClientManager();
	~UChattingClientManager();
	
	static UChattingClientManager* GetInstance() {
		static UChattingClientManager s;
		return &s;
	}
	

	void SetSocket(USocketManager* socketManager);
	USocketManager* GetSocket();

	void SetUserWidgetManager(UUserWidgetManager* userWidgetManager);
	//UUserWidgetManager* GetUserWidgetManager();

private:
	static UChattingClientManager* ChattingClientManager;

	UUserWidgetManager* UserWidgetManager;
	USocketManager* SocketManager;

};
