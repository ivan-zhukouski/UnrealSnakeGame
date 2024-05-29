// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grid.h"
#include "MainTypes.h"



namespace SnakeGame
{
class Grid;
class Snake;

class SNAKEGAME_API Game
{
public:
	Game(const Settings& settings);
    /**
     * Returns the pointer to the grid object
     * @return TSharedPtr<Grid> pointer to the grid object 
     */
    TSharedPtr<Grid> grid() const {return m_grid;}
    TSharedPtr<Snake> snake() const {return m_snake;}
    void update(float deltaSeconds, const Input& input);

private:
    Settings c_settings;
    TSharedPtr<Grid> m_grid;
    TSharedPtr<Snake> m_snake;

    float m_moveSeconds{0.0f};
    bool m_gameOver{false};


    void move(const Input& input);
    void updateGrid();
    bool updateTime(float deltaSeconds);
    bool died() const;
};
}
