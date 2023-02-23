// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInfo.h"


UPlayerInfo::UPlayerInfo()
{
	playerState = WAITING;
	packetFlag = NON;
}

UPlayerInfo::~UPlayerInfo()
{
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

//유저 정보 초기화
void UPlayerInfo::ResetInfo()
{
	playerState = WAITING;
	packetFlag = NON;
}