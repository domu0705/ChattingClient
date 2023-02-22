// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/ScrollBox.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "LobbyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API ULobbyUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		UButton* RoomListBtn = nullptr;
	UPROPERTY(meta = (BindWidget))
		UScrollBox* ListScrollBox = nullptr;

	UFUNCTION()
		void RoomListBtnClicked();

	UFUNCTION()
		void LoadRoomList(const FString& msg);
};
