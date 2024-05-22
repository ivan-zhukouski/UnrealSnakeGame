// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Grid.h"
#include "Core/MainTypes.h"

using namespace SnakeGame;

DEFINE_LOG_CATEGORY_STATIC(LogGrid,All,All);

Grid::Grid(const Dimension& dimension) //
    : c_dimension(Dimension{dimension.width+2, dimension.height+2})
{
    m_cells.Init(CellType::Empty, c_dimension.height * c_dimension.width);
    initWall();
    printDebug();
}

void Grid::initWall()
{
    for(uint32 y = 0; y < c_dimension.height; ++y)
    {
        for( uint32 x = 0; x< c_dimension.width; ++x)
        {
            if(x == 0 || x == c_dimension.width -1 || y == 0 || y == c_dimension.height -1)
            {
                m_cells[posToIndex(x,y)] = CellType::Wall;
            }
        }
    }
}

void Grid::printDebug()
{
#if !UE_BUILD_SHIPPING
    for(uint32 y = 0; y < c_dimension.height; ++y)
    {
        FString line;
        for( uint32 x = 0; x< c_dimension.width; ++x)
        {
            TCHAR symbol = ' ';
            switch ( m_cells[posToIndex(x,y)])
            {
                case CellType::Empty: symbol = '0'; break;
                case CellType::Wall: symbol = '*'; break;
            }
            line.AppendChar(symbol).AppendChar(' ');
        }
        UE_LOG(LogGrid,Display,TEXT("%s"), * line);
    }
#endif
    
}

uint32 Grid::posToIndex(uint32 x, uint32 y) const
{
    return x + y * c_dimension.width;
}
