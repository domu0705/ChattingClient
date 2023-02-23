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
	if (!JoinRoomBtn)
		return;
	JoinRoomBtn->OnClicked.AddDynamic(this, &ULobbyUserWidget::JoinRoomBtnClicked);


	if (!RoomInfoBtn)
		return;
	RoomInfoBtn->OnClicked.AddDynamic(this, &ULobbyUserWidget::RoomInfoBtnClicked);
	if (!UserInfoBtn)
		return;
	UserInfoBtn->OnClicked.AddDynamic(this, &ULobbyUserWidget::UserInfoBtnClicked);

	if (!PrivateMsgBtn)
		return;
	PrivateMsgBtn->OnClicked.AddDynamic(this, &ULobbyUserWidget::PrivateMsgBtnClicked);
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

void ULobbyUserWidget::JoinRoomBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT(" ULobbyUserWidget:: JoinRoomBtnClicked버튼 시작@@@@"));
	UUserWidgetManager* UImanager = UUserWidgetManager::GetInstance();

	FString text = TEXT("참여할 방 번호 입력");
	UImanager->OnOffSearchView(text, true);
}

void ULobbyUserWidget::RoomInfoBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT(" ULobbyUserWidget:: RoomInfoBtnClicked버튼 시작@@@@"));
	UUserWidgetManager* UImanager = UUserWidgetManager::GetInstance();

	FString text = TEXT("검색할 방 번호 입력");
	UImanager->OnOffSearchView(text, true);
}

void ULobbyUserWidget::UserInfoBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT(" ULobbyUserWidget:: UserInfoBtnClicked버튼 시작@@@@"));
	UUserWidgetManager* UImanager = UUserWidgetManager::GetInstance();

	FString text = TEXT("검색할 ID 입력");
	UImanager->OnOffSearchView(text,true);
}


void ULobbyUserWidget::PrivateMsgBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT(" ULobbyUserWidget:: PrivateMsgBtnClicked버튼 시작@@@@"));
	UUserWidgetManager* UImanager = UUserWidgetManager::GetInstance();

	UImanager->OnOffPrivateMsgView(true);

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
