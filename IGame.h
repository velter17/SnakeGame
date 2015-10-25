#pragma once

#include "GameTypes.h"

class IGame
{
public:
    virtual ~IGame() {}

    virtual bool Update() = 0;
    virtual GameState State() = 0;
    virtual void Input(GameInput type, int32_t param_a, int32_t param_b) = 0;
    virtual GameCellType Cell(GameCellPos x, GameCellPos y) const = 0;
};
