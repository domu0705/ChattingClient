// Fill out your copyright notice in the Description page of Project Settings.
//안되면 actor class 상속받기.

#include "SocketManager.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include "Engine.h"
#include "Runtime/Networking/Public/Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Internationalization/Text.h"

USocketManager::USocketManager()
{
	port = 1112;
}

USocketManager::~USocketManager()
{

}

void USocketManager::Send(FString& string)
{
	setlocale(LC_ALL, "korean");
	string += "\r\n";

	char c[1024];

	TArray<uint8> msg;
	wchar_t* da = string.GetCharArray().GetData();
	int len = wcstombs(c, da, 1024);
	for (int i = 0; i < len; i++)
	{
		msg.Add(c[i]);
	}

	int32 sendingByte = 0;
	bool IsSended = socket->Send(msg.GetData(), msg.Num(), sendingByte);

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

//actor에 존재하는 tick이 실행될때마다 이것도 함께 실행됨

void USocketManager::Tick()
{
	uint32 pendingSize = 0;
	if (!isConnected || !(socket->HasPendingData(pendingSize)))
		return;
	
	int curRecvBytes = 0;
	bool isReceived = socket->Recv(buffer + recvBytes, BUFFER_SIZE - recvBytes, curRecvBytes);

	if (isReceived)
	{
		recvBytes += curRecvBytes;
		UE_LOG(LogTemp, Log, TEXT("recvBytes %d"), recvBytes);

		if (curRecvBytes <= 0)
		{
			memset(buffer, 0, BUFFER_SIZE);
			recvBytes = 0;
			UE_LOG(LogTemp, Log, TEXT("curRecvBytes <= 0"));
			return;
		}


		//한글 받아지는 변환
		FString recvStr = FString(UTF8_TO_TCHAR((const ANSICHAR*)buffer));

		// Log the received string
		UE_LOG(LogTemp, Log, TEXT("@@ReceivedString: %s"), *recvStr);


		if (recvStr.Contains("\r\n") == true)
		{
			TArray<FString> lines;
			recvStr.ParseIntoArray(lines, TEXT("\r\n"));
			if (lines.Num() > 0)
			{
				for (const FString& line : lines)
				{
					//HandleRecv(line);
					UE_LOG(LogTemp, Log, TEXT("Recv lines"));

				}
			}
		}
		memset(buffer, 0, BUFFER_SIZE);
		recvBytes = 0;
	}
}

/*
int USocketManager::WideCharToMBT(char* to, wchar_t* from)
{
	int len = WideCharToMultiByte(CP_ACP, 0, from, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, from, -1, to, len, NULL, NULL);
	return len;
}*/