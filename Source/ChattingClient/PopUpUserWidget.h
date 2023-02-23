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
#include "PopUpUserWidget.generated.h"


UCLASS()
class CHATTINGCLIENT_API UPopUpUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		UButton* CloseBtn = nullptr;
	UPROPERTY(meta = (BindWidget))
		UScrollBox* MsgScrollBox = nullptr;

	UFUNCTION()
		void CloseBtnClicked();
	UFUNCTION()
		void LoadPopUpMsg(const FString& msg);
};
