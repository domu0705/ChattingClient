// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetManager.h"
#include "LogInUserWidget.h"
#include "LobbyUserWidget.h"
#include "RoomOptionUserWidget.h"
#include "RoomUserWidget.h"
#include "RoomUserWidget.h"
#include "PrivateMsgUserWidget.h"
#include "PopUpUserWidget.h"
#include "SearchUserWidget.h"
#include <UObject/ConstructorHelpers.h>


UUserWidgetManager::UUserWidgetManager()
{
	manager = UChattingClientManager::GetInstance();
}

void UUserWidgetManager::StartUserWidgetManager()
{

}

// --------------------------------------------------------------------------------------
// 위젯을 viewPort에 올리기
// --------------------------------------------------------------------------------------
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

	FString path = "/Game/BP_Lobby";
	LobbyUIClass = ConstructorHelpersInternal::FindOrLoadClass(path, ULobbyUserWidget::StaticClass());
	if (!LobbyUIClass)
		return;

	LobbyUI = Cast<ULobbyUserWidget>(CreateWidget<UUserWidget>(world, LobbyUIClass));
	if (LobbyUI)
	{
		LobbyUI->AddToViewport();
		OnOffLobbyView(false);
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

	FString path = "/Game/BP_CreateRoom";
	RoomOptionUIClass = ConstructorHelpersInternal::FindOrLoadClass(path, URoomOptionUserWidget::StaticClass());
	if (!RoomOptionUIClass)
		return;

	RoomOptionUI = Cast<URoomOptionUserWidget>(CreateWidget<UUserWidget>(world, RoomOptionUIClass));
	if (RoomOptionUI)
	{
		RoomOptionUI->AddToViewport();
		OnOffRoomOptionView(false);
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

	FString path = "/Game/BP_Room";
	RoomUIClass = ConstructorHelpersInternal::FindOrLoadClass(path, URoomUserWidget::StaticClass());
	if (!RoomUIClass)
		return;

	RoomUI = Cast<URoomUserWidget>(CreateWidget<UUserWidget>(world, RoomUIClass));
	if (RoomUI)
	{
		RoomUI->AddToViewport();
		OnOffRoomView(false);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("@@@ CreateRoomView  fail "));
	}
}

void UUserWidgetManager::CreatePrivateMsgView(UWorld* world)
{
	if (!world)
		return;

	FString path = "/Game/BP_PrivateMsg";

	PrivateMsgUIClass = ConstructorHelpersInternal::FindOrLoadClass(path, UPrivateMsgUserWidget::StaticClass());
	if (!PrivateMsgUIClass)
		return;

	PrivateMsgUI = Cast<UPrivateMsgUserWidget>(CreateWidget<UUserWidget>(world, PrivateMsgUIClass));
	if (PrivateMsgUI)
	{
		PrivateMsgUI->AddToViewport();
		OnOffPrivateMsgView(false);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("@@@ CreatePrivateMsgView  fail "));
	}
}

void UUserWidgetManager::CreatePopUpView(UWorld* world)
{
	if (!world)
		return;

	FString path = "/Game/BP_PopUp";
	PopUpUIClass = ConstructorHelpersInternal::FindOrLoadClass(path, UPopUpUserWidget::StaticClass());
	if (!PopUpUIClass)
		return;

	PopUpUI = Cast<UPopUpUserWidget>(CreateWidget<UUserWidget>(world, PopUpUIClass));
	if (PopUpUI)
	{
		PopUpUI->AddToViewport();
		OnOffPopUpView(false);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("CreateRoomView  fail "));
	}
}

void UUserWidgetManager::CreateSearchView(UWorld* world)
{
	if (!world)
		return;

	FString path = "/Game/BP_Search";
	SearchUIClass = ConstructorHelpersInternal::FindOrLoadClass(path, USearchUserWidget::StaticClass());
	if (!SearchUIClass)
		return;

	SearchUI = Cast<USearchUserWidget>(CreateWidget<UUserWidget>(world, SearchUIClass));
	if (SearchUI)
	{
		SearchUI->AddToViewport();
		FString title = TEXT("검색할 방 번호:");
		OnOffSearchView(title,false);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("CreateSearchView  fail "));
	}
}

// --------------------------------------------------------------------------------------
// View On Off 관리
// --------------------------------------------------------------------------------------
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
		return;

	if (isVIsible)
	{
		UPlayerInfo* PlayerInfo = manager->GetPlayerInfo();
		PlayerInfo->SetPacketFlag(UPlayerInfo::ROOM_LIST);

		manager->GetSocket()->SendRoomList();
		LobbyUI->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		LobbyUI->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UUserWidgetManager::OnOffRoomOptionView(bool isVIsible)
{
	if (!RoomOptionUI)
		return;

	if (isVIsible)
	{
		RoomOptionUI->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		RoomOptionUI->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UUserWidgetManager::OnOffRoomView(bool isVIsible)
{
	if (!RoomUI)
		return;

	if (isVIsible)
	{
		RoomUI->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		RoomUI->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UUserWidgetManager::OnOffPrivateMsgView(bool isVIsible)
{
	if (!PrivateMsgUI)
		return;

	if (isVIsible)
	{
		PrivateMsgUI->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		PrivateMsgUI->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UUserWidgetManager::OnOffPopUpView(bool isVIsible)
{
	if (!PopUpUI)
		return;

	if (isVIsible)
	{
		PopUpUI->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		PopUpUI->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UUserWidgetManager::OnOffSearchView(FString& type, bool isVIsible)
{
	if (!SearchUI)
		return;

	if (isVIsible)
	{
		SearchUI->LoadTitleMsg(type);
		SearchUI->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SearchUI->SetVisibility(ESlateVisibility::Collapsed);
	}
}

//팝업창 메세지 갱신
void  UUserWidgetManager::UpdatePopUp(const FString& msg)
{
	PopUpUI->LoadPopUpMsg(msg);
}

//로비 정보창 정보 갱신
void UUserWidgetManager::UpdateList(const FString& msg)
{
	LobbyUI->LoadList(msg);
}

//채팅방 정보 갱신
void UUserWidgetManager::UpdateChatList(FString& msg)
{
	RoomUI->LoadChat(msg);
}
