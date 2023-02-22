// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyUserWidget.h"

void ULobbyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!RoomListBtn)
		return;
	RoomListBtn->OnClicked.AddDynamic(this, &ULobbyUserWidget::RoomListBtnClicked);

	if (!UserListBtn)
		return;
	UserListBtn->OnClicked.AddDynamic(this, &ULobbyUserWidget::UserListBtnClicked);

	if (!CreateRoomBtn)
		return;
	CreateRoomBtn->OnClicked.AddDynamic(this, &ULobbyUserWidget::CreateRoomBtnClicked);
}

//방 리스트 버튼 클릭
void ULobbyUserWidget::RoomListBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT(" ULobbyUserWidget::RoomListBtnClicked버튼 시작@@@@"));
	UChattingClientManager* manager = UChattingClientManager::GetInstance();
	manager->GetSocket()->SendRoomList();
}

void ULobbyUserWidget::UserListBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT(" ULobbyUserWidget::UserListBtnClicked버튼 시작@@@@"));
	UChattingClientManager* manager = UChattingClientManager::GetInstance();
	manager->GetSocket()->SendUserList();
}

void ULobbyUserWidget::CreateRoomBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT(" ULobbyUserWidget:: CreateRoomBtnClicked버튼 시작@@@@"));
	UUserWidgetManager* UImanager = UUserWidgetManager::GetInstance();

	UImanager->OnOffRoomOptionView(true);

}

//방 리스트 정보 텍스트 갱신
void ULobbyUserWidget::LoadList(const FString& msg)
{
	UE_LOG(LogTemp, Log, TEXT(" !@!@!@!@ ULobbyUserWidget::LoadRoomList ,%s"),*msg);
	ListScrollBox->ClearChildren();

	UTextBlock* NewTextBlock = NewObject<UTextBlock>(ListScrollBox);
	NewTextBlock->SetText(FText::FromString(msg));
	ListScrollBox->AddChild(NewTextBlock);
}