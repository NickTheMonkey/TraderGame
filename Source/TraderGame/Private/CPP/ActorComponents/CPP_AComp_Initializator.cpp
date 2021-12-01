// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP/ActorComponents/CPP_AComp_Initializator.h"

#include "CPP/ActorComponents/CPP_AComp_Resource.h"

// Sets default values for this component's properties
UCPP_AComp_Initializator::UCPP_AComp_Initializator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UCPP_AComp_Initializator::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Prices.Init(100.f, static_cast<int32>(ResourceType::RT_Resources_Count));
}


// Called every frame
void UCPP_AComp_Initializator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

#pragma region Map // Map starting settings
bool UCPP_AComp_Initializator::Map_Set_Settings(const uint8& width, const uint8& height, const int32& seed)
{
	if(width>0 && height >0)
	{
		Map_Width = width;
		Map_Height = height;
		Map_Seed = seed;

		OnMapSettingsChanged.Execute();
		return true;
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Initializator component: map width or/and height equal zero") );
	}

	return false;
}

void UCPP_AComp_Initializator::Map_Get_Settings(uint8& width, uint8& height, int32& seed)
{
	width = Map_Width;
	height = Map_Height;
	seed = Map_Seed;
}

#pragma endregion Map


#pragma region Players // Players starting settings

bool UCPP_AComp_Initializator::Players_Set_Settings(const TMap<ResourceType, float>& playersResources)
{
	if(Players_Resources.Num()>0)
	{
		Players_Resources = playersResources;

		OnPlayersSettingsChanged.Execute();
		
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Initializator component: players starting resources not setted") );
	}
		
	return false;
}

void UCPP_AComp_Initializator::Players_Get_Settings(TMap<ResourceType, float>& playersResources)
{
	for(auto a:Players_Resources)
	{
		playersResources.Add(a);	
	};
}

bool UCPP_AComp_Initializator::Prices_Set_Settings(const TMap<ResourceType, float>& pricesRes)
{
	if(pricesRes.Num() == 0) return false;

	for(auto a: pricesRes)
	{
		Prices[static_cast<int32>(a.Key)] = a.Value;
	}

	OnPricesSettingsChanged.Execute();
	return true;
}

void UCPP_AComp_Initializator::Prices_Get_Settings(TMap<ResourceType, float>& pricesRes)
{
	for(int32 a = 0; a < Prices.Num(); a++)
	{
		pricesRes.Add(static_cast<ResourceType>(a), Prices[a]);
	}
}

#pragma endregion Players

