// Copyright 2019 Rokoko Electronics. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interfaces/IHttpRequest.h"
#include "RokokoStudioCommandAPI.generated.h"

USTRUCT(BlueprintType)
struct FRokokoCommandAPI_IPInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category="Command API")
	FString IPAddress;

	UPROPERTY(BlueprintReadWrite, Category="Command API")
	FString Port;

	UPROPERTY(BlueprintReadWrite, Category="Command API")
	FString APIKey;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCompletedRequest, int32, ResponseCode, const FString&, ResponseContentString, bool, bSucceeded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTrackerRequest, FVector, Position, FQuat, Rotation);

/**
 * 
 */
UCLASS(Config="RokokoStudioCommandAPI",BlueprintType)
class SMARTSUIT_API URokokoStudioCommandAPI : public UObject
{
	GENERATED_BODY()
	
public:

	URokokoStudioCommandAPI();

	UFUNCTION(BlueprintCallable, Category="Command API")
	void Restart(const FRokokoCommandAPI_IPInfo& IPInfo, const FString& SmartSuitName);

	UFUNCTION(BlueprintCallable, Category="Command API")
	void Calibrate(const FRokokoCommandAPI_IPInfo& IPInfo, const FString& SmartSuitName, int32 CountdownDelay=3);

	UFUNCTION(BlueprintCallable, Category="Command API")
	void StartRecording(const FRokokoCommandAPI_IPInfo& IPInfo, const FString& FileName);

	UFUNCTION(BlueprintCallable, Category="Command API")
	void StopRecording(const FRokokoCommandAPI_IPInfo& IPInfo);

	UFUNCTION(BlueprintCallable, Category = "Command API")
	void Tracker(const FRokokoCommandAPI_IPInfo& IPInfo, const FString& DeviceId, const FString& BoneName, const FTransform& transform, float timeoutTime=2.f, bool isQueryOnly=false);

	UPROPERTY(BlueprintAssignable, Category="Command API")
	FOnCompletedRequest OnCompletedRequest;

	UPROPERTY(BlueprintAssignable, Category = "Command API")
	FOnTrackerRequest OnTrackerRequest;

	UPROPERTY(Config, BlueprintReadOnly, Category="Command API")
	FRokokoCommandAPI_IPInfo Default_IPInfo;

	UPROPERTY(Config, BlueprintReadOnly, Category="Command API")
	FString Default_SmartSuitName;

	UFUNCTION(BlueprintCallable, Category="Command API")
	void SaveConfigFile(const FRokokoCommandAPI_IPInfo& IPInfo, const FString& SmartSuitname);

	void OnProcessRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	void OnTrackerRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
};
