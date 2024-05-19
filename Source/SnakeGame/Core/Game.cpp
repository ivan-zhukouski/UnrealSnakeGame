// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGame/Core/Game.h"
#include "SnakeGame/Core/Grid.h"


using namespace Snake;

DEFINE_LOG_CATEGORY_STATIC(LogGame,All,All);

Game::Game(const Settings& settings) : c_settings(settings)
{
    m_grid = MakeShared<Grid>(settings.gridDims);
}
