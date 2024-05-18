// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/SG_GameMode.h"

#include "SG_Pawn.h"
#include "SnakeGame/Core/MainTypes.h"
#include "SnakeGame/Core/Grid.h"
#include "World/SG_Grid.h"

void ASG_GameMode::StartPlay()
{
    Super::StartPlay();
    //init core game
    const Snake::Settings GameSettings {GridDims.X, GridDims.Y};
    CoreGame = MakeUnique<Snake::Game>(GameSettings);
    check(CoreGame.IsValid());

    //init world grid
    FTransform GridOrigin = FTransform::Identity;
    check(GetWorld());
    GridVisual = GetWorld()->SpawnActorDeferred<ASG_Grid>(GridVisualClass, GridOrigin);
    check(GridVisual);
    GridVisual->SetModel(CoreGame->grid(),CellSize);
    GridVisual->FinishSpawning(GridOrigin);
    //set pawn location

    auto* PlayerController = GetWorld()->GetFirstPlayerController();
    check(PlayerController)

    auto* Pawn = Cast<ASG_Pawn>(PlayerController->GetPawn());
    check(Pawn);
    check(CoreGame->grid().IsValid());
    Pawn->UpdateLocation(CoreGame->grid()->dimension(),CellSize, GridOrigin);
}
