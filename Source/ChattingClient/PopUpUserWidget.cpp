// Fill out your copyright notice in the Description page of Project Settings.


#include "PopUpUserWidget.h"

//버튼 이벤트와 함수 연결
void UPopUpUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!CloseBtn)
		return;
	CloseBtn->OnClicked.AddDynamic(this, &UPopUpUserWidget::CloseBtnClicked);
}

//팝업창 보여주기
void UPopUpUserWidget::CloseBtnClicked()
{
	UUserWidgetManager* UImanager = UUserWidgetManager::GetInstance();
	UImanager->OnOffPopUpView(false);
}

// 팝업창 택스트 업데이트
void UPopUpUserWidget::LoadPopUpMsg(const FString& msg)
{
	MsgScrollBox->ClearChildren();

	UTextBlock* NewTextBlock = NewObject<UTextBlock>(MsgScrollBox);
	NewTextBlock->SetText(FText::FromString(msg));
	MsgScrollBox->AddChild(NewTextBlock);
}