// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP/DATA/DataAssets/DA_TilesMeshKeys.h"

void UDA_TilesMeshKeys::GetKeyRange_Implementation(int32& firstKey, int32& lastKey)
{
	firstKey = FirstKeyNumber;
	lastKey = LastKeyNumber;
}

float UDA_TilesMeshKeys::GetTileSize_Implementation()
{
	return TileSize;
}

bool UDA_TilesMeshKeys::GetTileType_Implementation(const int32& tileID, TSubclassOf<ACPP_Tile_Base>& result)
{
	if(NumberToTile.Contains(tileID))
	{
		result = *NumberToTile.Find(tileID);
		return true;
	}
	return false;
}
