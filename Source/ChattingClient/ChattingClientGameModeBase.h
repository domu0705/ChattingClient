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
	UFUNCTION(BlueprintCallable, Category = "UMG_Game") //UFunction ��ũ�θ� ���� �� �Լ��� �������Ʈ���� ȣ���� �� �ֵ��� ��
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	virtual void BeginPlay() override;//�̺�Ʈ �Լ�


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;//������ ���۵� �� ǥ�õ� ������ ����
	//TSubclassOf Ÿ���� UE���� UClass Ÿ�� �������� �����ϴ� ���ø� Ŭ������
	//TSubclassOf �� ���޵� ����� <> �ȿ� �־��� ���ø� ���� Ÿ�԰� ��ġ�ϰų�,
	//���ø� ���ڷ� ���� Ÿ���� ��ӹ��� Ÿ�������� ��Ÿ�� �߿� Ȯ���ϵ��� ���� Ŭ������

	UPROPERTY()
		UUserWidget* CurrentWidget;//���� ȭ�鿡 ǥ�õǰ� �ִ� UI ������ ���夷�� ������Ÿ���� ����

};
