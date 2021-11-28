// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../DATA/CPP_ENUMS.h"

#include "CPP_BPI_Resources.generated.h"


/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UCPP_BPI_Resources : public UInterface
{
	GENERATED_BODY()
	
};

class TRADERGAME_API ICPP_BPI_Resources
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources")
	void Resources_Initialization();
	
#pragma region SETTERS
	// increase one type resource
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources|General|Set")
	bool Resources_Increase(const ResourceType& resType, const float& amount);
	// increase few types of resources
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources|General|Set")
	bool Resources_Increase_Array(const TMap<ResourceType, float>& resources);

	// decrease one type resource
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources|General|Set")
	bool Resources_Decrease(const ResourceType& resType, const float& amount);
	// decrease few types of resources
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources|General|Set")
	bool Resources_Decrease_Array(const TMap<ResourceType, float>& resources);
#pragma endregion SETTERS

#pragma region GETTERS
	// get amount of one type resource
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources|General|Get")
	bool Resources_Get_Amount(const ResourceType& resType, float& amount);
	// check amount of one type resource
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources|General|Get")
	bool Resources_Get_Enough(const ResourceType& resType, const float& amount);
	// get amount of few types resources
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources|General|Get")
	bool Resources_Get_Enough_Array(const TMap<ResourceType, float>& resources);
	// get amount of all types resources
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources|General|Get")
	TMap<ResourceType, float> Resources_Get_AllType_Amount();
	
#pragma endregion GETTERS

#pragma region TRADE

	// buy resource
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources|Trade")
	bool Resources_Buy(const ResourceType& resType, const float& amount);
	//sell resource
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources|Trade")
	bool Resources_Sell(const ResourceType& resType, const float& amount);
	
#pragma endregion TRADE
};