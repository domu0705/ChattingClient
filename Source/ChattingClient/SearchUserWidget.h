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
#include "Engine/EngineTypes.h"
#include "SearchUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API USearchUserWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	FString title;
public:
	void NativeConstruct() override;
	UPROPERTY(meta = (BindWidget))
		UButton* OKBtn = nullptr;
	UPROPERTY(meta = (BindWidget))
		UButton* CloseBtn = nullptr;
	UPROPERTY(meta = (BindWidget))
		UEditableTextBox* NumEditText;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TitleTextBox = nullptr;

	UFUNCTION()
		void OKBtnClicked();
	UFUNCTION()
		void CloseBtnClicked();
	UFUNCTION()
		void LoadTitleMsg(const FString& msg);
};
