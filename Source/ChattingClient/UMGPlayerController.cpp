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

}

void AUMGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//SetInputMode 는 player controller가 가지고 있는 변수임
	SetInputMode(FInputModeUIOnly()); //5:05 게임과 UI모두 입력 가능한 상태가 됨  FInputModeGameAndUI 
	bShowMouseCursor = true;

}