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
	UE_LOG(LogTemp, Log, TEXT("USocketManager::SendRoomList()"));
	FString command = FString::Printf(TEXT("LT\n"));//TEXT("LT\r\n");
	Send(command);
}

void USocketManager::SendUserList()
{
	UPlayerInfo* PlayerInfo = UChattingClientManager::GetInstance()->GetPlayerInfo();
	PlayerInfo->SetPacketFlag(UPlayerInfo::USER_LIST);
	UE_LOG(LogTemp, Log, TEXT("USocketManager::SendUserList()"));
	FString command = FString::Printf(TEXT("US\n"));//TEXT("LT\r\n");
	Send(command);
}

void USocketManager::SendQuitRoom()
{
	UE_LOG(LogTemp, Log, TEXT("USocketManager::SendQuitRoom()"));
	UPlayerInfo* PlayerInfo = UChattingClientManager::GetInstance()->GetPlayerInfo();
	if (!PlayerInfo)
		return;
	PlayerInfo->SetPlayerState(UPlayerInfo::LOBBY);
	PlayerInfo->SetPacketFlag(UPlayerInfo::NON);
	FString command = FString::Printf(TEXT("Q\n"));
	Send(command);
}

void USocketManager::SendCreateRoom(const FString& num, const FString& name)
{
	UPlayerInfo* PlayerInfo = UChattingClientManager::GetInstance()->GetPlayerInfo();
	PlayerInfo->SetPacketFlag(UPlayerInfo::WAIT_ROOM_CREATION);
	UE_LOG(LogTemp, Log, TEXT("USocketManager::SendCreateRoom()"));
	FString command = FString::Printf(TEXT("O %s %s\n"), *num,*name);
	Send(command);
}

void USocketManager::SendPrivateMsg(const FString& name, const FString& msg)
{
	UPlayerInfo* PlayerInfo = UChattingClientManager::GetInstance()->GetPlayerInfo();
	PlayerInfo->SetPacketFlag(UPlayerInfo::WAIT_PRIVATE_MSG);
	UE_LOG(LogTemp, Log, TEXT("USocketManager::SendPrivateMsg()"));
	FString command = FString::Printf(TEXT("TO %s %s\n"), *name, *msg);
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
		UE_LOG(LogTemp, Log, TEXT("@@ReceivedString: %s"), *recvStr);

		
		if (recvStr.Contains("\r\n") == true)
		{
			TArray<FString> lines;
			recvStr.ParseIntoArray(lines, TEXT("\r\n"));
			if (lines.Num() > 0)
			{
				//UE_LOG(LogTemp, Log, TEXT("@@ lines Num: %d"), lines.Num());
				CheckRecvMsg(recvStr ,lines[0]);
				for (const FString& line : lines)
				{
					
					//UE_LOG(LogTemp, Log, TEXT("@@one line : %s"), *line);

				}
			}
		}
		
		memset(buffer, 0, BUFFER_SIZE);
		recvBytes = 0;
	}
}

void USocketManager::CheckRecvMsg(FString& recvStr, FString& str1)
{
	UE_LOG(LogTemp, Log, TEXT("@@@@@@@@@@@@@@@@@@@@USocketManager::CheckRecvMsg: %s"), *recvStr);
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
	
	if (curPacketFlag == UPlayerInfo::WAIT_PRIVATE_MSG)//귓속말
	{
		//귓말 갔다는 팝업
		return;
	}
	
	if(curState == UPlayerInfo::WAITING)
	{
		if (str1.Contains("------") == true)//로그인 성공
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
		UE_LOG(LogTemp, Log, TEXT("LOBBY 입장!!!!!!!!!!!!!!!"));
		if (curPacketFlag == UPlayerInfo::USER_LIST)
		{
			UIManager->UpdateList(recvStr);
		}
		else if (curPacketFlag == UPlayerInfo::ROOM_LIST)
		{
			UE_LOG(LogTemp, Log, TEXT("~~~~~~~~~~~USocketManager::CheckRecvMsg() } UPlayerInfo::ROOM_LIST %s"), *recvStr);
			UIManager->UpdateList(recvStr);
		}
		else if (curPacketFlag == UPlayerInfo::ROOM_INFO)
		{

		}
		else if (curPacketFlag == UPlayerInfo::USER_INFO)
		{

		}
		else if (curPacketFlag == UPlayerInfo::WAIT_ROOM_CREATION)
		{
			UE_LOG(LogTemp, Log, TEXT("room creation result %s"), *str1);
			if (str1.Contains(TEXT("개설")) == true)//방 생성 성공
			{
				UE_LOG(LogTemp, Log, TEXT("success room creation"));
				PlayerInfo->SetPlayerState(UPlayerInfo::ROOM);
				UIManager->OnOffLobbyView(false);
				UIManager->OnOffRoomOptionView(false);
				UIManager->OnOffRoomView(true);
				UIManager->UpdateChatList(recvStr);
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("fail room creation"));
			}
		}
	}
	else if (curState == UPlayerInfo::ROOM)
	{
		UIManager->UpdateChatList(recvStr);
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