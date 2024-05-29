// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainTypes.h"

namespace SnakeGame
{

class Grid
{
public:
	Grid(const Dimension& dimension);

    Dimension dimension() const {return c_dimension; }
    void printDebug();
    void freeCellsByType(CellType celltype);
    void update(const TPositionPtr* links, CellType celltype);
    bool hitTest(const Position& position, CellType celltype) const;
private:
    Dimension c_dimension;
    TArray<CellType> m_cells;
    void initWall();
    
    FORCEINLINE uint32 posToIndex(uint32 x, uint32 y) const;
    FORCEINLINE uint32 posToIndex(const Position& position) const;
};

}
