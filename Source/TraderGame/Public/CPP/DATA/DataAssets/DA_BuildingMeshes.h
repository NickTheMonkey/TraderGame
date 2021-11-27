// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CPP/DATA/CPP_ENUMS.h"
#include "Engine/DataAsset.h"
#include "DA_BuildingMeshes.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TRADERGAME_API UDA_BuildingMeshes : public UDataAsset
{
	GENERATED_BODY()

	protected:
	UPROPERTY(EditAnywhere)
	TMap<BuildingType, UStaticMesh*> BuildingMeshes;

	public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure)
	UStaticMesh* GetMeshValue(const BuildingType& buildingType, bool& success);
};
