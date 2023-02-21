// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetManager.h"
#include "LogInUserWidget.h"
#include "LobbyUserWidget.h"
#include <UObject/ConstructorHelpers.h>

//UI가 뷰포트에 추가되면(Add to ViewPort) 그 이후에 NativeContruct 함수가 호출
UUserWidgetManager::UUserWidgetManager()//(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)//userwidget은 생성자 호출 이렇게 해야함
{
	//static ConstructorHelpers::FClassFinder<UUserWidget> WB_Login(TEXT("/Game/BP_Login"));// 무조건 생성자에서만 호출WidgetBlueprint'/Game/BP_LogIn.BP_LogIn' BP오브젝트
	//if (WB_Login.Succeeded())
	//{
	//	LoginUIClass = WB_Login.Class;
	//	UE_LOG(LogTemp, Log, TEXT("success @@@@@@@@@@@@@@"));
	//}
}

void UUserWidgetManager::StartUserWidgetManager()
{
	//CreateUserWidgetClass();
	//CreateLogInView();
}

//위젯을 viewPort에 올리기
void UUserWidgetManager::CreateLogInView(UWorld* world)
{
	if (!world)
		return;

	FString path = "/Game/BP_Login";
	LoginUIClass = ConstructorHelpersInternal::FindOrLoadClass(path, ULogInUserWidget::StaticClass());
	if (!LoginUIClass)
		return;

	auto asd = CreateWidget<UUserWidget>( world, LoginUIClass);

	LoginUIObject = Cast<ULogInUserWidget>( asd );
	if (LoginUIObject)
	{
		LoginUIObject->AddToViewport();
	}
}

void UUserWidgetManager::CreateLobbyView(UWorld* world)
{
	if (!world)
		return;

	UE_LOG(LogTemp, Log, TEXT("@@@ CreateLobbyView"));

	FString path = "/Game/BP_Lobby";
	LobbyUIClass = ConstructorHelpersInternal::FindOrLoadClass(path, ULobbyUserWidget::StaticClass());
	if (!LobbyUIClass)
		return;

	LobbyUIObject = Cast<ULobbyUserWidget>(CreateWidget<UUserWidget>(world, LobbyUIClass));
	if (LobbyUIObject)
	{
		LobbyUIObject->AddToViewport();
		OnOffLobbyView(false);
		UE_LOG(LogTemp, Log, TEXT("@@@ LobbyUIObject success"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("@@@ LobbyUIObject  fail "));
	}
}

void UUserWidgetManager::OnOffLogInView(bool isVIsible)
{
	if (!LoginUIObject)
		return;

	if (isVIsible)
	{
		LoginUIObject->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		LoginUIObject->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UUserWidgetManager::OnOffLobbyView(bool isVIsible)
{
	UE_LOG(LogTemp, Log, TEXT("@@@ OnOffLobbyView"));
	if (!LobbyUIObject) {
		UE_LOG(LogTemp, Log, TEXT("@@@ OnOffLobbyView | LobbyUIObject nulllll"));
		return;
	}

	if (isVIsible)
	{
		UE_LOG(LogTemp, Log, TEXT("@@@ OnOffLobbyView | true"));
		LobbyUIObject->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("@@@ OnOffLobbyView | false"));
		LobbyUIObject->SetVisibility(ESlateVisibility::Collapsed);
	}
}