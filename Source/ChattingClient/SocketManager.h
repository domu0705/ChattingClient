// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInfo.h"
#include "UserWidgetManager.h"
#include "ChattingClientManager.h"
#include "UObject/NoExportTypes.h"
#include "Engine.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include <locale.h>


class CHATTINGCLIENT_API USocketManager
{
	enum 
	{ 
		BUFFER_SIZE = 2048, 
		PORT = 1112
	};

private:
	FSocket* socket;
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

	void Tick();
	bool ConnectServer();
	void Send(FString& string);
	void SendLogin(const FString& name);
	void SendRoomList();
	void SendRoomChat(const FString& chat);
	void SendUserList();
	void SendJoinRoom(const FString& name);
	void SendQuitRoom();
	void SendDeleteRoom();
	void SendQuitSystem();
	void SendCreateRoom(const FString& num, const FString& name);
	void SendPrivateMsg(const FString& name, const FString& msg);
	void SendRoomInfo(const FString& num);
	void SendUserInfo(const FString& name);
	void CheckRecvMsg(FString& recvStr, FString& str1);
};
