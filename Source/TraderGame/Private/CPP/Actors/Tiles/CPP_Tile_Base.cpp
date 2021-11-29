// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP/Actors/Tiles/CPP_Tile_Base.h"

// Sets default values
ACPP_Tile_Base::ACPP_Tile_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/*USceneComponent* rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));*/
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

bool ACPP_Tile_Base::CompareResourcesIn_Implementation(const TMap<ResourceType, float>& resTypes)
{
	if (resTypes.Num() > 0)
	{
		for (auto a: resTypes)
		{
			if(ResourcesIn.Contains(a.Key))
			{
				if(*ResourcesIn.Find(a.Key) < a.Value) return false;
			}
			else
			{
				return false;
			}
		}
	}

	return true; // смысл такой, что если запрашиваемые ресурсы ничему не равн€ютс€ - функци€ вернет, что "все окей"
}

bool ACPP_Tile_Base::Get_Tile_ID(int32& tileType)
{
	tileType = Tile_ID;
	return (tileType != 0);
}

void ACPP_Tile_Base::Set_Tile_ID_Implementation(const int32& newID)
{
	Tile_ID = newID;
}

bool ACPP_Tile_Base::GetResourcesIn_Implementation(const ResourceType& resType)
{
	return ResourcesIn.Contains(resType);
}

