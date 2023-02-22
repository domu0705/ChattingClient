// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include <locale.h>//for setlocale
/**
 * 
 */
class CHATTINGCLIENT_API USocketManager
{
	enum { BUFFER_SIZE = 2048 };

private:
	FSocket* socket;
	int32 port;
	uint8 buffer[BUFFER_SIZE] = { 0 };
	int recvBytes = 0;
public:
	static USocketManager* GetInstance() {
		static USocketManager s;
		return &s;
	}

	bool isConnected;
	USocketManager();
	~USocketManager();

	//void Tick();
	bool ConnectServer();
	void Send(FString& string);
	void SendLogin(const FString& name);
	int WideCharToMBT(char* from, wchar_t* to);

};
