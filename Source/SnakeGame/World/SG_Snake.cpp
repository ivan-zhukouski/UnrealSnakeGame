// Fill out your copyright notice in the Description page of Project Settings.


#include "World/SG_Snake.h"

namespace
{
    FVector LinkPositionToVector(const SnakeGame::Position& Position, uint32 CellSize, const SnakeGame::Dimension& Dims)
    {
        return FVector((Dims.height - 1 - Position.y) * CellSize, Position.x * CellSize,0.0) + FVector(CellSize * 0.5);
    }
}

ASG_Snake::ASG_Snake()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASG_Snake::SetModel(const TSharedPtr<SnakeGame::Snake>& InSnake, uint32 InCellSize, const SnakeGame::Dimension& InDims)
{
    Snake = InSnake;
    CellSize = InCellSize;
    Dims = InDims;
}

void ASG_Snake::BeginPlay()
{
	Super::BeginPlay();
	if(!Snake.IsValid()) return;
    
    const auto& Links = Snake.Pin()->links();
    uint32 i = 0;
    for(const auto& Link: Links)
    {
        const bool IsHead = i ==0;
        const FTransform Transform = FTransform( LinkPositionToVector(Link,CellSize,Dims));
        auto* LinkActor = GetWorld()->SpawnActor<AActor>(IsHead ? SnakeHeadClass : SnakeLinkClass, Transform);
        SnakeLinks.Add(LinkActor);
        ++i;
    }
}

void ASG_Snake::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    if(!Snake.IsValid()) return;
    const auto& Links = Snake.Pin()->links();
    auto* LinkPtr = Links.GetHead();
    for(auto* LinkActor: SnakeLinks)
    {
        LinkActor->SetActorLocation(LinkPositionToVector(LinkPtr->GetValue(),CellSize,Dims));
        LinkPtr = LinkPtr->GetNextNode();
    }
}

