// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
/**
 * 
 */
class CHATTINGCLIENT_API USocketManager
{

private:
	FSocket* socket;
	int32 port;

public:
	static USocketManager* GetInstance() {
		static USocketManager s;
		return &s;
	}

	bool isConnected;
	USocketManager();
	~USocketManager();

	bool ConnectServer();
	void Send(FString& string);
	void SendLogin(const FString& name);
	int WideCharToMBT(char* from, wchar_t* to);

protected:
};
