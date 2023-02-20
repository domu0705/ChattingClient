// Fill out your copyright notice in the Description page of Project Settings.
//���⼭ ���콺 Ŀ�� ���̰� �ٲ��־�� �ҵ�

#include "UMGPlayerController.h"

/*
void AUMGPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("AUMGPlayerController @@@@@@@@@@@@@@"));
	SetInputMode(FInputModeGameAndUI()); //5:05
}
*/
AUMGPlayerController::AUMGPlayerController()
{
	static ConstructorHelpers::FClassFinder<ULogInUserWidget> WB_Login(TEXT("/Game/BP_Login"));// WidgetBlueprint'/Game/BP_LogIn.BP_LogIn'
	if (WB_Login.Succeeded())
	{
		LoginUIClass = WB_Login.Class;
		UE_LOG(LogTemp, Log, TEXT("success @@@@@@@@@@@@@@"));
	}
}

void AUMGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly()); //5:05 게임과 UI모두 입력 가능한 상태가 됨  FInputModeGameAndUI
	bShowMouseCursor = true;
	if (LoginUIClass)
	{
		LoginUIObject = CreateWidget<ULogInUserWidget>(GetWorld(), LoginUIClass);
		if (LoginUIObject)
		{
			LoginUIObject->AddToViewport();
			UE_LOG(LogTemp, Log, TEXT("LoginUIObject success @@@@@@@@@@@@@@"));
		}
	}
}