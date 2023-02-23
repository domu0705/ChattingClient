// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGPlayerController.h"


AUMGPlayerController::AUMGPlayerController()
{

}

void AUMGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly()); 
	bShowMouseCursor = true;
}