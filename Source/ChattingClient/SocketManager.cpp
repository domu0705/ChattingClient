// Fill out your copyright notice in the Description page of Project Settings.
//안되면 actor class 상속받기.

#include "SocketManager.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include "Engine.h"
#include "Runtime/Networking/Public/Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Internationalization/Text.h"
#include "Internationalization/Internationalization.h"
USocketManager::USocketManager()
{

}

USocketManager::~USocketManager()
{

}

void USocketManager::Send(FString& string)
{
	//FString packetEnd = string;
	//packetEnd += "\n";
	char message[BUFFER_SIZE];
	const wchar_t* encode = *string;
	char defaultSetting = '?';

	int32 len = WideCharToMultiByte(CP_ACP, 0, encode, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, encode, -1, message, len, &defaultSetting, NULL);
	int32 bytesSents = 0;

	bool IsSended = socket->Send((uint8*)(message), len, bytesSents);

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
	FString command = FString::Printf(TEXT("LOGIN %s\r\n"), *name);//name이 추가되며 공백이 생겨 뒤에 두개 무시
	Send(command);
}

void USocketManager::SendRoomList()
{
	FString command = FString::Printf(TEXT("LT\n"));//TEXT("LT\r\n");
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
	addr->SetPort(PORT);

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
		//UE_LOG(LogTemp, Log, TEXT("@@ReceivedString: %s"), *recvStr);

		
		if (recvStr.Contains("\r\n") == true)
		{
			TArray<FString> lines;
			recvStr.ParseIntoArray(lines, TEXT("\r\n"));
			if (lines.Num() > 0)
			{
				UE_LOG(LogTemp, Log, TEXT("@@ lines Num: %d"), lines.Num());
				CheckRecvMsg(lines[0]);
				for (const FString& line : lines)
				{
					
					UE_LOG(LogTemp, Log, TEXT("@@one line : %s"), *line);

				}
			}
		}
		
		memset(buffer, 0, BUFFER_SIZE);
		recvBytes = 0;
	}
}

void USocketManager::CheckRecvMsg(FString& str)
{
	UE_LOG(LogTemp, Log, TEXT("@@@@@@@@@@@@@@@@@@@@USocketManager::CheckRecvMsg: %s"), *str);
	UChattingClientManager*manager = UChattingClientManager::GetInstance();
	if (!manager)
		return;

	UPlayerInfo* PlayerInfo = manager->GetPlayerInfo();
	if (!PlayerInfo)
		return;

	UUserWidgetManager* UIManager = UUserWidgetManager::GetInstance();
	if (!UIManager)
		return;

	UPlayerInfo::State curState = UPlayerInfo::State(PlayerInfo->GetPlayerState());
	UPlayerInfo::Packet curPacketFlag = UPlayerInfo::Packet(PlayerInfo->GetPacketFlag());
	if(curState == UPlayerInfo::WAITING)
	{
		if (str.Contains("------") == true)//로그인 성공
		{
			UE_LOG(LogTemp, Log, TEXT("@@@ USocketManager::CheckRecvMsg: 로그인 성공. state->LOBBY"));
			PlayerInfo->SetPlayerState(UPlayerInfo::LOBBY);
			UIManager->OnOffLogInView(false);
			UIManager->OnOffLobbyView(true);
		}
		else//로그인 실패
		{
			UE_LOG(LogTemp, Log, TEXT("@@@ USocketManager::CheckRecvMsg: 로그인 실패"));
		}
	}
	else if (curState == UPlayerInfo::LOBBY)
	{
		if (curPacketFlag == UPlayerInfo::USER_LIST)
		{

		}
		else if (curPacketFlag == UPlayerInfo::ROOM_LIST)
		{
			UE_LOG(LogTemp, Log, TEXT("~~~~~~~~~~~USocketManager::CheckRecvMsg() } UPlayerInfo::ROOM_LIST %s"), *str);
			UIManager->UpdateRoomList(str);
		}
		else if (curPacketFlag == UPlayerInfo::ROOM_INFO)
		{

		}
		else if (curPacketFlag == UPlayerInfo::USER_INFO)
		{

		}
	}
	else if (curState == UPlayerInfo::ROOM)
	{

	}
	else if (curState == UPlayerInfo::LOGOUT)
	{

	}
	else //
	{
		UE_LOG(LogTemp, Log, TEXT("@@ USocketManager::CheckRecvMsg | else"));
	}

}

/*
int USocketManager::WideCharToMBT(char* to, wchar_t* from)
{
	int len = WideCharToMultiByte(CP_ACP, 0, from, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, from, -1, to, len, NULL, NULL);
	return len;
}*/