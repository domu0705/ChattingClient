// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LogInUserWidget.h"
#include "UMGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API AUMGPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AUMGPlayerController();
	virtual void BeginPlay() override;

private:

	TSubclassOf<ULogInUserWidget> LoginUIClass;
	ULogInUserWidget* LoginUIObject;
};