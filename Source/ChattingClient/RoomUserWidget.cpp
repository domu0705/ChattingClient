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

	if (!DelBtn)
		return;
	DelBtn->OnClicked.AddDynamic(this, &URoomUserWidget::DeleteBtnClicked);

}

void URoomUserWidget::SendBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT(" ULobbyUserWidget::SendBtnClicked버튼 시작@@@@"));
	FString chat = (ChatEditText->GetText()).ToString();

	UChattingClientManager* manager = UChattingClientManager::GetInstance();
	manager->GetSocket()->SendRoomChat(chat);
	//ChatEditText->SetEditableText();
	ChatEditText->SetText(FText::FromString(""));
}


void URoomUserWidget::QuitBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT(" ULobbyUserWidget::QuitBtnClicked()"));

	UChattingClientManager* manager = UChattingClientManager::GetInstance();
	manager->GetSocket()->SendQuitRoom();
	chatLog = TEXT("");
	ChatEditText->SetText(FText::FromString(""));
}

//방 삭제 요청 보내기
void URoomUserWidget::DeleteBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT(" ULobbyUserWidget::DeleteBtnClicked()"));

	UChattingClientManager* manager = UChattingClientManager::GetInstance();
	manager->GetSocket()->SendDeleteRoom();
	chatLog = TEXT("");
	ChatEditText->SetText(FText::FromString(""));
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