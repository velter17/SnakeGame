#pragma once

#include <cstdint>

typedef uint8_t GameCellType;
typedef uint8_t GameCellPos;

enum class GameState
{
    Running,
    Stop,
    Over,
    Total,
};

enum class GameInput
{
    Run,
    Stop,
    LButtonDown,
    RButtonDown,
    UButtonDown,
    DButtonDown,
    Total,
};
