// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/ScrollBox.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "ChattingClientManager.h"
#include "SocketManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LobbyUserWidget.generated.h"


UCLASS()
class CHATTINGCLIENT_API ULobbyUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		UButton* RoomListBtn = nullptr;
	UPROPERTY(meta = (BindWidget))
		UButton* UserListBtn = nullptr;
	UPROPERTY(meta = (BindWidget))
		UButton* CreateRoomBtn = nullptr;
	UPROPERTY(meta = (BindWidget))
		UButton* JoinRoomBtn = nullptr;
	UPROPERTY(meta = (BindWidget))
		UButton* PrivateMsgBtn = nullptr;
	UPROPERTY(meta = (BindWidget))
		UButton* RoomInfoBtn = nullptr;
	UPROPERTY(meta = (BindWidget))
		UButton* UserInfoBtn = nullptr;
	UPROPERTY(meta = (BindWidget))
		UButton* QuitBtn = nullptr;
	UPROPERTY(meta = (BindWidget))
		UScrollBox* ListScrollBox = nullptr;

	UFUNCTION()
		void RoomListBtnClicked();
	UFUNCTION()
		void UserListBtnClicked();
	UFUNCTION()
		void CreateRoomBtnClicked();
	UFUNCTION()
		void PrivateMsgBtnClicked();
	UFUNCTION()
		void RoomInfoBtnClicked();
	UFUNCTION()
		void UserInfoBtnClicked();
	UFUNCTION()
		void JoinRoomBtnClicked();
	UFUNCTION()
		void LoadList(const FString& msg);
	UFUNCTION()
		void QuitBtnClicked();
};
