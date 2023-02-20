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
class CHATTINGCLIENT_API ConnSocket
{

private:
	FSocket* socket;
	int port;

public:
	ConnSocket();
	~ConnSocket();

	void ConnectServer();
	void Send(FString& string);
	void SendLogin(const FString& name);

protected:
	bool isConnected;
};
