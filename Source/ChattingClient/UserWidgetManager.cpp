// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetManager.h"
#include "LogInUserWidget.h"
#include "LobbyUserWidget.h"
#include "RoomOptionUserWidget.h"
#include "RoomUserWidget.h"
#include <UObject/ConstructorHelpers.h>

//UI가 뷰포트에 추가되면(Add to ViewPort) 그 이후에 NativeContruct 함수가 호출
UUserWidgetManager::UUserWidgetManager()//(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)//userwidget은 생성자 호출 이렇게 해야함
{
	manager = UChattingClientManager::GetInstance();
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

	LoginUI = Cast<ULogInUserWidget>( asd );
	if (LoginUI)
	{
		LoginUI->AddToViewport();
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

	LobbyUI = Cast<ULobbyUserWidget>(CreateWidget<UUserWidget>(world, LobbyUIClass));
	if (LobbyUI)
	{
		LobbyUI->AddToViewport();
		OnOffLobbyView(false);
		UE_LOG(LogTemp, Log, TEXT("@@@ LobbyUIObject success"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("@@@ LobbyUIObject  fail "));
	}
}

void UUserWidgetManager::CreateRoomOptionView(UWorld* world)
{
	if (!world)
		return;

	UE_LOG(LogTemp, Log, TEXT("@@@ CreateRoomOptionView"));

	FString path = "/Game/BP_CreateRoom";
	RoomOptionUIClass = ConstructorHelpersInternal::FindOrLoadClass(path, URoomOptionUserWidget::StaticClass());
	if (!RoomOptionUIClass)
		return;

	RoomOptionUI = Cast<URoomOptionUserWidget>(CreateWidget<UUserWidget>(world, RoomOptionUIClass));
	if (RoomOptionUI)
	{
		RoomOptionUI->AddToViewport();
		OnOffRoomOptionView(false);
		UE_LOG(LogTemp, Log, TEXT("@@@ LobbyUIObject success"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("@@@ LobbyUIObject  fail "));
	}
}

void UUserWidgetManager::CreateRoomView(UWorld* world)
{
	if (!world)
		return;

	UE_LOG(LogTemp, Log, TEXT("@@@ CreateRoomView"));

	FString path = "/Game/BP_Room";
	RoomUIClass = ConstructorHelpersInternal::FindOrLoadClass(path, URoomUserWidget::StaticClass());
	if (!RoomUIClass)
		return;

	RoomUI = Cast<URoomUserWidget>(CreateWidget<UUserWidget>(world, RoomUIClass));
	if (RoomUI)
	{
		RoomUI->AddToViewport();
		OnOffRoomView(false);
		UE_LOG(LogTemp, Log, TEXT("@@@ CreateRoomView success"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("@@@ CreateRoomView  fail "));
	}
}

void UUserWidgetManager::OnOffLogInView(bool isVIsible)
{
	if (!LoginUI)
		return;

	if (isVIsible)
	{
		OnOffLobbyView(false);
	}
	else
	{
		LoginUI->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UUserWidgetManager::OnOffLobbyView(bool isVIsible)
{
	if (!LobbyUI) 
	{
		UE_LOG(LogTemp, Log, TEXT("@@@ OnOffLobbyView | LobbyUIObject nulllll"));
		return;
	}

	if (isVIsible)
	{
		UE_LOG(LogTemp, Log, TEXT("@@@ OnOffLobbyView | true"));
		UPlayerInfo* PlayerInfo = manager->GetPlayerInfo();
		PlayerInfo->SetPacketFlag(UPlayerInfo::ROOM_LIST);

		manager->GetSocket()->SendRoomList();
		LobbyUI->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("@@@ OnOffLobbyView | false"));
		LobbyUI->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UUserWidgetManager::OnOffRoomOptionView(bool isVIsible)
{
	UE_LOG(LogTemp, Log, TEXT("@@@  UUserWidgetManager::OnOffRoomOptionView()"));
	if (!RoomOptionUI)
	{
		UE_LOG(LogTemp, Log, TEXT("@@@  없음"));
		return;
	}

	if (isVIsible)
	{
		UE_LOG(LogTemp, Log, TEXT("@@@  UUserWidgetManager::OnOffRoomOptionView() | SetVisibility(ESlateVisibility::Visible)"));
		RoomOptionUI->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		RoomOptionUI->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UUserWidgetManager::OnOffRoomView(bool isVIsible)
{
	UE_LOG(LogTemp, Log, TEXT("@@@  UUserWidgetManager::OnOffRoomView()"));
	if (!RoomUI)
	{
		UE_LOG(LogTemp, Log, TEXT("@@@  없음"));
		return;
	}

	if (isVIsible)
	{
		UE_LOG(LogTemp, Log, TEXT("@@@  UUserWidgetManager::OnOffRoomView() | SetVisibility(ESlateVisibility::Visible)"));
		RoomUI->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		RoomUI->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UUserWidgetManager::UpdateList(const FString& msg)
{
	UE_LOG(LogTemp, Log, TEXT("@@@ UUserWidgetManager::UpdateRoomList %s"),*msg);
	LobbyUI->LoadList(msg);
	//LobbyUIObject LoadRoomList(msg);
}

void UUserWidgetManager::UpdateChatList(FString& msg)
{
	UE_LOG(LogTemp, Log, TEXT("@@@ UUserWidgetManager::UpdateChatList %s"), *msg);
	RoomUI->LoadChat(msg);
	//LobbyUIObject LoadRoomList(msg);
}
