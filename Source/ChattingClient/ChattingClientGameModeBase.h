// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ChattingClientGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class CHATTINGCLIENT_API AChattingClientGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UMG_Game") //UFunction 메크로를 통해 이 함수를 블루프린트에서 호출할 수 있도록 함
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	virtual void StartPlay() override;
	virtual void BeginPlay() override;//이벤트 함수

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;//게임이 시작될 때 표시될 위젯을 저장
	//TSubclassOf 타입은 UE에서 UClass 타입 안정성을 보장하는 템플릿 클래스임
	//TSubclassOf 에 전달된 대상이 <> 안에 넣어준 템플릿 인자 타입과 일치하거나,
	//템플릿 인자로 받은 타입을 상속받은 타입인지를 런타임 중에 확인하도록 돕는 클래스임

	UPROPERTY()
		UUserWidget* CurrentWidget;//현재 화면에 표시되고 있는 UI 위젯을 저장ㅇ할 포인터타입의 변수

};