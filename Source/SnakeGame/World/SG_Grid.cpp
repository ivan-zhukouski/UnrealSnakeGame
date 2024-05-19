// Fill out your copyright notice in the Description page of Project Settings.


#include "World/SG_Grid.h"
#include "Core/Grid.h"
#include "DrawDebugHelpers.h"
#include "Components/LineBatchComponent.h"


DEFINE_LOG_CATEGORY_STATIC(LogWorldGrid,All,All);

ASG_Grid::ASG_Grid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASG_Grid::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASG_Grid::SetModel(const TSharedPtr<Snake::Grid>& Grid, int32 InCellSize)
{
    if(!Grid.IsValid())
    {
        UE_LOG(LogWorldGrid, Fatal, TEXT("Grid is null, game aborted!"));
    }
    GridDim = Grid.Get()->dimension();
    CellSize = InCellSize;
    WorldWidth = GridDim.width * CellSize;
    WorldHeight = GridDim.height * CellSize;
}

void ASG_Grid::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    DrawGrid();
}

void ASG_Grid::DrawGrid()
{
    if(!GetWorld() || !GetWorld()->LineBatcher) return;
    for(int32 i = 0; i< GridDim.height +1; ++i)
    {
        const FVector StarLocation = GetActorForwardVector() * CellSize * i + GetActorLocation();
        //DrawDebugLine(GetWorld(), StarLocation, StarLocation + GetActorRightVector() * WorldWidth, FColor::Red, false, -1.0f, 0,2.0f);
        GetWorld()->LineBatcher->DrawLine(StarLocation, StarLocation + GetActorRightVector() * WorldWidth, FLinearColor::Red,0,2.0f,0);
    }
    

    for(int32 i = 0; i< GridDim.width +1; ++i)
    {
        const FVector StarLocation = GetActorRightVector() * CellSize * i + GetActorLocation();
       // DrawDebugLine(GetWorld(), StarLocation, StarLocation + GetActorForwardVector() * WorldHeight, FColor::Red, false, -1.0f, 0,2.0f);
        GetWorld()->LineBatcher->DrawLine(StarLocation, StarLocation +GetActorForwardVector() * WorldHeight, FLinearColor::Red,0,2.0f,0);
    }
}
