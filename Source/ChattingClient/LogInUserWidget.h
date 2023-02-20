// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"

#include "LogInUserWidget.generated.h"

/**
 *
 */
UCLASS()
class CHATTINGCLIENT_API ULogInUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		UButton* LogInBtn = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UEditableTextBox* IDEditText;

	void SetLoginUI();

protected:

	UFUNCTION()
		void LogInBtnClicked(); 
};
