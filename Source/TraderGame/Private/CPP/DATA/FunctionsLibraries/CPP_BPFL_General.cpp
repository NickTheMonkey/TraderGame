// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP/DATA/FunctionsLibraries/CPP_BPFL_General.h"


bool UCPP_BPFL_General::ConvertLocationToTileLocation(const FVector& location, const float& tileWidth,
	const float& tileHeight, FVector& result)
{
	FVector l_loc;
	l_loc.X = (round(location.X/tileWidth))*tileWidth;
	l_loc.Y = (round(location.Y/tileHeight))*tileHeight;
	
	/*FIntVector l_loc;
	l_loc.X = round(location.X);
	l_loc.Y = round(location.Y);*/

	
	
	return false;
}
