// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP/DATA/CPP_GS_Gameplay.h"

#include "CPP/ActorComponents/CPP_AComp_Initializator.h"
#include "Net/UnrealNetwork.h"

ACPP_GS_Gameplay::ACPP_GS_Gameplay()
{
	
}

void ACPP_GS_Gameplay::BeginPlay()
{
	Super::BeginPlay();
	
	CreateBinds();
	InitializationStartingResources();
}

void ACPP_GS_Gameplay::Update_ResourcePrice_Implementation(const ResourceType& resType)
{
	int32 number = static_cast<int32>(resType);
	float coefficient = (ResourceStore_Old[number] > ResourceStore[number] ? 1.0f : 0.5f);

	float price = Resources_Prices[number];
	price += (Resources_Price_Coefficients[number] * ((ResourceStore_Old[number] - ResourceStore[number]) * coefficient));
	if(price < 1.0f) price = 1.0f;
	if(price > 100000.0f) price = 100000.0f;
	
	Resources_Prices[number] = price;
	ResourceStore_Old[number] = ResourceStore[number];
}

void ACPP_GS_Gameplay::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ACPP_GS_Gameplay, Resources_Prices);
}

void ACPP_GS_Gameplay::InitializationStartingResources_Implementation()
{
	ResourceStore.Init(0,static_cast<int32>(ResourceType::RT_Resources_Count));
	
	for(auto a:Resources_Starting_Amount)
	{
		ResourceStore[static_cast<int32>(a.Key)] = a.Value;
	};
	ResourceStore_Old = ResourceStore;

	Resources_Prices.Init(1.0f,static_cast<int32>(ResourceType::RT_Resources_Count));

	UCPP_AComp_Initializator* initializator = this->FindComponentByClass<UCPP_AComp_Initializator>();
	if(initializator)
	{
		TMap<ResourceType, float> pricesRes;
		initializator->Prices_Get_Settings(pricesRes);

		for(auto a: pricesRes)
		{
			Resources_Prices[static_cast<int32>(a.Key)] = a.Value;
		}
	}
}

bool ACPP_GS_Gameplay::Resources_Get_Prices(TMap<ResourceType, float>& resourcesPrice)
{
	for(int a = 0; a < Resources_Prices.Num(); a++)
	{
		resourcesPrice.Add(static_cast<ResourceType>(a), Resources_Prices[a]);
	}
	return true;
}

bool ACPP_GS_Gameplay::Resources_Get_Once_Price(const ResourceType& resType, float& price)
{
	int num = static_cast<int>(resType);
	if(Resources_Prices.IsValidIndex(num))
	{
		price = Resources_Prices[num];
		return true;
	};
	return false;
}

bool ACPP_GS_Gameplay::Resources_Increase(const ResourceType& resType, const float& amount)
{
	ResourceStore[static_cast<int32>(resType)] += amount;
	Update_ResourcePrice(resType);
	return true;
}

bool ACPP_GS_Gameplay::Resources_Decrease(const ResourceType& resType, const float& amount)
{
	ResourceStore[static_cast<int32>(resType)] -= amount;
	Update_ResourcePrice(resType);
	return true;
}


void ACPP_GS_Gameplay::CreateBinds()
{
	UCPP_AComp_Initializator* initializator = this->FindComponentByClass<UCPP_AComp_Initializator>();
	if(initializator)
	{
		initializator->OnPricesSettingsChanged.BindUFunction(this, "InitializationStartingResources");
	}
}