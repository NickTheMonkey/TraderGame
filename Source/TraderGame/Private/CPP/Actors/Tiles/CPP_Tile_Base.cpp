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
		// ��������� ������ �� ����� ������ ��������� ��������
		TArray<ResourceType> l_res;
		// ���������� ����������� ������ ��������
		for(auto a: resTypes)
		{
			l_res.AddUnique(a);
		}

		for(auto b: l_res) // ������ �������� ������������� ���� ��� ��������
		{
			int l_req = 0; // ������� �������, ������� ����� ��� ���������
			for (auto req: resTypes)
			{
				if (req == b) l_req++;
			}// �� ������ �������� l_req ����� ���������� �������, ������� ������ ����������� ����

			int l_in = 0; //������� ��������, ������� ���������� �����
			for (auto in: ResourcesIn)
			{
				if (in == b) l_in++;
			}// l_in ��������� ���-�� ������������� ���������������� �������

			if(l_in < l_req) return false; //���� ����� �� ���������� ����������� ���-�� ������� - �-�� ��������� ������ � ������ false
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

	return true; // ����� �����, ��� ���� ������������� ������� ������ �� ��������� - ������� ������, ��� "��� ����"
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

