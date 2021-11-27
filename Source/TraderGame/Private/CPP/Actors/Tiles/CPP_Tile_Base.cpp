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

/*bool ACPP_Tile_Base::GetAllResourcesIn_Implementation(TArray<ResourceType>& resTypes)
{
	resTypes = ResourcesIn;
	return true;
}*/

/*bool ACPP_Tile_Base::CompareResourcesIn_DEPRECATED_Implementation(const TArray<ResourceType>& resTypes)
{
	if(resTypes.Num() > 0)
	{	
		// локальный массив со всеми видами требуемых ресурсов
		TArray<ResourceType> l_res;
		// заполнение уникальными типами ресурсов
		for(auto a: resTypes)
		{
			l_res.AddUnique(a);
		}

		for(auto b: l_res) // каждая итерация рассматривает один тип ресурсов
		{
			int l_req = 0; // счетчик ресурса, который нужен для постройки
			for (auto req: resTypes)
			{
				if (req == b) l_req++;
			}// на выходе получаем l_req равен количеству ресурса, которое должен производить тайл

			int l_in = 0; //счетчик ресурсов, которые производит земля
			for (auto in: ResourcesIn)
			{
				if (in == b) l_in++;
			}// l_in равняется кол-ву производимого рассматриваемого ресурса

			if(l_in < l_req) return false; //если земля не производит достаточное кол-во ресурса - ф-ия прекратит работу и выдаст false
		}

		return true;
	}

	return false;
}*/

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

	return true; // смысл такой, что если запрашиваемые ресурсы ничему не равняются - функция вернет, что "все окей"
}

bool ACPP_Tile_Base::GetTileTypeID(int32& tileType)
{
	tileType = ID_Type;
	return (tileType != 0);
}

bool ACPP_Tile_Base::GetResourcesIn_Implementation(const ResourceType& resType)
{
	return ResourcesIn.Contains(resType);
}

