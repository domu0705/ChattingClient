// Copyright Epic Games, Inc. All Rights Reserved.


#include "ChattingClientGameModeBase.h"
#include "ChattingClientGameInstance.h"
#include <Blueprint/UserWidget.h>

//플레이가 시작되었을 때, 게임 모드에서 액터들의 BeginPlay() 함수를 호출하는 역할.
void AChattingClientGameModeBase::StartPlay()
{
	Super::StartPlay();
	auto aa = GetWorld();

	ChattingClientManager = UChattingClientManager::GetInstance(); // new UChattingClientManager();
	SocketManager = USocketManager::GetInstance();// new USocketManager();
	ChattingClientManager->SetSocket(SocketManager);
	//GameInstance->SetSocketManager(SocketManager);

}

void AChattingClientGameModeBase::BeginPlay()
{
	Super::BeginPlay();//내가 구현할 함수는 기존 절차의 끝부분에 한단계를 추가하기 위한 것이므로 super::BeginPlay함수를 맨처음에 호출.
	//PlayerControllerClass = AClientPlayerController::StaticClass();
	//ChangeMenuWidget(StartingWidgetClass);//게임 시작시 UI를 표시함

	//FString testString = TEXT("한글 테스트 완료");

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *testString);

	//UE_LOG(LogTemp, Log, TEXT("BeginPlay 시작됨@@@@@@@@@@@@@@"));

	UserWidgetManager = UUserWidgetManager::GetInstance();// new UUserWidgetManager(); //CreateDefaultSubobject<UUserWidgetManager>(TEXT("userWidgetManager"))
	UserWidgetManager->CreateLogInView( GetWorld() );
	UserWidgetManager->CreateLobbyView(GetWorld());
}

void AChattingClientGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//if (SocketManager != nullptr) SocketManager->Tick();
}


//endplay에서 UUserWidgetManager delete

