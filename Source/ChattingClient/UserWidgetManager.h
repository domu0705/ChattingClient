// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChattingClientManager.h"
#include "SocketManager.h"

#include "PlayerInfo.h"
/**
 * 
 */
class ULogInUserWidget;
class ULobbyUserWidget;
class URoomOptionUserWidget;
class URoomUserWidget;

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
	void CreateRoomOptionView(UWorld* world);
	void CreateRoomView(UWorld* world);
	void OnOffLogInView(bool isVIsible);
	void OnOffLobbyView(bool isVIsible);
	void OnOffRoomOptionView(bool isVisible);
	void OnOffRoomView(bool isVisible);
	void UpdateList(const FString& msg);
	void UpdateChatList(FString& msg);
	//void CreateUserWidgetClass();
	//virtual void BeginPlay() override; 여기 이거 못씀

private:
	USocketManager* GetPacketmanager();
	TSubclassOf<UUserWidget> LoginUIClass;
	TSubclassOf<UUserWidget> LobbyUIClass;
	TSubclassOf<UUserWidget> RoomOptionUIClass;
	TSubclassOf<UUserWidget> RoomUIClass;
	ULogInUserWidget* LoginUI;
	ULobbyUserWidget* LobbyUI;
	URoomOptionUserWidget* RoomOptionUI;
	URoomUserWidget* RoomUI;
	UChattingClientManager* manager;
	//TSharedPtr<UUserWidget> LoginUIObject;
	//LoginUIObject.IsValid();
	//UUserWidget* a = LoginUIObject.Get();

};
