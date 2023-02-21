// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SocketManager.h"
#include "ChattingClientGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API UChattingClientGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	//void SetSocketManager(USocketManager* packetManager);
	//USocketManager* GetSocketManager();
private:
	//USocketManager* SocketManager;
};
