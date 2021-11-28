// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP/ActorComponents/CPP_AComp_Resource.h"

#include "CPP/DATA/CPP_GS_Gameplay.h"
#include "CPP/ActorComponents/CPP_AComp_Initializator.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UCPP_AComp_Resource::UCPP_AComp_Resource()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}

// Called when the game starts
void UCPP_AComp_Resource::BeginPlay()
{
	Super::BeginPlay();

	Initialization();
	
}

void UCPP_AComp_Resource::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UCPP_AComp_Resource, ResourceStore);
}

void UCPP_AComp_Resource::Resources_Initialization_Implementation()
{
	Initialization();
}

void UCPP_AComp_Resource::Initialization_Implementation()
{
	UCPP_AComp_Initializator* initializator = GetWorld()->GetGameState()->FindComponentByClass<UCPP_AComp_Initializator>();
	if(initializator != nullptr)
	{
		ResourceStore.Init(0,static_cast<int32>(ResourceType::RT_Resources_Count));
		
		TMap<ResourceType, float> resources;
		initializator->Players_Get_Settings(resources);

		for(auto a:resources)
		{
			Server_Set_Resource(a.Key, a.Value);
		};
		
		return ;
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player's resource component: Initializator component not founded") );
	}
	
	return ;
}

// Set resource amount on server
void UCPP_AComp_Resource::Server_Set_Resource_Implementation(const ResourceType& resType, const float& amount)
{
	ResourceStore[static_cast<int32>(resType)] = amount;
}


void UCPP_AComp_Resource::Server_Resources_Buy_Implementation(const ResourceType& resType, const float& amount)
{
	ACPP_GS_Gameplay* gameState = Cast<ACPP_GS_Gameplay>(GetWorld()->GetGameState());
	
	if(gameState)
	{
		float price;
		gameState->Resources_Get_Once_Price(resType, price);

		float gold;
		Resources_Get_Amount(ResourceType::RT_Gold, gold);

		if(gold >= (amount * price))
		{
			Resources_Increase(resType, amount);
			gameState->Resources_Decrease(resType, amount);
			Resources_Decrease(ResourceType::RT_Gold, amount * price);
		}
		else if ( gold > 0.0f)
		{
			Resources_Increase(resType, gold/price);
			gameState->Resources_Decrease(resType, gold/price);
			Resources_Decrease(ResourceType::RT_Gold, gold);
		};
	}
}

void UCPP_AComp_Resource::Server_Resources_Sell_Implementation(const ResourceType& resType, const float& amount)
{
	ACPP_GS_Gameplay* gameState = Cast<ACPP_GS_Gameplay>(GetWorld()->GetGameState());

	if(gameState)
	{
		float price;
		gameState->Resources_Get_Once_Price(resType, price);

		float resAmount;
		Resources_Get_Amount(resType, resAmount);

		if (resAmount >= amount)
		{
			Resources_Decrease(resType, amount);
			gameState->Resources_Increase(resType, amount);
			Resources_Increase(ResourceType::RT_Gold, amount * price);
		}
		else if (resAmount > 0.0f)
		{
			Resources_Decrease(resType, resAmount);
			gameState->Resources_Increase(resType, resAmount);
			Resources_Increase(ResourceType::RT_Gold, resAmount * price);
		};
	}
}

// Called every frame
void UCPP_AComp_Resource::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


#pragma region Resources_Interface

bool UCPP_AComp_Resource::Resources_Increase_Implementation(const ResourceType& resType, const float& amount)
{
	Server_Set_Resource(resType, ResourceStore[static_cast<int32>(resType)] + abs(amount));
	return true;
}


bool UCPP_AComp_Resource::Resources_Increase_Array_Implementation(const TMap<ResourceType, float>& resources)
{
	for(auto a:resources)
	{
		if(!this->Resources_Increase(a.Key, a.Value)) return false;
	}
	return true;
}

bool UCPP_AComp_Resource::Resources_Decrease_Implementation(const ResourceType& resType, const float& amount)
{
	Server_Set_Resource(resType, ResourceStore[static_cast<int32>(resType)] - abs(amount));
	return true;
}

bool UCPP_AComp_Resource::Resources_Decrease_Array_Implementation(const TMap<ResourceType, float>& resources)
{
	for(auto a:resources)
	{
		if(!this->Resources_Decrease(a.Key, a.Value)) return false;
	}
	return false;
}

bool UCPP_AComp_Resource::Resources_Get_Amount_Implementation(const ResourceType& resType, float& amount)
{
	if(ResourceStore[static_cast<int32>(resType)])
	{
		amount = ResourceStore[static_cast<int32>(resType)];
	
		return true;
	}
	return false;
}

bool UCPP_AComp_Resource::Resources_Get_Enough_Implementation(const ResourceType& resType, const float& amount)
{
	return ResourceStore[static_cast<int32>(resType)] >= amount;
}

bool UCPP_AComp_Resource::Resources_Get_Enough_Array_Implementation(const TMap<ResourceType, float>& resources)
{
	for(auto a:resources)
	{
		if(!this->Resources_Get_Enough(a.Key, a.Value)) return false;
	}
	return true;
}

TMap<ResourceType, float> UCPP_AComp_Resource::Resources_Get_AllType_Amount_Implementation()
{
	TMap<ResourceType, float> result;
	for(int32 a = 0; a < ResourceStore.Num(); a++)
	{
		result.Add(static_cast<ResourceType>(a), ResourceStore[a]);
	}
	return result;
}

bool UCPP_AComp_Resource::Resources_Buy_Implementation(const ResourceType& resType, const float& amount)
{
	Server_Resources_Buy(resType, abs(amount));
	return true;
}

bool UCPP_AComp_Resource::Resources_Sell_Implementation(const ResourceType& resType, const float& amount)
{
	Server_Resources_Sell(resType, abs(amount));
	return true;
}

#pragma endregion Resources_Interface
