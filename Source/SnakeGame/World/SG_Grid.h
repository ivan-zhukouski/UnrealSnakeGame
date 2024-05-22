// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SG_WorldTypes.h"
#include "Core/MainTypes.h"
#include "GameFramework/Actor.h"
#include "SG_Grid.generated.h"

namespace SnakeGame
{
class Grid;
}

UCLASS()
class SNAKEGAME_API ASG_Grid : public AActor
{
	GENERATED_BODY()
	
public:	
	ASG_Grid();
    virtual void Tick(float DeltaTime) override;
    void SetModel(const TSharedPtr<SnakeGame::Grid>& Grid, uint32 InCellSize);

    void UpdateColors(const FSnakeColors& Colors);

protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Origin;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* GridMesh;
    
	virtual void BeginPlay() override;
	
private:
    UPROPERTY()
    UMaterialInstanceDynamic* GridMaterial;
    SnakeGame::Dimension GridDim;
    uint32 CellSize;
    uint32 WorldWidth;
    uint32 WorldHeight;

    void DrawGrid();
};
