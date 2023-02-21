// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LogInUserWidget.h"

/**
 * 
 */
class UUserWidgetManager
{
	//virtual void NativeConstruct() override;
public:
	UUserWidgetManager();
	void StartUserWidgetManager();
	void CreateLogInView(UWorld* world);
	//void CreateUserWidgetClass();
	//virtual void BeginPlay() override; 여기 이거 못씀

private:

	TSubclassOf<UUserWidget> LoginUIClass;
	UUserWidget* LoginUIObject;
};
