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

	// ?????? ????????, ??????? ????? ?????? ?? ???? ?????
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Tooltip = "Resources to can extract"))
	TMap<ResourceType, float> ResourcesIn;

	UPROPERTY(BlueprintReadOnly, meta = (Tooltip = "Once for each tile type. Must have unique number", ExposeOnSpawn = "true"))
	int32 Tile_ID;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, BlueprintPure)
	bool GetResourcesIn(const ResourceType& resType);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool CompareResourcesIn(const TMap<ResourceType, float>& resTypes);

	UFUNCTION()
	bool Get_Tile_ID(int32& tileType);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Set_Tile_ID(const int32& newID);

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;*/
};
