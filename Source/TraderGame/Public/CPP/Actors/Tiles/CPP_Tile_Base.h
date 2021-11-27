// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Tile_Base.generated.h"

enum class ResourceType : uint8;
UCLASS()
class TRADERGAME_API ACPP_Tile_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Tile_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// список ресурсов, которые можно добыть на этом тайле
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Tooltip = "Resources to can extract"))
	TArray<ResourceType> ResourcesIn;

	UPROPERTY(BlueprintReadOnly, meta = (Tooltip = "Once for each tile type. Must have unique number", ExposeOnSpawn = "true"))
	int32 ID_Type;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
	bool ResourceToCanExtract(const ResourceType& resType);

	UFUNCTION()
	bool GetTileTypeID(int32& tileType);
};
