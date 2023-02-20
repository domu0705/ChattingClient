// Fill out your copyright notice in the Description page of Project Settings.
//���⼭ ���콺 Ŀ�� ���̰� �ٲ��־�� �ҵ�

#include "UMGPlayerController.h"


void AUMGPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("AUMGPlayerController @@@@@@@@@@@@@@"));
	SetInputMode(FInputModeGameAndUI()); //5:05
}