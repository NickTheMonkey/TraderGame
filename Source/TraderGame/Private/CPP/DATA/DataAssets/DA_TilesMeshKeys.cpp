// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP/DATA/DataAssets/DA_TilesMeshKeys.h"

bool UDA_TilesMeshKeys::GetTileType_OLD_Implementation(const int32& tileID, TSubclassOf<ACPP_Tile_Base>& tileType)
{
	if(NumberToTile.Contains(tileID))
	{
		tileType = *NumberToTile.Find(tileID);
		return true;
	}
	return false;
}

void UDA_TilesMeshKeys::GetKeyRange_Implementation(int32& firstKey, int32& lastKey)
{
	firstKey = FirstKeyNumber;
	lastKey = LastKeyNumber;
}

float UDA_TilesMeshKeys::GetTileSize_Implementation()
{
	return TileSize;
}

TSubclassOf<ACPP_Tile_Base>& UDA_TilesMeshKeys::GetTileType_Implementation(const int32& tileID)
{
	if(NumberToTile.Contains(tileID))
	{
		return *NumberToTile.Find(tileID);
	}
}
