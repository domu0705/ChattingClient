// Fill out your copyright notice in the Description page of Project Settings.


#include "LogInUserWidget.h"

//���� Ŭ������ �ļ���
void ULogInUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Btn_LogIn)
	{
		Btn_LogIn->OnClicked.AddDynamic(this, &ULogInUserWidget::Btn_LogIn_Func);
	}
	//if (Btn_LogIn)
	//{
	//	Btn_LogIn->OnClicked.AddDynamic(this, &ULogIn_UserWidget::Btn_LogIn_Func);
	//}
}


void ULogInUserWidget::SetLoginUI()
{
	//EditText_LogIn->SetHintText(FText::FromString(L"hihihi!"));//�г����� �Է��ϼ���

}


void ULogInUserWidget::Btn_LogIn_Func()
{
	FString tempStr = (ETxt_Id->GetText()).ToString();
	int32 tempCnt = FCString::Atoi(*tempStr);
	UE_LOG(LogTemp, Log, TEXT("BeginPlay ���۵�@@@@@@@@@@@@@@"));
	/*if (tempCnt > 0)
	{
		NPCBot->BuyItem1(tempCnt);
	}*/
}