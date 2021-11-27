// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ResourceType : uint8
{
	RT_Food	UMETA(DisplayName = "Food"),
	RT_Iron UMETA(DisplayName = "Iron"),
	RT_Coil UMETA(DisplayName = "Coil"),
	RT_Gold UMETA(DisplayName = "Gold"),

	RT_Resources_Count
};

UENUM(BlueprintType)
enum class BuildingType : uint8
{
    BT_Mill  UMETA(DisplayName = "Mill"),
    BT_Forge UMETA(DisplayName = "Forge"),
    BT_Mine  UMETA(DisplayName = "Mine"),
    
    BT_Buildings_Count
};