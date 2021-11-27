// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP/Actors/Tiles/CPP_Tile_Base.h"

// Sets default values
ACPP_Tile_Base::ACPP_Tile_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ACPP_Tile_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Tile_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACPP_Tile_Base::GetTileTypeID(int32& tileType)
{
	tileType = ID_Type;
	return (tileType != 0);
}

bool ACPP_Tile_Base::ResourceToCanExtract_Implementation(const ResourceType& resType)
{
	return ResourcesIn.Contains(resType);
}

