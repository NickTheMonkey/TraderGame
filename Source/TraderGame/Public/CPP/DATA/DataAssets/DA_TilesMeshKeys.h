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
	
	UPROPERTY(EditAnywhere)
	TMap<int32, TSubclassOf<ACPP_Tile_Base>> NumberToTile;

	
	public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure)
	bool GetTileType(const int32& tileID, TSubclassOf<ACPP_Tile_Base>& tileType);
};
