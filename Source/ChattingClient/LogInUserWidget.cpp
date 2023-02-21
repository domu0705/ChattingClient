// Fill out your copyright notice in the Description page of Project Settings.


#include "LogInUserWidget.h"

//위젯 클래스의 셍성자
void ULogInUserWidget::NativeConstruct()
{
	UE_LOG(LogTemp, Log, TEXT("NativeConstruct ���۵�@@@@@@@@@@@@@@"));
	Super::NativeConstruct();

	if (LogInBtn)
	{
		LogInBtn->OnClicked.AddDynamic(this, &ULogInUserWidget::LogInBtnClicked);
	}

	//SetLoginText();
	//if (Btn_LogIn)
	//{
	//	Btn_LogIn->OnClicked.AddDynamic(this, &ULogIn_UserWidget::Btn_LogIn_Func);
	//}
}


void ULogInUserWidget::SetLoginUI()
{
	//EditText_LogIn->SetHintText(FText::FromString(L"hihihi!"));/

}


void ULogInUserWidget::LogInBtnClicked()
{
	UE_LOG(LogTemp, Log, TEXT("버튼 시작@@@@@@@@@@@@@@"));
	FString tempStr = (IDEditText->GetText()).ToString();
	int32 tempCnt = FCString::Atoi(*tempStr);


	/*if (tempCnt > 0)
	{
		NPCBot->BuyItem1(tempCnt);
	}*/
}