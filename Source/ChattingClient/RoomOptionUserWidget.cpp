// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomOptionUserWidget.h"

void URoomOptionUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!OKBtn)
		return;
	OKBtn->OnClicked.AddDynamic(this, &URoomOptionUserWidget::OKBtnClicked);
	if (!CloseBtn)
		return;
	CloseBtn->OnClicked.AddDynamic(this, &URoomOptionUserWidget::CloseBtnClicked);
}


void URoomOptionUserWidget::OKBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT(" URoomOptionUserWidget::OKBtnClicked()"));


	FString num = (NumEditText->GetText()).ToString();
	FString name = (NameEditText->GetText()).ToString();

	UChattingClientManager* manager = UChattingClientManager::GetInstance();
	if (!manager)
		return;

	USocketManager* socketManager = manager->GetSocket();
	if (!socketManager)
	{
		UE_LOG(LogTemp, Log, TEXT("LogInBtnClicked() | !socketmanager fail"));
		return;
	}

	socketManager->SendCreateRoom(num, name);
	UE_LOG(LogTemp, Log, TEXT("@@@LogInBtnClicked::SendLogin success"));

}

void URoomOptionUserWidget::CloseBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT(" URoomOptionUserWidget::CloseBtnClicked()"));
	UUserWidgetManager* UImanager = UUserWidgetManager::GetInstance();
	UImanager->OnOffRoomOptionView(false);
}