// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CPP_BPFL_General.generated.h"
/**
 * 
 */
UCLASS()
class TRADERGAME_API UCPP_BPFL_General : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	public:

	UFUNCTION(BlueprintCallable)
	static bool ConvertLocationToTileLocation(const FVector& location, const float& tileWidth, const float& tileHeight, FVector& result);
};
