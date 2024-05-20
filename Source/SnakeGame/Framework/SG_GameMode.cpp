// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/SG_GameMode.h"

#include "SG_Pawn.h"
#include "SnakeGame/Core/MainTypes.h"
#include "SnakeGame/Core/Grid.h"
#include "World/SG_Grid.h"
#include "World/SG_WorldTypes.h"
#include "Engine/ExponentialHeightFog.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Kismet/GameplayStatics.h"


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

    FindFog();

    //update colors of grid
    check(ColorsTable)
    const auto RowsCount = ColorsTable->GetRowNames().Num();
    check(RowsCount >= 1);
    ColorTableIndex = FMath::RandRange(0, RowsCount - 1);
    UpdateColors();
}

void ASG_GameMode::NextColor()
{
    if(ColorsTable)
    {
        ColorTableIndex = (ColorTableIndex + 1) % ColorsTable->GetRowNames().Num();
        UpdateColors();
    }
}

void ASG_GameMode::FindFog()
{
    TArray<AActor*> Fogs;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(),AExponentialHeightFog::StaticClass(),Fogs);
    if(Fogs.Num()>0)
    {
        Fog = Cast<AExponentialHeightFog>(Fogs[0]);
    }
}

void ASG_GameMode::UpdateColors()
{
    const auto RowName = ColorsTable->GetRowNames()[ColorTableIndex];
    const auto* ColorSet = ColorsTable->FindRow<FSnakeColors>(RowName,{});

    if(ColorSet)
    {
        //update grid
        GridVisual->UpdateColors(*ColorSet);

        //update fog color
        if(Fog && Fog->GetComponent())
        {
            Fog->GetComponent()->SkyAtmosphereAmbientContributionColorScale = ColorSet->SkyAtmosphereColor;
            Fog->MarkComponentsRenderStateDirty();
        }
    }
}
