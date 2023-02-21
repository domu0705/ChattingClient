// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyUserWidget.h"

void ULobbyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (RoomListBtn)
	{
		RoomListBtn->OnClicked.AddDynamic(this, &ULobbyUserWidget::RoomListBtnClicked);
	}
}

void ULobbyUserWidget::RoomListBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT(" RoomListBtnClicked버튼 시작@@@@"));

}