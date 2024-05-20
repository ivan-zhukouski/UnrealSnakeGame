// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Game.h"
#include "Core/MainTypes.h"
#include "GameFramework/Pawn.h"
#include "SG_Pawn.generated.h"

class UCameraComponent;

UCLASS()
class SNAKEGAME_API ASG_Pawn : public APawn
{
	GENERATED_BODY()

public:
	ASG_Pawn();
    
    void UpdateLocation(const Snake::Dimension& Dim, int32 CellSize, const FTransform& GridOrigin);
    
protected:
    
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Origin;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent* MainCamera;
private:
    Snake::Dimension Dim;
    int32 CellSize;
    FTransform GridOrigin;
    FDelegateHandle ResizeHandle;
    void OnViewportResized(FViewport* Viewport, uint32 Val);
};
