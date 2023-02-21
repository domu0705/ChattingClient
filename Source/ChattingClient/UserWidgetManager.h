// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SocketManager.h"
#include "LogInUserWidget.h"

/**
 * 
 */
class CHATTINGCLIENT_API UUserWidgetManager
{
	//virtual void NativeConstruct() override;
public:
	static UUserWidgetManager* GetInstance() {
		static UUserWidgetManager s;
		return &s;
	}

	UUserWidgetManager();
	void StartUserWidgetManager();
	void CreateLogInView(UWorld* world);
	void CreateLobbyView(UWorld* world);

	void OnOffLogInView(bool isVIsible);
	void OnOffLobbyView(bool isVIsible);
	//void CreateUserWidgetClass();
	//virtual void BeginPlay() override; 여기 이거 못씀

private:
	USocketManager* GetPacketmanager();
	TSubclassOf<UUserWidget> LoginUIClass;
	TSubclassOf<UUserWidget> LobbyUIClass;
	UUserWidget* LoginUIObject;
	UUserWidget* LobbyUIObject;
	//TSharedPtr<UUserWidget> LoginUIObject;
	//LoginUIObject.IsValid();
	//UUserWidget* a = LoginUIObject.Get();

};
