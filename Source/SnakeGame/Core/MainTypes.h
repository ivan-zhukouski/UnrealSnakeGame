// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/List.h"

namespace SnakeGame
{
struct Dimension
{
    uint32 width;
    uint32 height;
};

enum class CellType
{
    Empty = 0,
    Wall,
    Snake,
    //Food
};

struct Position
{
    Position(uint32 inX, uint32 inY) : x(inX),y(inY) {};
    uint32 x;
    uint32 y;

    FORCEINLINE Position& operator+=(const Position& rhs)
    {
        x +=rhs.x;
        y +=rhs.y;
        return *this;
    }
};

struct Input
{
    
    int8 x;
    int8 y;

    FORCEINLINE bool opposite(const Input& rhs) const //
    {
        return ( x == -rhs.x && x != 0) || (y == -rhs.y && y != 0);
    }
};

struct Settings
{
    Dimension gridDims{40, 10};

    struct Snake
    {
        uint32 defaultSize{4};
        Position startPosition{0, 0};
        
    } snake;
    float snakeSpeed{1.0f};
    
};
using TSnakeList = TDoubleLinkedList<Position>;
using TPositionPtr  = TSnakeList::TDoubleLinkedListNode;
}
