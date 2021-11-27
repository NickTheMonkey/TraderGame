// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameMap.generated.h"

USTRUCT(BlueprintType)
struct TRADERGAME_API FGameMap
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	uint8 Width;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	uint8 Height;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<int32> Tiles;
};
