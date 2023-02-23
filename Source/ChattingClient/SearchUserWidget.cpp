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

void USearchUserWidget::OKBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT(" URoomOptionUserWidget::OKBtnClicked()"));


	FString name = (NumEditText->GetText()).ToString();

	UChattingClientManager* manager = UChattingClientManager::GetInstance();
	if (!manager)
		return;

	USocketManager* socketManager = manager->GetSocket();
	if (!socketManager)
	{
		UE_LOG(LogTemp, Log, TEXT("LogInBtnClicked() | !socketmanager fail"));
		return;
	}

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
	UE_LOG(LogTemp, Log, TEXT("@@@USearchUserWidget::OKBtnClicked success"));
	CloseBtnClicked();
}


void USearchUserWidget::CloseBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT(" UPopUpUserWidget::CloseBtnClicked()"));
	UUserWidgetManager* UImanager = UUserWidgetManager::GetInstance();
	UImanager->OnOffSearchView(title,false);
	NumEditText->SetText(FText::FromString(""));
}

// 제목 택스트 업데이트
void USearchUserWidget::LoadTitleMsg(const FString& msg)
{
	title = msg;
	UE_LOG(LogTemp, Log, TEXT(" !@!@!@!@ ULobbyUserWidget::LoadRoomList ,%s"), *msg);
	TitleScrollBox->ClearChildren();

	UTextBlock* NewTextBlock = NewObject<UTextBlock>(TitleScrollBox);
	NewTextBlock->SetText(FText::FromString(msg));
	TitleScrollBox->AddChild(NewTextBlock);
}