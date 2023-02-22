// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomUserWidget.h"

void URoomUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!SendBtn)
		return;
	SendBtn->OnClicked.AddDynamic(this, &URoomUserWidget::SendBtnClicked);

	if (!QuitBtn)
		return;
	QuitBtn->OnClicked.AddDynamic(this, &URoomUserWidget::QuitBtnClicked);

}

void URoomUserWidget::SendBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT(" ULobbyUserWidget::RoomListBtnClicked버튼 시작@@@@"));
	UChattingClientManager* manager = UChattingClientManager::GetInstance();
	manager->GetSocket()->SendRoomList();
}


void URoomUserWidget::QuitBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT(" ULobbyUserWidget::QuitBtnClicked()"));
	UUserWidgetManager* UImanager = UUserWidgetManager::GetInstance();
	UImanager->OnOffRoomOptionView(false);
	chatLog = TEXT("");
}

void URoomUserWidget::LoadChat(FString& msg)
{
	chatLog += msg;
	UE_LOG(LogTemp, Log, TEXT(" !@!@!@!@  URoomUserWidget::LoadChat ,%s"), *msg);

	ChatScrollBox->ClearChildren();
	UTextBlock* NewTextBlock = NewObject<UTextBlock>(ChatScrollBox);
	NewTextBlock->SetText(FText::FromString(chatLog));
	FLinearColor NewColor = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);
	NewTextBlock->SetColorAndOpacity(NewColor);
	ChatScrollBox->AddChild(NewTextBlock);
}