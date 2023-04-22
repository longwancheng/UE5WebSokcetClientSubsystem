// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IWebSocket.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WebSocketClientSubsystem.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReceiveMessage, FString, str);
UCLASS()
class WEBSOCKETCLIENT_API UWebSocketClientSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UWebSocketClientSubsystem();
	//结束时调用
	virtual void Deinitialize() override;
	
	UFUNCTION(BlueprintCallable,Category="WebSocketClientSubsystem")
	void ConnectServer(const FString& URL);
	
	UFUNCTION(BlueprintCallable,Category="WebSocketClientSubsystem")
	void CloseConnect();

	UFUNCTION(BlueprintCallable,Category="WebSocketClientSubsystem")
	void SendMessage(const FString& Message);
	
private:
	TSharedPtr<IWebSocket>Socket = nullptr;
	
	UPROPERTY(BlueprintAssignable,Category="WebSocketClientSubsystem")
	FReceiveMessage ReceiveMessage;
	
protected:
	void OnConnected();
	
	void OnConnectionError(const FString& Error);
	
	void OnClosed(int32 StatusCode,const FString& Reason,bool bWasClean);
	
	void OnMessage(const FString& Message);//接收消息时
	
	void OnMessageSent(const FString& MessageString); //发送消息时
};

