// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CPP_ENUMS.h"
#include "GameFramework/GameState.h"
#include "CPP_GS_Gameplay.generated.h"

/**
 * 
 */
UCLASS()
class TRADERGAME_API ACPP_GS_Gameplay : public AGameState
{
	GENERATED_BODY()

	public:

	ACPP_GS_Gameplay();
	
	UFUNCTION(BlueprintCallable, Category = "Gamestate resources")
	bool Resources_Get_Prices(TMap<ResourceType, float> &resourcesPrice);
	UFUNCTION(BlueprintCallable, Category = "Gamestate resources")
	bool Resources_Get_Once_Price(const ResourceType& resType, float& price);

	UFUNCTION(BlueprintCallable, Category = "Gamestate resources")
	bool Resources_Increase(const ResourceType& resType, const float& amount);
	UFUNCTION(BlueprintCallable, Category = "Gamestate resources")
	bool Resources_Decrease(const ResourceType& resType, const float& amount);

	protected:

	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const;

	TArray<float> ResourceStore; // текущее кол-во ресурсов
	TArray<float> ResourceStore_Old; // предыдущее сохраненное кол-во материалов
	
	UPROPERTY(Replicated, BlueprintReadOnly)
	TArray<float> Resources_Prices;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamestate resources|Trade|Prices")
	TArray<float> Resources_Price_Coefficients; // коэффициент влияния изменения кол-ва ресурсов на цену

	UFUNCTION(BlueprintNativeEvent)
	void Update_ResourcePrice(const ResourceType& resType);
	
#pragma region Resources_Initialization // initialization starting resources on server
	// starting resources set at "details"-panel
	UPROPERTY(EditAnywhere, Category = "Gamestate resources")
	TMap<ResourceType, float> Resources_Starting_Amount;

	UPROPERTY(EditAnywhere, Category = "Gamestate resources|Trade|Prices")
	TMap<ResourceType, float> Resources_Starting_Prices;	// стартовые цены на ресурсы
	
	// realization initialization at server
	UFUNCTION(BlueprintNativeEvent, Category = "Gamestate resources")
	void InitializationStartingResources();
#pragma endregion Resources_Initialization
};
