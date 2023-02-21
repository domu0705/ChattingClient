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

	TArray<uint8> msg;
	FTCHARToUTF8 Converter(*string);
	msg.Append((uint8*)Converter.Get(), Converter.Length());

	int32 ByteSent = 0;
	bool IsSended = socket->Send(msg.GetData(), msg.Num(), ByteSent);

	if (IsSended)
	{
		UE_LOG(LogTemp, Log, TEXT("Sended Message: %s"), *string);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to send message"));
	}
}

void USocketManager::SendLogin(const FString& name)
{
	FString command = FString::Printf(TEXT("LOGIN %s\r\n"), *name);
	Send(command);
}


bool USocketManager::ConnectServer()
{
	socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(TEXT("Stream"), TEXT("Client Socket"));
	FString address = TEXT("127.0.0.1");
	FIPv4Address ip;
	FIPv4Address::Parse(address, ip);

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(port);

	if (socket->Connect(*addr)) {
		isConnected = true;
		return true;
	}
	else
	{
		return false;
	}

}

int USocketManager::WideCharToMBT(char* to, wchar_t* from)
{
	int len = WideCharToMultiByte(CP_ACP, 0, from, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, from, -1, to, len, NULL, NULL);
	return len;
}