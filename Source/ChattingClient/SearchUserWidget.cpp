// Fill out your copyright notice in the Description page of Project Settings.


#include "SearchUserWidget.h"

void USearchUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	title = TEXT("검색할 방 번호:");

	if (!OKBtn)
		return;
	OKBtn->OnClicked.AddDynamic(this, &USearchUserWidget::OKBtnClicked);
	if (!CloseBtn)
		return;
	CloseBtn->OnClicked.AddDynamic(this, &USearchUserWidget::CloseBtnClicked);
}

//입력한 정보에 해당하는 검색 요청
void USearchUserWidget::OKBtnClicked()
{
	FString name = (NumEditText->GetText()).ToString();

	UChattingClientManager* manager = UChattingClientManager::GetInstance();
	if (!manager)
		return;

	USocketManager* socketManager = manager->GetSocket();
	if (!socketManager)
		return;

	if (title.Contains(TEXT("검색할 방")))//방찾기
	{
		socketManager->SendRoomInfo(name);
	}
	else if (title.Contains(TEXT("참여할 방")))//방찾기
	{
		socketManager->SendJoinRoom(name);
	}
	else//유저 찾기
	{
		socketManager->SendUserInfo(name);
	}

	CloseBtnClicked();
}

//정보 검색 창 닫기
void USearchUserWidget::CloseBtnClicked()
{
	UUserWidgetManager* UImanager = UUserWidgetManager::GetInstance();
	UImanager->OnOffSearchView(title,false);
	NumEditText->SetText(FText::FromString(""));
}

// 정보 설명 택스트를 업데이트 함
void USearchUserWidget::LoadTitleMsg(const FString& msg)
{
	title = msg;
	TitleTextBox->SetText(FText::FromString(msg));
}