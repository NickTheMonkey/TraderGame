// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP/Actors/MapGenerator/CPP_MapGenerator.h"

#include "CPP/ActorComponents/CPP_AComp_Initializator.h"
#include "GameFramework/GameStateBase.h"

// Sets default values
ACPP_MapGenerator::ACPP_MapGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_MapGenerator::BeginPlay()
{
	Super::BeginPlay();

	CreateBinds();

	Initialization();
}

void ACPP_MapGenerator::CreateBinds()
{
	UCPP_AComp_Initializator* initializator = GetWorld()->GetGameState()->FindComponentByClass<UCPP_AComp_Initializator>();
	if(initializator)
	{
		initializator->OnMapSettingsChanged.BindUFunction(this, "Initialization");
	}
}

void ACPP_MapGenerator::Initialization()
{
	UCPP_AComp_Initializator* initializator = GetWorld()->GetGameState()->FindComponentByClass<UCPP_AComp_Initializator>();
	if(initializator)
	{
		initializator->Map_Get_Settings(GameMap.Width, GameMap.Height, MapSeed);
		GenerateMap();
	}
}

void ACPP_MapGenerator::GenerateMap() //TODO: до конца протестировать функцию
{
	GameMap.Tiles.Empty();
	for(auto a: MapElements)
		{
			if(a)
			{
				a->Destroy();
			}
		}
	MapElements.Empty();

	for(int x = 0; x < GameMap.Width; x++)
	{
		for(int y = 0; y < GameMap.Height; y++)
		{
			int32 seed = (GameMap.Width - y) * MapSeed * x * y;

			FRandomStream stream(seed);
			int32 l_from, l_to;
			Current_Tileset->GetKeyRange(l_from, l_to);
			seed = stream.RandRange(l_from, l_to);
			GameMap.Tiles.Add(seed);
		}
	}


	for(int x = 0; x < GameMap.Width; x++)
	{
		for(int y = 0; y < GameMap.Height; y++)
		{
			float tileSize = Current_Tileset->GetTileSize();
			FVector* location = new FVector;
			*location = {0.0f, 0.0f, 0.0f};

			location->X = tileSize * 0.8f * (float)x;
			location->Y = tileSize * 0.95f * (float)y;

			if(y%2 != 0)
			{
				location->Y += tileSize * 0.5f;
			};

			FVector actorLoc = GetActorLocation();
			actorLoc.X -= (float)GameMap.Width * 0.5f * tileSize;
			actorLoc.Y -= (float)GameMap.Height * 0.5f * tileSize;

			*location = *location + actorLoc;

			int32 tileID = GameMap.Tiles[x * GameMap.Width + y];
			if(tileID)
			{
				ACPP_Tile_Base* spawnedTile;
				spawnedTile = Cast<ACPP_Tile_Base>(GetWorld()->SpawnActor(Current_Tileset->GetTileType(GameMap.Tiles[tileID]), location));
				if(spawnedTile)
				{
					spawnedTile->Set_Tile_ID(tileID);
					MapElements.Add(spawnedTile);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Tile was not spawned"));
				}
			}


			location = nullptr;
			delete location;
		}
	}
}

// Called every frame
void ACPP_MapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

