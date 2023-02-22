// Fill out your copyright notice in the Description page of Project Settings.

#include "LogInUserWidget.h"
#include "SocketManager.h"

//위젯 클래스의 셍성자
void ULogInUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(LogTemp, Log, TEXT("NativeConstruct ���۵�@@@@@@@@@@@@@@"));

	UserWidgetManager = UUserWidgetManager::GetInstance();

	if (LogInBtn)
	{
		LogInBtn->OnClicked.AddDynamic(this, &ULogInUserWidget::LogInBtnClicked);
		LogInBtn->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (PortBtn)
	{
		PortBtn->OnClicked.AddDynamic(this, &ULogInUserWidget::PortConnBtnClicked);
	}
}

void ULogInUserWidget::SetLoginUI()
{
	//EditText_LogIn->SetHintText(FText::FromString(L"hihihi!"));/

}

void ULogInUserWidget::PortConnBtnClicked()
{
	//UChattingClientManager* manager = UChattingClientManager::GetInstance();
	USocketManager* socketManager = USocketManager::GetInstance();//manager->GetSocket();

	if (socketManager->ConnectServer())
	{
		UE_LOG(LogTemp, Log, TEXT("@@@PortConnBtnClicked::ConnectServer success"));
		PortBtn->SetVisibility(ESlateVisibility::Collapsed);//Collapsed  Hidden
		LogInBtn->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("@@@PortConnBtnClicked::ConnectServer fail"));
	}
}

void ULogInUserWidget::LogInBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT("버튼 시작@@@@@@@@@@@@@@"));
	FString idStr = (IDEditText->GetText()).ToString();
	int32 tempCnt = FCString::Atoi(*idStr);

	UChattingClientManager* manager = UChattingClientManager::GetInstance();
	if (!manager)
		return;

	USocketManager* socketManager = manager->GetSocket();
	if (!socketManager)
	{
		UE_LOG(LogTemp, Log, TEXT("LogInBtnClicked() | !socketmanager fail"));
		return;
	}
	
	if (socketManager)
	{
		socketManager->SendLogin(idStr);
		UE_LOG(LogTemp, Log, TEXT("@@@LogInBtnClicked::SendLogin success"));
		UserWidgetManager->OnOffLogInView(false);
		UserWidgetManager->OnOffLobbyView(true);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("@@@LogInBtnClicked::SendLogin fail"));
	}
}
