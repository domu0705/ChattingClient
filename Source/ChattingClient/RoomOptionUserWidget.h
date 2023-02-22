// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"
#include "ChattingClientManager.h"
#include "SocketManager.h"
#include "RoomOptionUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API URoomOptionUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		UButton* OKBtn = nullptr;
	UPROPERTY(meta = (BindWidget))
		UButton* CloseBtn = nullptr;
	UPROPERTY(meta = (BindWidget))
		UEditableTextBox* NameEditText;
	UPROPERTY(meta = (BindWidget))
		UEditableTextBox* NumEditText;
	
	UFUNCTION()
		void OKBtnClicked();
	UFUNCTION()
		void CloseBtnClicked();
};
