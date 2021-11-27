// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP/DATA/DataAssets/DA_BuildingMeshes.h"

UStaticMesh* UDA_BuildingMeshes::GetMeshValue_Implementation(const BuildingType& buildingType, bool& success)
{
	if (BuildingMeshes.Contains(buildingType))
	{
		success = true;
		return *BuildingMeshes.Find(buildingType);		
	};
	
	success = false;
	return nullptr;
}
