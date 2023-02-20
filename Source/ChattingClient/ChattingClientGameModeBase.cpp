// Copyright Epic Games, Inc. All Rights Reserved.


#include "ChattingClientGameModeBase.h"
#include <Blueprint/UserWidget.h>

void AChattingClientGameModeBase::BeginPlay()
{
	Super::BeginPlay();//내가 구현할 함수는 기존 절차의 끝부분에 한단계를 추가하기 위한 것이므로 super::BeginPlay함수를 맨처음에 호출.
	//PlayerControllerClass = AClientPlayerController::StaticClass();
	ChangeMenuWidget(StartingWidgetClass);//게임 시작시 UI를 표시함
	
	//FString testString = TEXT("한글 테스트 완료");

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *testString);

	//UE_LOG(LogTemp, Log, TEXT("BeginPlay 시작됨@@@@@@@@@@@@@@"));

}


void AChattingClientGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)//먼저 현재 위젯이 비어있는지 검사
	{
		CurrentWidget->RemoveFromViewport();//화면에서 UI제거
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)//매개변수로 받은 NewWidgetClass가 유효한지 검사
	{
		CurrentWidget = CreateWidget(GetWorld(), NewWidgetClass);//CreateWidget()로 새위젯을 만들어 currentWidget에 저장한 뒤 뷰포트에 표시하도록 만듦
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}