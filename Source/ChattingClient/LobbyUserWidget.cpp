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
	if (!QuitBtn)
		return;
	QuitBtn->OnClicked.AddDynamic(this, &ULobbyUserWidget::QuitBtnClicked);
}

//모든 채팅방 정보 요청
void ULobbyUserWidget::RoomListBtnClicked()
{
	UChattingClientManager* manager = UChattingClientManager::GetInstance();
	manager->GetSocket()->SendRoomList();
}

//모든 유저 정보 요청
void ULobbyUserWidget::UserListBtnClicked()
{
	UChattingClientManager* manager = UChattingClientManager::GetInstance();
	manager->GetSocket()->SendUserList();
}

//방 생성 팝업 보여주기
void ULobbyUserWidget::CreateRoomBtnClicked()
{
	UUserWidgetManager* UImanager = UUserWidgetManager::GetInstance();
	UImanager->OnOffRoomOptionView(true);
}

//방 참여 팝업 보여주기
void ULobbyUserWidget::JoinRoomBtnClicked()
{
	UUserWidgetManager* UImanager = UUserWidgetManager::GetInstance();
	FString text = TEXT("참여할 방 번호 : ");
	UImanager->OnOffSearchView(text, true);
}

//방 검색 팝업보여주기
void ULobbyUserWidget::RoomInfoBtnClicked()
{
	UUserWidgetManager* UImanager = UUserWidgetManager::GetInstance();
	FString text = TEXT("검색할 방 번호 : ");
	UImanager->OnOffSearchView(text, true);
}

//아이디 검색창 보여주기
void ULobbyUserWidget::UserInfoBtnClicked()
{
	UUserWidgetManager* UImanager = UUserWidgetManager::GetInstance();
	FString text = TEXT("검색할 ID :");
	UImanager->OnOffSearchView(text,true);
}

//쪽지 생성 팝업 보여주기
void ULobbyUserWidget::PrivateMsgBtnClicked()
{
	UUserWidgetManager* UImanager = UUserWidgetManager::GetInstance();
	UImanager->OnOffPrivateMsgView(true);
}

//로비 나가기
void ULobbyUserWidget::QuitBtnClicked()
{
	UChattingClientManager* manager = UChattingClientManager::GetInstance();
	manager->GetSocket()->SendQuitSystem();
	UKismetSystemLibrary::QuitGame(this, 0, EQuitPreference::Quit, false);
}

//방 리스트 정보 텍스트 갱신
void ULobbyUserWidget::LoadList(const FString& msg)
{
	ListScrollBox->ClearChildren();

	UTextBlock* NewTextBlock = NewObject<UTextBlock>(ListScrollBox);
	NewTextBlock->SetText(FText::FromString(msg));
	FLinearColor NewColor = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);
	NewTextBlock->SetColorAndOpacity(NewColor);
	ListScrollBox->AddChild(NewTextBlock);
}
