// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomUserWidget.h"


//버튼 이벤트와 함수 연결
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

//채팅방에서 채팅 전송 요청
void URoomUserWidget::SendBtnClicked()
{
	FString chat = (ChatEditText->GetText()).ToString();

	UChattingClientManager* manager = UChattingClientManager::GetInstance();
	manager->GetSocket()->SendRoomChat(chat);
	ChatEditText->SetText(FText::FromString(""));
}

//채팅방 나가기 요청
void URoomUserWidget::QuitBtnClicked()
{
	UChattingClientManager* manager = UChattingClientManager::GetInstance();
	manager->GetSocket()->SendQuitRoom();
	chatLog = TEXT("");
	ChatEditText->SetText(FText::FromString(""));
}

//방 삭제 요청
void URoomUserWidget::DeleteBtnClicked()
{
	UChattingClientManager* manager = UChattingClientManager::GetInstance();
	manager->GetSocket()->SendDeleteRoom();
	chatLog = TEXT("");
	ChatEditText->SetText(FText::FromString(""));
}

//채팅방 채팅 내용 업데이트
void URoomUserWidget::LoadChat(FString& msg)
{
	chatLog += msg;

	ChatScrollBox->ClearChildren();
	UTextBlock* NewTextBlock = NewObject<UTextBlock>(ChatScrollBox);
	NewTextBlock->SetText(FText::FromString(chatLog));
	FLinearColor NewColor = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);
	NewTextBlock->SetColorAndOpacity(NewColor);
	ChatScrollBox->AddChild(NewTextBlock);
}