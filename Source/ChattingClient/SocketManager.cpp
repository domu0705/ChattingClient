// Fill out your copyright notice in the Description page of Project Settings.
//안되면 actor class 상속받기.

#include "SocketManager.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include "Engine.h"
#include "Runtime/Networking/Public/Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

USocketManager::USocketManager()
{
	port = 1112;
}

USocketManager::~USocketManager()
{

}

void USocketManager::Send(FString& string)
{
	string += "\r\n";

	//int size = ;
	//int sent = ;


	const char* result = TCHAR_TO_ANSI(*string);
	int32 sendedBytes = 0;
	uint8_t slidePressure = (uint8_t)atoi(result);
	socket->Send( &slidePressure, string.Len(), sendedBytes);//uint8= 음수가 아닌, 8bit로 표현 가능한 숫자
	//Socket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent);
}

void USocketManager::SendLogin(const FString& name)
{
	FString command = FString::Printf(TEXT("LOGIN %s\r\n"), *name);
	Send(command);
}


bool USocketManager::ConnectServer()
{
	FSocket* socketTmp = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(TEXT("Stream"), TEXT("Client Socket"));
	FString address = TEXT("127.0.0.1");
	FIPv4Address ip;
	FIPv4Address::Parse(address, ip);

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(port);

	if (socketTmp->Connect(*addr)) {
		isConnected = true;
		socket = socketTmp;
		return true;
	}
	else
	{
		return false;
	}

}