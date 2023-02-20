// Copyright Epic Games, Inc. All Rights Reserved.


#include "ChattingClientGameModeBase.h"
#include <Blueprint/UserWidget.h>

void AChattingClientGameModeBase::BeginPlay()
{
	Super::BeginPlay();//���� ������ �Լ��� ���� ������ ���κп� �Ѵܰ踦 �߰��ϱ� ���� ���̹Ƿ� super::BeginPlay�Լ��� ��ó���� ȣ��.
	//PlayerControllerClass = AClientPlayerController::StaticClass();
	ChangeMenuWidget(StartingWidgetClass);//���� ���۽� UI�� ǥ����
	
	//FString testString = TEXT("�ѱ� �׽�Ʈ �Ϸ�");

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *testString);

	//UE_LOG(LogTemp, Log, TEXT("BeginPlay ���۵�@@@@@@@@@@@@@@"));

}


void AChattingClientGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)//���� ���� ������ ����ִ��� �˻�
	{
		CurrentWidget->RemoveFromViewport();//ȭ�鿡�� UI����
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)//�Ű������� ���� NewWidgetClass�� ��ȿ���� �˻�
	{
		CurrentWidget = CreateWidget(GetWorld(), NewWidgetClass);//CreateWidget()�� �������� ����� currentWidget�� ������ �� ����Ʈ�� ǥ���ϵ��� ����
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}