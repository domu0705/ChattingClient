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
#include "RoomUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API URoomUserWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	FString chatLog;

public:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		UButton* SendBtn = nullptr;
	UPROPERTY(meta = (BindWidget))
		UButton* QuitBtn = nullptr;
	UPROPERTY(meta = (BindWidget))
		UScrollBox* ChatScrollBox = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UEditableTextBox* ChatEditText;

	UFUNCTION()
		void SendBtnClicked();
	UFUNCTION()
		void QuitBtnClicked();
	UFUNCTION()
		void LoadChat(FString& msg);
};
