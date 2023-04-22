// Fill out your copyright notice in the Description page of Project Settings.


#include "WebSocketClientSubsystem.h"
#include "WebSocketsModule.h"
#include "IWebSocket.h"

UWebSocketClientSubsystem::UWebSocketClientSubsystem()
{

}

void UWebSocketClientSubsystem::Deinitialize()
{
	Super::Deinitialize();
	if(Socket->IsConnected())
	{
		Socket->Close();
	}
}
void UWebSocketClientSubsystem::ConnectServer(const FString& URL)
{
	FModuleManager::Get().LoadModuleChecked("WebSockets");
	Socket=FWebSocketsModule::Get().CreateWebSocket(URL,"ws");
	
	Socket->OnConnected().AddUObject(this,&UWebSocketClientSubsystem::OnConnected);
	
	Socket->OnConnectionError().AddUObject(this,&UWebSocketClientSubsystem::OnConnectionError);
	
	Socket->OnClosed().AddUObject(this,&UWebSocketClientSubsystem::OnClosed);
	
	Socket->OnMessage().AddUObject(this,&UWebSocketClientSubsystem::OnMessage);
	
	Socket->OnMessageSent().AddUObject(this,&UWebSocketClientSubsystem::OnMessageSent);

	if(!Socket.IsValid()||Socket->IsConnected())
	{
		return;
	}
	Socket->Connect();
}

void UWebSocketClientSubsystem::CloseConnect()
{
	if(Socket->IsConnected())
	{
		Socket->Close();
	}
}

void UWebSocketClientSubsystem::SendMessage(const FString& Message)
{
	if(Socket->IsConnected())
	{
		Socket->Send(Message);
	}
}

void UWebSocketClientSubsystem::OnConnected()
{
	UE_LOG(LogTemp,Warning,TEXT("%s"),*FString(__FUNCTION__));
}

void UWebSocketClientSubsystem::OnConnectionError(const FString& Error)
{
	UE_LOG(LogTemp,Warning,TEXT("%s Error:%s"),*FString(__FUNCTION__),*Error);
}

void UWebSocketClientSubsystem::OnClosed(int32 StatusCode, const FString& Reason, bool bWasClean)
{
	UE_LOG(LogTemp,Warning,TEXT("%s StatusCode:%d Reason:%s bWasClean:%d"),
		*FString(__FUNCTION__),StatusCode,*Reason,bWasClean);
}

void UWebSocketClientSubsystem::OnMessage(const FString& Message)
{
	ReceiveMessage.Broadcast(Message);
	UE_LOG(LogTemp,Warning,TEXT("%s Message:%s"),*FString(__FUNCTION__),*Message);
}

void UWebSocketClientSubsystem::OnMessageSent(const FString& MessageString)
{
	UE_LOG(LogTemp,Warning,TEXT("%s MessageString:%s"),*FString(__FUNCTION__),*MessageString);
}
