// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


class CHATTINGCLIENT_API UPlayerInfo
{
public:
    enum State //유저 상태 
    {
        WAITING,
        LOBBY,
        ROOM,
        LOGOUT
    };
    enum Packet// 요청한 패킷 상태
    {
        NON,
        USER_LIST,
        ROOM_LIST,
        ROOM_INFO,
        WAIT_JOIN,
        USER_INFO,
        SEND_NOTE,
        CREATE_ROOM,
        JOIN_ROOM,
        WAIT_ROOM_CREATION,
        WAIT_PRIVATE_MSG,
        QUIT_WAIT,
        DEL_WAIT,
        LOGOUT_WAIT,
        X,
    };

private:
	int packetFlag;
	int playerState;

public:
    static UPlayerInfo* GetInstance() {
        static UPlayerInfo s;
        return &s;
    }

	UPlayerInfo();
	~UPlayerInfo();

	int GetPacketFlag();
    void SetPacketFlag(int newFlag);
    int GetPlayerState();
    void SetPlayerState(int newState);

    void ResetInfo();


};