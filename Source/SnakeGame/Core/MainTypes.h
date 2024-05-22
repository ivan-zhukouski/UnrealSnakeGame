// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

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
    Wall = 1,
    //Food,
    //Snake
};

struct Settings
{
    Dimension gridDims;
};
}
