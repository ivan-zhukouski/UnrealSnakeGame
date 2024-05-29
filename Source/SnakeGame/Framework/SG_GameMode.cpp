// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/SG_GameMode.h"

#include "SG_Pawn.h"
#include "SnakeGame/Core/MainTypes.h"
#include "SnakeGame/Core/Grid.h"
#include "World/SG_Grid.h"
#include "World/SG_Snake.h"
#include "World/SG_WorldTypes.h"
#include "Engine/ExponentialHeightFog.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Kismet/GameplayStatics.h"
#include "World/SG_Snake.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


ASG_GameMode::ASG_GameMode()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ASG_GameMode::StartPlay()
{
    Super::StartPlay();
    //init core game
    SnakeGame::Settings GameSettings;
    GameSettings.gridDims = SnakeGame::Dimension{GridDims.X,GridDims.Y};
    GameSettings.snakeSpeed = SnakeSpeed;
    GameSettings.snake.defaultSize = SnakeDefaultSize;
    GameSettings.snake.startPosition = SnakeGame::Position{GridDims.X / 2, GridDims.Y / 2};
    //{GridDims.X, GridDims.Y};
    CoreGame = MakeUnique<SnakeGame::Game>(GameSettings);
    check(CoreGame.IsValid());

    //init world grid
    FTransform GridOrigin = FTransform::Identity;
    check(GetWorld());
    GridVisual = GetWorld()->SpawnActorDeferred<ASG_Grid>(GridVisualClass, GridOrigin);
    check(GridVisual);
    GridVisual->SetModel(CoreGame->grid(),CellSize);
    GridVisual->FinishSpawning(GridOrigin);

    //init world snake
    SnakeVisual = GetWorld()->SpawnActorDeferred<ASG_Snake>(SnakeVisualClass, GridOrigin);
    SnakeVisual->SetModel(CoreGame->snake(),CellSize,CoreGame->grid()->dimension());
    SnakeVisual->FinishSpawning(GridOrigin);
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
    //
    SetupInput();
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

void ASG_GameMode::SetupInput()
{
    if(!GetWorld()) return;
    if(auto* PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController()))
    {
        if(auto* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            InputSystem->AddMappingContext(InputMapping,0);
        }
        auto* Input = Cast<UEnhancedInputComponent>(PC->InputComponent);
        check(Input);
        Input->BindAction(MoveForwardInputAction, ETriggerEvent::Triggered, this, &ThisClass::OnMoveForward);
        Input->BindAction(MoveRightInputAction, ETriggerEvent::Triggered, this, &ThisClass::OnMoveRight);
    }
}

void ASG_GameMode::OnMoveForward(const FInputActionValue& Value)
{
    const float InputValue = Value.Get<float>();
    SnakeInput = SnakeGame::Input{0,static_cast<int8>(InputValue)};
}

void ASG_GameMode::OnMoveRight(const FInputActionValue& Value)
{
    const float InputValue = Value.Get<float>();
    SnakeInput = SnakeGame::Input{static_cast<int8>(InputValue),0};
}

void ASG_GameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if( CoreGame.IsValid())
    {
        CoreGame->update(DeltaSeconds,SnakeInput);
        
    }
}
