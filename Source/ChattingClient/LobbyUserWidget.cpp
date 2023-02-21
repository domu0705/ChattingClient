// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyUserWidget.h"

void ULobbyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (RoomListBtn)
	{
		RoomListBtn->OnClicked.AddDynamic(this, &ULobbyUserWidget::RoomListBtnClicked);
	}

	//SetLoginText();
	//if (Btn_LogIn)
	//{
	//	Btn_LogIn->OnClicked.AddDynamic(this, &ULogIn_UserWidget::Btn_LogIn_Func);
	//}
}

void ULobbyUserWidget::RoomListBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT(" RoomListBtnClicked버튼 시작@@@@"));

}