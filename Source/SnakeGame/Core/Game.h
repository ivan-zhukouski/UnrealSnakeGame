// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grid.h"
#include "MainTypes.h"

class Grid;

namespace SnakeGame
{

class SNAKEGAME_API Game
{
public:
	Game(const Settings& settings);
    /**
     * Returns the pointer to the grid object
     * @return TSharedPtr<Grid> pointer to the grid object 
     */
    TSharedPtr<Grid> grid() const {return m_grid;}
private:
    Settings c_settings;
    TSharedPtr<Grid> m_grid;
};
}
