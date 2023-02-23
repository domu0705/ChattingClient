// Fill out your copyright notice in the Description page of Project Settings.


#include "PopUpUserWidget.h"

void UPopUpUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!CloseBtn)
		return;
	CloseBtn->OnClicked.AddDynamic(this, &UPopUpUserWidget::CloseBtnClicked);
}

void UPopUpUserWidget::CloseBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT(" UPopUpUserWidget::CloseBtnClicked()"));
	UUserWidgetManager* UImanager = UUserWidgetManager::GetInstance();
	UImanager->OnOffPopUpView(false);
}

// 팝업 택스트 업데이트
void UPopUpUserWidget::LoadPopUpMsg(const FString& msg)
{
	UE_LOG(LogTemp, Log, TEXT(" !@!@!@!@ ULobbyUserWidget::LoadRoomList ,%s"), *msg);
	MsgScrollBox->ClearChildren();

	UTextBlock* NewTextBlock = NewObject<UTextBlock>(MsgScrollBox);

	//UFont* Font = Cast<UFont>(StaticLoadObject(UFont::StaticClass(), nullptr, TEXT("Font'/Game/Resource/netM_.netM_'")));

	//FSlateFontInfo FontInfo;
	//FontInfo.Size = 25;

	//NewTextBlock->SetFont(FontInfo);
	//const FTextBlockStyle& CurrentStyle = NewTextBlock->GetDefaultFontName() ;


	NewTextBlock->SetText(FText::FromString(msg));
	MsgScrollBox->AddChild(NewTextBlock);
}