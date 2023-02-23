// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UserWidgetManager.h"
#include "SocketManager.h"
#include "ChattingClientManager.h"
#include "PlayerInfo.h"
#include "ChattingClientGameModeBase.generated.h"


UCLASS()
class CHATTINGCLIENT_API AChattingClientGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


protected:
	UPROPERTY()
		UUserWidget* CurrentWidget;

	virtual void StartPlay() override;
	virtual void BeginPlay() override;

private:
	UUserWidgetManager* UserWidgetManager;
	UChattingClientManager* ChattingClientManager;
	USocketManager* SocketManager;
	UPlayerInfo* PlayerInfo;

	virtual void Tick(float DeltaSeconds) override;

public:
	AChattingClientGameModeBase();
};