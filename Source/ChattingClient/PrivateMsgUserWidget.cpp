// Fill out your copyright notice in the Description page of Project Settings.


#include "PrivateMsgUserWidget.h"

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

void UPrivateMsgUserWidget::SendBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT(" UPrivateMsgUserWidget::SendBtnClicked()"));


	FString dest = (DestEditText->GetText()).ToString();
	FString msg = (MsgEditText->GetText()).ToString();

	UChattingClientManager* manager = UChattingClientManager::GetInstance();
	if (!manager)
		return;

	USocketManager* socketManager = manager->GetSocket();
	if (!socketManager)
	{
		UE_LOG(LogTemp, Log, TEXT("UPrivateMsgUserWidget::SendBtnClicked() | !socketmanager fail"));
		return;
	}

	socketManager->SendPrivateMsg(dest, msg);
	CloseBtnClicked();
}

void UPrivateMsgUserWidget::CloseBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT(" UPrivateMsgUserWidget::CloseBtnClicked()"));
	UUserWidgetManager* UImanager = UUserWidgetManager::GetInstance();
	UImanager->OnOffPrivateMsgView(false);
}