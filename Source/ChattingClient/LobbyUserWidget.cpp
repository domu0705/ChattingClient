// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyUserWidget.h"

void ULobbyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!RoomListBtn)
		return;
	RoomListBtn->OnClicked.AddDynamic(this, &ULobbyUserWidget::RoomListBtnClicked);
}

//방 리스트 버튼 클릭
void ULobbyUserWidget::RoomListBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT(" RoomListBtnClicked버튼 시작@@@@"));
	//UChattingClientManager* manager = UChattingClientManager::Get
	//manager->GetSocket()->SendRoomList();
}

//방 리스트 정보 텍스트 갱신
void ULobbyUserWidget::LoadRoomList(const FString& msg)
{
	UE_LOG(LogTemp, Log, TEXT(" !@!@!@!@ ULobbyUserWidget::LoadRoomList ,%s"),*msg);
	ListScrollBox->ClearChildren();

	UTextBlock* NewTextBlock = NewObject<UTextBlock>(ListScrollBox);
	NewTextBlock->SetText(FText::FromString(msg));
	ListScrollBox->AddChild(NewTextBlock);
}