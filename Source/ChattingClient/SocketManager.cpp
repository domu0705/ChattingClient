// Fill out your copyright notice in the Description page of Project Settings.

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

//서버로 데이터 전송 
void USocketManager::Send(FString& string)
{
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
	FString command = FString::Printf(TEXT("LOGIN %s\r\n"), *name);
	Send(command);
}

//방 정보 리스트 요청
void USocketManager::SendRoomList()
{
	FString command = FString::Printf(TEXT("LT\n"));
	Send(command);
}

//채팅 전송 요청
void USocketManager::SendRoomChat(const FString& chat)
{
	FString command = FString::Printf(TEXT("%s\n"),*chat);
	Send(command);
}

//유저 정보 리스트 요청
void USocketManager::SendUserList()
{
	UPlayerInfo* PlayerInfo = UChattingClientManager::GetInstance()->GetPlayerInfo();
	PlayerInfo->SetPacketFlag(UPlayerInfo::USER_LIST);
	FString command = FString::Printf(TEXT("US\n"));
	Send(command);
}

//방 참가 요청
void USocketManager::SendJoinRoom(const FString& name)
{
	UPlayerInfo* PlayerInfo = UChattingClientManager::GetInstance()->GetPlayerInfo();
	PlayerInfo->SetPacketFlag(UPlayerInfo::WAIT_JOIN);
	FString command = FString::Printf(TEXT("J %s\n"),*name);
	Send(command);
}

//방 나가기 요청
void USocketManager::SendQuitRoom()
{
	UPlayerInfo* PlayerInfo = UChattingClientManager::GetInstance()->GetPlayerInfo();
	if (!PlayerInfo)
		return;
	PlayerInfo->SetPacketFlag(UPlayerInfo::QUIT_WAIT);
	FString command = FString::Printf(TEXT("Q\n"));
	Send(command);
}

//방 삭제 요청
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
	FString command = FString::Printf(TEXT("O %s %s\n"), *num,*name);
	Send(command);
}

//쪽지 보내기 요청
void USocketManager::SendPrivateMsg(const FString& name, const FString& msg)
{
	UPlayerInfo* PlayerInfo = UChattingClientManager::GetInstance()->GetPlayerInfo();
	PlayerInfo->SetPacketFlag(UPlayerInfo::WAIT_PRIVATE_MSG);
	FString command = FString::Printf(TEXT("TO %s %s\n"), *name, *msg);
	Send(command);
}

//방 정보 요청
void USocketManager::SendRoomInfo(const FString& num)
{
	UPlayerInfo* PlayerInfo = UChattingClientManager::GetInstance()->GetPlayerInfo();
	PlayerInfo->SetPacketFlag(UPlayerInfo::ROOM_INFO);
	FString command = FString::Printf(TEXT("ST %s\n"), *num);
	Send(command);
}

//유저 정보 요청
void USocketManager::SendUserInfo(const FString& name)
{
	UPlayerInfo* PlayerInfo = UChattingClientManager::GetInstance()->GetPlayerInfo();
	PlayerInfo->SetPacketFlag(UPlayerInfo::USER_INFO);
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

//서버로부터 정보가 오는지 지속적 확인
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
				//불필요 데이터 삭제
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
			PlayerInfo->SetPlayerState(UPlayerInfo::LOBBY);
			UIManager->OnOffLogInView(false);
			UIManager->OnOffLobbyView(true);
		}
		else//로그인 실패
		{
			if (str1.Contains(TEXT("안녕하세요.")) == true)
				return;
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
			UIManager->UpdatePopUp(recvStr);
			UIManager->OnOffPopUpView(true);
			PlayerInfo->SetPacketFlag(UPlayerInfo::NON);
		}
		else if (curPacketFlag == UPlayerInfo::USER_INFO)
		{
			UIManager->UpdatePopUp(recvStr);
			UIManager->OnOffPopUpView(true);
			PlayerInfo->SetPacketFlag(UPlayerInfo::NON);
		}
		else if (curPacketFlag == UPlayerInfo::WAIT_JOIN)//방 참여 대기
		{
			if (str1.Contains(TEXT("들어오셨습니다")) == true)//방 참여 성공
			{
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
				UIManager->UpdatePopUp(recvStr);
				UIManager->OnOffPopUpView(true);
				PlayerInfo->SetPacketFlag(UPlayerInfo::NON);
			}
		}
		else if (curPacketFlag == UPlayerInfo::WAIT_ROOM_CREATION)
		{
			if (str1.Contains(TEXT("개설")) == true)//방 생성 성공
			{
				PlayerInfo->SetPlayerState(UPlayerInfo::ROOM);
				PlayerInfo->SetPacketFlag(UPlayerInfo::NON);
				UIManager->OnOffLobbyView(false);
				UIManager->OnOffRoomOptionView(false);
				UIManager->OnOffRoomView(true);
				UIManager->UpdateChatList(recvStr);
			}
			else
			{
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
			FGenericPlatformMisc::RequestExit(false);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("fail system exit"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("USocketManager::CheckRecvMsg() | msg not used"));
	}
}