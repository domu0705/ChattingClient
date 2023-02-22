// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInfo.h"

UPlayerInfo::UPlayerInfo()
{
	//packetFlag->Add(USER_LIST, false);
	//packetFlag->Add(ROOM_LIST, false);
	playerState = WAITING;
	packetFlag = NON;
}

UPlayerInfo::~UPlayerInfo()
{
}

void UPlayerInfo::ResetInfo()
{
	UE_LOG(LogTemp, Log, TEXT("###################UPlayerInfo::UPlayerInfo()"));
	playerState = WAITING;
	packetFlag = NON;
}
int UPlayerInfo::GetPacketFlag()
{
	return packetFlag;
}
void UPlayerInfo::SetPacketFlag(int newFlag)
{
	packetFlag = newFlag;
}

int UPlayerInfo::GetPlayerState() 
{
	return playerState;
}
void UPlayerInfo::SetPlayerState(int newState)
{
	playerState = newState;
}
/*
TMap<int32, bool>* PlayerInfo::GetPacketFlag()
{
	return packetFlag;
}
*/