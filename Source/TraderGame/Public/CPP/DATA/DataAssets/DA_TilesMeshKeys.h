// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CPP/Actors/Tiles/CPP_Tile_Base.h"
#include "Engine/DataAsset.h"
#include "DA_TilesMeshKeys.generated.h"


UCLASS(BlueprintType)
class TRADERGAME_API UDA_TilesMeshKeys : public UDataAsset
{
	GENERATED_BODY()
	
	protected:

	UPROPERTY(EditAnywhere, meta = (Tooltip = "First key number for randomizer (if numbers not defined - randomize will generate empty tile)"))
	int32 FirstKeyNumber;
	UPROPERTY(EditAnywhere,  meta = (Tooltip = "Last key number for randomizer (if numbers not defined - randomize will generate empty tile)"))
	int32 LastKeyNumber;

	UPROPERTY(EditAnywhere)
	float TileSize = 100.0f;
	
	UPROPERTY(EditAnywhere)
	TMap<int32, TSubclassOf<ACPP_Tile_Base>> NumberToTile;	
	
	public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure)
	TSubclassOf<ACPP_Tile_Base> GetTileType(const int32& tileID);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure)
	void GetKeyRange(int32& firstKey, int32& lastKey);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure)
	float GetTileSize();
};
