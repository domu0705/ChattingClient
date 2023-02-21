// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
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

	UFUNCTION()
		void RoomListBtnClicked();
};
