// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP/Interfaces/CPP_BPI_Resources.h"

#include "CPP_AComp_Resource.generated.h"

UCLASS( Blueprintable, BlueprintType, ClassGroup=(Resource), meta=(BlueprintSpawnableComponent))
//UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRADERGAME_API UCPP_AComp_Resource : public UActorComponent, public ICPP_BPI_Resources
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCPP_AComp_Resource();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const;
	UPROPERTY(Replicated)
	TArray<float> ResourceStore;

//private:
#pragma region StartingResources

	UFUNCTION(Server, Reliable)
	void Initialization();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources|General|Set")
	void Resources_Initialization();
	virtual void Resources_Initialization_Implementation() override;
	
#pragma endregion StartingResources

#pragma region SERVER_FUNCTIONS
	UFUNCTION(Server, Reliable)
	void Server_Set_Resource(const ResourceType& resType, const float& amount);

	UFUNCTION(Server, Reliable)
	void Server_Resources_Buy(const ResourceType& resType, const float& amount);
	UFUNCTION(Server, Reliable)
	void Server_Resources_Sell(const ResourceType& resType, const float& amount);
#pragma endregion SERVER_FUNCTIONS
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma region Resources_Interface

#pragma region SETTERS
	// increase one type resource
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources|General|Set")
	bool Resources_Increase(const ResourceType& resType, const float& amount);
	virtual bool Resources_Increase_Implementation(const ResourceType& resType, const float& amount) override;
	// increase few types of resources
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources|General|Set")
	bool Resources_Increase_Array(const TMap<ResourceType, float>& resources);
	virtual bool Resources_Increase_Array_Implementation(const TMap<ResourceType, float>& resources) override;

	// decrease one type resource
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources|General|Set")
	bool Resources_Decrease(const ResourceType& ResType, const float& amount);
	virtual bool Resources_Decrease_Implementation(const ResourceType& ResType, const float& amount) override;
	// decrease few types of resources
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources|General|Set")
	bool Resources_Decrease_Array(const TMap<ResourceType, float>& resources);
	virtual bool Resources_Decrease_Array_Implementation(const TMap<ResourceType, float>& resources) override;
#pragma endregion SETTERS

#pragma region GETTERS
	// get amount of one type resource
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources|General|Get")
	bool Resources_Get_Amount(const ResourceType& resType, float& amount);
	virtual bool Resources_Get_Amount_Implementation(const ResourceType& resType, float& amount) override;
	// check amount of one type resource
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources|General|Get")
	bool Resources_Get_Enough(const ResourceType& resType, const float& amount);
	virtual bool Resources_Get_Enough_Implementation(const ResourceType& resType, const float& amount) override;
	// get amount of few types resources
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources|General|Get")
	bool Resources_Get_Enough_Array(const TMap<ResourceType, float>& resources);
	virtual bool Resources_Get_Enough_Array_Implementation(const TMap<ResourceType, float>& resources) override;
	// get amount of all types resources
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources|General|Get")
	TMap<ResourceType, float> Resources_Get_AllType_Amount();
	virtual TMap<ResourceType, float> Resources_Get_AllType_Amount_Implementation() override;
	
#pragma endregion GETTERS

#pragma region TRADE

	// buy resource
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources|Trade")
	bool Resources_Buy(const ResourceType& resType, const float& amount);
	virtual bool Resources_Buy_Implementation(const ResourceType& resType, const float& amount) override;
	//sell resource
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources|Trade")
	bool Resources_Sell(const ResourceType& resType, const float& amount);
	virtual bool Resources_Sell_Implementation(const ResourceType& resType, const float& amount) override;
	
#pragma endregion TRADE
	
#pragma endregion Resources_Interface

		
};
