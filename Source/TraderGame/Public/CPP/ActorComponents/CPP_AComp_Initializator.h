// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP/DATA/CPP_ENUMS.h"

#include "CPP_AComp_Initializator.generated.h"


UCLASS( Blueprintable, BlueprintType, ClassGroup=(Initialization), meta=(BlueprintSpawnableComponent))
class TRADERGAME_API UCPP_AComp_Initializator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCPP_AComp_Initializator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	UPROPERTY()
	uint8 Map_Width = 25;
	UPROPERTY()
	uint8 Map_Height = 25;
	UPROPERTY()
	int32 Map_Seed = 1;


	UPROPERTY()
	TMap<ResourceType, float> Players_Resources =
		{
			{ResourceType::RT_Food, 10.0f},
			{ResourceType::RT_Iron, 10.0f},
			{ResourceType::RT_Coil, 10.0f},
			{ResourceType::RT_Gold, 0.0f}
		}; // starting default minimum resources set
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma region Map // Map starting settings
	UFUNCTION(BlueprintCallable, Category = "Map")
	bool Map_Set_Settings(const uint8& width, const uint8& height, const int32& seed);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Map")
	void Map_Get_Settings(uint8& width, uint8& height, int32& seed);
#pragma endregion Map

#pragma region Players // Players starting settings
	UFUNCTION(BlueprintCallable, Category = "Players settings")
	bool Players_Set_Settings(const TMap<ResourceType, float>& playersResources);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Players settings")
	void Players_Get_Settings(TMap<ResourceType, float>& playersResources);
#pragma endregion Players
};
