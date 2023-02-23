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

//로그인 요청
void USocketManager::SendLogin(const FString& name)
{
	FString command = FString::Printf(TEXT("LOGIN %s\r\n"), *name);//name이 추가되며 공백이 생겨 뒤에 두개 무시
	Send(command);
}

//방 정보 리스트 요청
void USocketManager::SendRoomList()
{
	UE_LOG(LogTemp, Log, TEXT("USocketManager::SendRoomList()"));
	FString command = FString::Printf(TEXT("LT\n"));//TEXT("LT\r\n");
	Send(command);
}

void USocketManager::SendRoomChat(const FString& chat)
{
	UE_LOG(LogTemp, Log, TEXT("USocketManager::SendRoomChat()"));
	FString command = FString::Printf(TEXT("%s\n"),*chat);//TEXT("LT\r\n");
	Send(command);
}

//유저 정보 리스트 요청
void USocketManager::SendUserList()
{
	UPlayerInfo* PlayerInfo = UChattingClientManager::GetInstance()->GetPlayerInfo();
	PlayerInfo->SetPacketFlag(UPlayerInfo::USER_LIST);
	UE_LOG(LogTemp, Log, TEXT("USocketManager::SendUserList()"));
	FString command = FString::Printf(TEXT("US\n"));
	Send(command);
}

void USocketManager::SendJoinRoom(const FString& name)
{
	UPlayerInfo* PlayerInfo = UChattingClientManager::GetInstance()->GetPlayerInfo();
	PlayerInfo->SetPacketFlag(UPlayerInfo::WAIT_JOIN);
	UE_LOG(LogTemp, Log, TEXT("USocketManager::SendUserList()"));
	FString command = FString::Printf(TEXT("J %s\n"),*name);
	Send(command);
}

//방 나가기 요청
void USocketManager::SendQuitRoom()
{
	UE_LOG(LogTemp, Log, TEXT("USocketManager::SendQuitRoom()"));
	UPlayerInfo* PlayerInfo = UChattingClientManager::GetInstance()->GetPlayerInfo();
	if (!PlayerInfo)
		return;
	PlayerInfo->SetPacketFlag(UPlayerInfo::QUIT_WAIT);
	FString command = FString::Printf(TEXT("Q\n"));
	Send(command);
}

void USocketManager::SendDeleteRoom()
{
	UPlayerInfo* PlayerInfo = UChattingClientManager::GetInstance()->GetPlayerInfo();
	if (!PlayerInfo)
		return;
	PlayerInfo->SetPacketFlag(UPlayerInfo::DEL_WAIT);
	FString command = FString::Printf(TEXT("DEL\n"));
	Send(command);
}

//채팅시스템 종료 요청
void USocketManager::SendQuitSystem()
{
	UE_LOG(LogTemp, Log, TEXT("USocketManager::SendQuitSystem()"));
	UPlayerInfo* PlayerInfo = UChattingClientManager::GetInstance()->GetPlayerInfo();
	if (!PlayerInfo)
		return;
	PlayerInfo->SetPacketFlag(UPlayerInfo::LOGOUT_WAIT);
	FString command = FString::Printf(TEXT("X\n"));
	Send(command);
}
//방 생성 요청
void USocketManager::SendCreateRoom(const FString& num, const FString& name)
{
	UPlayerInfo* PlayerInfo = UChattingClientManager::GetInstance()->GetPlayerInfo();
	PlayerInfo->SetPacketFlag(UPlayerInfo::WAIT_ROOM_CREATION);
	UE_LOG(LogTemp, Log, TEXT("USocketManager::SendCreateRoom()"));
	FString command = FString::Printf(TEXT("O %s %s\n"), *num,*name);
	Send(command);
}

//쪽지 보내기 요청
void USocketManager::SendPrivateMsg(const FString& name, const FString& msg)
{
	UPlayerInfo* PlayerInfo = UChattingClientManager::GetInstance()->GetPlayerInfo();
	PlayerInfo->SetPacketFlag(UPlayerInfo::WAIT_PRIVATE_MSG);
	UE_LOG(LogTemp, Log, TEXT("USocketManager::SendPrivateMsg()"));
	FString command = FString::Printf(TEXT("TO %s %s\n"), *name, *msg);
	Send(command);
}


//방 정보 요청
void USocketManager::SendRoomInfo(const FString& num)
{
	UPlayerInfo* PlayerInfo = UChattingClientManager::GetInstance()->GetPlayerInfo();
	PlayerInfo->SetPacketFlag(UPlayerInfo::ROOM_INFO);
	UE_LOG(LogTemp, Log, TEXT("USocketManager::SendRoomInfo()"));
	FString command = FString::Printf(TEXT("ST %s\n"), *num);
	Send(command);
}

//유저 정보 요청
void USocketManager::SendUserInfo(const FString& name)
{
	UPlayerInfo* PlayerInfo = UChattingClientManager::GetInstance()->GetPlayerInfo();
	PlayerInfo->SetPacketFlag(UPlayerInfo::USER_INFO);
	UE_LOG(LogTemp, Log, TEXT("USocketManager::SendUserInfo()"));
	FString command = FString::Printf(TEXT("PF %s\n"), *name);
	Send(command);
}

//지정된 주소로 연결
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

//서버로부터 정보가 오는지 확인
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

		if (curRecvBytes <= 0)
		{
			memset(buffer, 0, BUFFER_SIZE);
			recvBytes = 0;
			UE_LOG(LogTemp, Log, TEXT("curRecvBytes <= 0"));
			return;
		}

		//한글 받아지도록 변환
		FString recvStr = FString(UTF8_TO_TCHAR((const ANSICHAR*)buffer));
		
		if (recvStr.Contains("\r\n") == true)
		{
			TArray<FString> lines;
			recvStr.ParseIntoArray(lines, TEXT("\r\n"));
			if (lines.Num() > 0)
			{
				if (recvStr.Contains(TEXT("명령어안내")) == true)
				{
					TArray<FString> parsedStr;

					recvStr.ParseIntoArray(parsedStr, TEXT("명령어안내"));
					recvStr = parsedStr[0];
				}
				CheckRecvMsg(recvStr ,lines[0]);
			}
		}
		
		memset(buffer, 0, BUFFER_SIZE);
		recvBytes = 0;
	}
}

//수신한 메시지 해석
void USocketManager::CheckRecvMsg(FString& recvStr, FString& str1)
{
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
	
	if (curPacketFlag == UPlayerInfo::WAIT_PRIVATE_MSG)//쪽지 보내기
	{
		UIManager->UpdatePopUp(recvStr);
		UIManager->OnOffPopUpView(true);
		PlayerInfo->SetPacketFlag(UPlayerInfo::NON);
		return;
	}
	if (str1.Contains(TEXT("# ")) == true)//쪽지 받기
	{
		UIManager->UpdatePopUp(recvStr);
		UIManager->OnOffPopUpView(true);
		return;
	}
	if (str1.Contains(TEXT("폭파되었습니다")) == true)//타인에 의해 방 폭파됨
	{
		UIManager->UpdatePopUp(recvStr);
		UIManager->OnOffPopUpView(true);
		UIManager->OnOffRoomView(false);
		UIManager->OnOffLobbyView(true);
		PlayerInfo->SetPlayerState(UPlayerInfo::LOBBY);
		PlayerInfo->SetPacketFlag(UPlayerInfo::ROOM_LIST);
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
			if (str1.Contains(TEXT("안녕하세요.")) == true)
				return;
			UE_LOG(LogTemp, Log, TEXT("@@@ USocketManager::CheckRecvMsg: 로그인 실패"));
			UIManager->UpdatePopUp(recvStr);
			UIManager->OnOffPopUpView(true);
		}
	}
	else if (curState == UPlayerInfo::LOBBY)
	{
		if (curPacketFlag == UPlayerInfo::USER_LIST)
		{
			UIManager->UpdateList(recvStr);
		}
		else if (curPacketFlag == UPlayerInfo::ROOM_LIST)
		{
			UIManager->UpdateList(recvStr);
		}
		else if (curPacketFlag == UPlayerInfo::ROOM_INFO)
		{
			UE_LOG(LogTemp, Log, TEXT("ROOM_INFO pop up"));
			UIManager->UpdatePopUp(recvStr);
			UIManager->OnOffPopUpView(true);
			PlayerInfo->SetPacketFlag(UPlayerInfo::NON);
		}
		else if (curPacketFlag == UPlayerInfo::USER_INFO)
		{
			UE_LOG(LogTemp, Log, TEXT("USER_INFO pop up"));
			UIManager->UpdatePopUp(recvStr);
			UIManager->OnOffPopUpView(true);
			PlayerInfo->SetPacketFlag(UPlayerInfo::NON);
		}
		else if (curPacketFlag == UPlayerInfo::WAIT_JOIN)//방 참여 대기
		{
			if (str1.Contains(TEXT("들어오셨습니다")) == true)//방 참여 성공
			{
				UE_LOG(LogTemp, Log, TEXT("success room join"));
				PlayerInfo->SetPlayerState(UPlayerInfo::ROOM);
				PlayerInfo->SetPacketFlag(UPlayerInfo::NON);
				UIManager->OnOffLobbyView(false);
				FString title = TEXT("검색할 방 번호:");
				UIManager->OnOffSearchView(title,false);
				UIManager->OnOffRoomView(true);
				UIManager->UpdateChatList(recvStr);
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("fail room join"));
				UIManager->UpdatePopUp(recvStr);
				UIManager->OnOffPopUpView(true);
				PlayerInfo->SetPacketFlag(UPlayerInfo::NON);
			}
		}
		else if (curPacketFlag == UPlayerInfo::WAIT_ROOM_CREATION)
		{
			UE_LOG(LogTemp, Log, TEXT("room creation result %s"), *str1);
			if (str1.Contains(TEXT("개설")) == true)//방 생성 성공
			{
				UE_LOG(LogTemp, Log, TEXT("success room creation"));
				PlayerInfo->SetPlayerState(UPlayerInfo::ROOM);
				PlayerInfo->SetPacketFlag(UPlayerInfo::NON);
				UIManager->OnOffLobbyView(false);
				UIManager->OnOffRoomOptionView(false);
				UIManager->OnOffRoomView(true);
				UIManager->UpdateChatList(recvStr);
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("fail room creation"));
				UIManager->UpdatePopUp(recvStr);
				UIManager->OnOffPopUpView(true);
				PlayerInfo->SetPacketFlag(UPlayerInfo::NON);
			}
		}
	}
	else if (curState == UPlayerInfo::ROOM)
	{
		if (curPacketFlag == UPlayerInfo::QUIT_WAIT)
		{
			UIManager->OnOffRoomView(false);
			UIManager->OnOffLobbyView(true);
			PlayerInfo->SetPlayerState(UPlayerInfo::LOBBY);
			PlayerInfo->SetPacketFlag(UPlayerInfo::ROOM_LIST);
			return;
		}
		else if (curPacketFlag == UPlayerInfo::DEL_WAIT)
		{
			UIManager->OnOffRoomView(false);
			UIManager->OnOffLobbyView(true);
			UIManager->UpdatePopUp(recvStr);
			UIManager->OnOffPopUpView(true);
			PlayerInfo->SetPlayerState(UPlayerInfo::LOBBY);
			PlayerInfo->SetPacketFlag(UPlayerInfo::ROOM_LIST);
			return;
		}
		UIManager->UpdateChatList(recvStr);
	}
	else if (curPacketFlag == UPlayerInfo::LOGOUT_WAIT)
	{
		if (str1.Contains(TEXT("---")) == true)//종료 성공
		{
			UE_LOG(LogTemp, Log, TEXT("success system exit"));
			FGenericPlatformMisc::RequestExit(false);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("fail system exit"));
		}
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