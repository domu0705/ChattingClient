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
		UButton* Btn_LogIn = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UEditableTextBox* ETxt_Id; // 아이템 목록1 구매 개수 입력 

	void SetLoginUI();

protected:

	UFUNCTION()
		void Btn_LogIn_Func(); // 인벤토리 닫기 버튼 누를 시 호출 될 함수
};
