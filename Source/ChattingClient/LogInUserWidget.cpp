// Fill out your copyright notice in the Description page of Project Settings.

#include "LogInUserWidget.h"
#include "SocketManager.h"

//버튼이벤트와 함수 연결
void ULogInUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UserWidgetManager = UUserWidgetManager::GetInstance();

	if (!LogInBtn)
		return;
	LogInBtn->OnClicked.AddDynamic(this, &ULogInUserWidget::LogInBtnClicked);
	LogInBtn->SetVisibility(ESlateVisibility::Collapsed);

	if (!PortBtn)
		return;
	PortBtn->OnClicked.AddDynamic(this, &ULogInUserWidget::PortConnBtnClicked);
}

//포트연결 요청
void ULogInUserWidget::PortConnBtnClicked()
{
	USocketManager* socketManager = USocketManager::GetInstance();
	if (!socketManager)
		return;

	if (socketManager->ConnectServer())
	{
		PortBtn->SetVisibility(ESlateVisibility::Collapsed);
		LogInBtn->SetVisibility(ESlateVisibility::Visible);
	}
}

//로그인 요청
void ULogInUserWidget::LogInBtnClicked()
{
	FString idStr = (IDEditText->GetText()).ToString();
	int32 tempCnt = FCString::Atoi(*idStr);

	UChattingClientManager* manager = UChattingClientManager::GetInstance();
	if (!manager)
		return;

	USocketManager* socketManager = manager->GetSocket();
	if (!socketManager)
		return;

	socketManager->SendLogin(idStr);
}
