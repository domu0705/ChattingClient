// Fill out your copyright notice in the Description page of Project Settings.
//안되면 actor class 상속받기.

#include "ConnSocket.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include "Engine.h"
#include "Runtime/Networking/Public/Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

ConnSocket::ConnSocket()
{
	port = 4444;
}

ConnSocket::~ConnSocket()
{

}

void ConnSocket::Send(FString& string)
{
	string += "\r\n";

	//int size = ;
	//int sent = ;

	//socket->Send(, size,sent );//uint8= 음수가 아닌, 8bit로 표현 가능한 숫자
	//Socket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent);
}

void ConnSocket::SendLogin(const FString& name)
{
	FString command = FString::Printf(TEXT("LOGIN %s\r\n"), *name);
	Send(command);
}


void ConnSocket::ConnectServer()
{
	socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	FString address = TEXT("127.0.0.1");
	FIPv4Address ip;
	
	FIPv4Address::Parse(address, ip);

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(port);

	if (socket->Connect(*addr)) {
		isConnected = true;
	}
}