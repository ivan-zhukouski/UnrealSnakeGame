// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SnakeGame/Core/Game.h"
#include "GameFramework/GameModeBase.h"
#include "SG_GameMode.generated.h"


class ASG_Grid;
class AExponentialHeightFog;

UCLASS()
class SNAKEGAME_API ASG_GameMode : public AGameModeBase
{
	GENERATED_BODY()
    
public:
    virtual void StartPlay() override;

protected:
    UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "10", ClampMax = "100"))
    FUintPoint GridDims {10,10};

    UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "10", ClampMax = "100"))
    uint32 CellSize{10};

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ASG_Grid> GridVisualClass;

    UPROPERTY(EditDefaultsOnly, Category = "Design")
    UDataTable* ColorsTable;
    
private:
    UPROPERTY()
    ASG_Grid* GridVisual;
    
    UPROPERTY()
    AExponentialHeightFog* Fog;

    UFUNCTION(Exec, Category = "Console Command")
    void NextColor();
    
    TUniquePtr<Snake::Game> CoreGame;
    uint32 ColorTableIndex {0};
    
    void FindFog();
    void UpdateColors();
};

