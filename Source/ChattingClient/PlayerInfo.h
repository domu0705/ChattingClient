// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class CHATTINGCLIENT_API UPlayerInfo
{
public:
    enum State
    {
        WAITING,
        LOBBY,
        ROOM,
        LOGOUT
    };
    enum Packet// 쪽지 따로 처리
    {
        NON,
        USER_LIST,
        ROOM_LIST,
        ROOM_INFO,
        USER_INFO,
        SEND_NOTE,//쪽지 보내기
        CREATE_ROOM,
        JOIN_ROOM,
        X,
    };

private:
	//TMap<int32, bool>* packetFlag;
	int packetFlag;
	int playerState;
public:
    static UPlayerInfo* GetInstance() {
        static UPlayerInfo s;
        return &s;
    }

	UPlayerInfo();
	~UPlayerInfo();
    void ResetInfo();
	//TMap<int32, bool>* GetPacketFlag();
	int GetPacketFlag();
    void SetPacketFlag(int newFlag);
    int GetPlayerState();
    void SetPlayerState(int newState);


};

/*
class MyClass
{
public:
    enum MyEnum
    {
        Value1,
        Value2,
        Value3
    };
};

// Use the enum in AnotherClass
class AnotherClass
{
public:
    void MyFunction(MyClass::MyEnum value)
    {
        // Use the enum value
        if (value == MyClass::Value1)
        {
            // Do something
        }
        else if (value == MyClass::Value2)
        {
            // Do something else
        }
        else if (value == MyClass::Value3)
        {
            // Do yet another thing
        }
    }
};
*/
/*
class MyClass
{
public:
    enum class MyEnum
    {
        Value1,
        Value2,
        Value3
    };

    void MyFunction(MyEnum value)
    {
        // Use the enum value
        if (value == MyEnum::Value1)
        {
            // Do something
        }
        else if (value == MyEnum::Value2)
        {
            // Do something else
        }
        else if (value == MyEnum::Value3)
        {
            // Do yet another thing
        }
    }
};

int main()
{
    MyClass myObject;
    myObject.MyFunction(MyClass::MyEnum::Value1);
    myObject.MyFunction(MyClass::MyEnum::Value2);
    myObject.MyFunction(MyClass::MyEnum::Value3);
    return 0;
}
*/