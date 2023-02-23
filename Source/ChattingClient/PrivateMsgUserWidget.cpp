// Fill out your copyright notice in the Description page of Project Settings.


#include "PrivateMsgUserWidget.h"

//버튼 이벤트와 함수 연결
void UPrivateMsgUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!SendBtn)
		return;
	SendBtn->OnClicked.AddDynamic(this, &UPrivateMsgUserWidget::SendBtnClicked);

	if (!CloseBtn)
		return;
	CloseBtn->OnClicked.AddDynamic(this, &UPrivateMsgUserWidget::CloseBtnClicked);
}

// 쪽지 전송 요청
void UPrivateMsgUserWidget::SendBtnClicked()
{
	FString dest = (DestEditText->GetText()).ToString();
	FString msg = (MsgEditText->GetText()).ToString();

	UChattingClientManager* manager = UChattingClientManager::GetInstance();
	if (!manager)
		return;

	USocketManager* socketManager = manager->GetSocket();
	if (!socketManager)
		return;

	socketManager->SendPrivateMsg(dest, msg);
	CloseBtnClicked();
}

//쪽지 전송 창 닫기
void UPrivateMsgUserWidget::CloseBtnClicked()
{
	UUserWidgetManager* UImanager = UUserWidgetManager::GetInstance();
	UImanager->OnOffPrivateMsgView(false);
}