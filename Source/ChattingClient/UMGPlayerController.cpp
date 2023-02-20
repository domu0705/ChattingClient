// Fill out your copyright notice in the Description page of Project Settings.
//여기서 마우스 커서 보이게 바꿔주어야 할듯

#include "UMGPlayerController.h"


void AUMGPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI()); //5:05
}