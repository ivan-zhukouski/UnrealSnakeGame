// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SnakeGame/Core/Game.h"
#include "GameFramework/GameModeBase.h"
#include "InputActionValue.h"
#include "SG_GameMode.generated.h"


class ASG_Grid;
class UInputAction;
class UInputMappingContext;
class AExponentialHeightFog;
class ASG_Snake;

UCLASS()
class SNAKEGAME_API ASG_GameMode : public AGameModeBase
{
	GENERATED_BODY()
    
public:
    ASG_GameMode();
    virtual void StartPlay() override;
    virtual void Tick(float DeltaSeconds) override;

protected:
    UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "10", ClampMax = "100"), Category = "Settings")
    FUintPoint GridDims {10,10};

    UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "10", ClampMax = "100"), Category = "Settings")
    uint32 CellSize{10};

    UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "4", ClampMax = "10"), Category = "Settings")
    uint32 SnakeDefaultSize{5};

    UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0.01", ClampMax = "10"), Category = "Settings")
    float SnakeSpeed{1.0};

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ASG_Grid> GridVisualClass;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ASG_Snake> SnakeVisualClass;

    UPROPERTY(EditDefaultsOnly, Category = "Design")
    UDataTable* ColorsTable;

    UPROPERTY(EditDefaultsOnly , Category = "SnakeInput")
    TObjectPtr<UInputAction> MoveForwardInputAction;
    
    UPROPERTY(EditDefaultsOnly , Category = "SnakeInput")
    TObjectPtr<UInputAction> MoveRightInputAction;

    UPROPERTY(EditDefaultsOnly , Category = "SnakeInput")
    TObjectPtr<UInputMappingContext> InputMapping; 

    
private:
    UPROPERTY()
    ASG_Grid* GridVisual;

    UPROPERTY()
    ASG_Snake* SnakeVisual;
    
    UPROPERTY()
    AExponentialHeightFog* Fog;

    UFUNCTION(Exec, Category = "Console Command")
    void NextColor();
    
    TUniquePtr<SnakeGame::Game> CoreGame;
    uint32 ColorTableIndex {0};
    SnakeGame::Input SnakeInput{1,0};
    
    void FindFog();

   
    /**
     *Updates Grid and ExponentialFog colors
     * according to the ColorTable property
     */
    void UpdateColors();

    void SetupInput();
    void OnMoveForward(const FInputActionValue& Value);
    void OnMoveRight(const FInputActionValue& Value);
};

