// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "CPP/DATA/Structs/SGameMap.h"
#include "GameFramework/Actor.h"
#include "CPP_MapGenerator.generated.h"

class ACPP_Tile_Base;
class UDA_TilesMeshKeys;

UCLASS()
class TRADERGAME_API ACPP_MapGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_MapGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	FGameMap GameMap;

	TArray<ACPP_Tile_Base*> MapElements;

	int32 MapSeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDA_TilesMeshKeys* Current_Tileset;

	UFUNCTION()
	void Initialization();
	
	UFUNCTION()
	void CreateBinds();

	UFUNCTION(BlueprintCallable)
	void GenerateMap();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
