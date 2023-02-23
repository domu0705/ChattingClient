// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChattingClientGameModeBase.h"
#include "ChattingClientGameInstance.h"
#include <Blueprint/UserWidget.h>


AChattingClientGameModeBase::AChattingClientGameModeBase()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AChattingClientGameModeBase::StartPlay()
{
	Super::StartPlay();

	ChattingClientManager = UChattingClientManager::GetInstance();
	PlayerInfo = UPlayerInfo::GetInstance();
	ChattingClientManager->SetPlayerInfo(PlayerInfo);
	SocketManager = USocketManager::GetInstance();
	ChattingClientManager->SetSocket(SocketManager);
}

void AChattingClientGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UserWidgetManager = UUserWidgetManager::GetInstance();
	
	//UI 생성
	UserWidgetManager->CreateLogInView( GetWorld() );
	UserWidgetManager->CreateLobbyView(GetWorld());
	UserWidgetManager->CreateRoomOptionView(GetWorld());
	UserWidgetManager->CreateRoomView(GetWorld());
	UserWidgetManager->CreatePrivateMsgView(GetWorld());
	UserWidgetManager->CreatePopUpView(GetWorld());
	UserWidgetManager->CreateSearchView(GetWorld());

	//유저 정보 초기화
	PlayerInfo = UPlayerInfo::GetInstance();
	PlayerInfo->ResetInfo();
}

void AChattingClientGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!SocketManager)
		return;
	SocketManager->Tick();	
}

