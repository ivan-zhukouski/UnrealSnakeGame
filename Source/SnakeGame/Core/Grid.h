// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainTypes.h"

namespace Snake
{

class Grid
{
public:
	Grid(const Dimension& dimension);

    Dimension dimension() const {return c_dimension; }
private:
    Dimension c_dimension;
    TArray<CellType> m_cells;
    void initWall();
    void printDebug();
    FORCEINLINE int32 posToIndex(int32 x, int32 y) const;
};

}
