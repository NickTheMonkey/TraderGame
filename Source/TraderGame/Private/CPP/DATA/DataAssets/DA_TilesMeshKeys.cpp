// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP/DATA/DataAssets/DA_TilesMeshKeys.h"

bool UDA_TilesMeshKeys::GetTileType_Implementation(const int32& tileID, TSubclassOf<ACPP_Tile_Base>& tileType)
{
	if(NumberToTile.Contains(tileID))
	{
		tileType = *NumberToTile.Find(tileID);
		return true;
	}
	return false;
}
