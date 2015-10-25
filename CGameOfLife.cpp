#include <cstdlib>
#include <ctime>

#include "CGameOfLife.h"

CGameOfLife::CGameOfLife(GameCellPos s)
    : mState(GameState::Stop)
    , mSize(s)
    , mCells(mSize * mSize * 2)
    , mCurGenerationOffset(0)
    , mNeedUpdate(true)
{
    GameInputRegistrator<(GameInput)0>();
}

CGameOfLife::~CGameOfLife()
{
}

template<GameInput input>
void CGameOfLife::GameInputRegistrator()
{
    mGameInputProcessors[(size_t)input] = &CGameOfLife::GameInputProcessor<input>;
    GameInputRegistrator<(GameInput)((size_t)input + 1)>();
}

template<>
void CGameOfLife::GameInputRegistrator<GameInput::Total>()
{
}

GameCellType CGameOfLife::Cell(GameCellPos x, GameCellPos y) const
{
    if (x > mSize || y > mSize)
    {
        throw std::exception();
    }
    return static_cast<GameCellType>(mCells[mCurGenerationOffset + y * mSize + x]);
}

bool CGameOfLife::Update()
{
    bool ret = mNeedUpdate;
    mNeedUpdate = false;

    if (mState != GameState::Running)
    {
        return ret;
    }

    const uint32_t next_generation_offset = mSize * mSize - mCurGenerationOffset;

    for (GameCellPos y = 0; y < mSize; y++)
    {
        for (GameCellPos x = 0; x < mSize; x++)
        {
            if (mCells[mCurGenerationOffset + y * mSize + x] == CellType::Alive)
            {
                uint8_t c = CountNeighbours<1>(x, y);
                if (c == 2 || c == 3)
                {
                    mCells[next_generation_offset + y * mSize + x] = CellType::Alive;
                }
                else
                {
                    mCells[next_generation_offset + y * mSize + x] = CellType::Empty;
                    ret = true;
                }
            }
            else
            {
                uint8_t c = CountNeighbours<0>(x, y);
                if (c == 3)
                {
                    mCells[next_generation_offset + y * mSize + x] = CellType::Alive;
                    ret = true;
                }
                else
                {
                    mCells[next_generation_offset + y * mSize + x] = CellType::Empty;
                }
            }
        }
    }

    mCurGenerationOffset = next_generation_offset;

    return ret;
}

template<uint8_t Alive>
uint8_t CGameOfLife::CountNeighbours(GameCellPos x, GameCellPos y)
{
    const GameCellPos xstart = x == 0 ? x : x - 1;
    const GameCellPos xend = x == mSize - 1 ? x : x + 1;
    const GameCellPos ystart = y == 0 ? y : y - 1;
    const GameCellPos yend = y == mSize - 1 ? y : y + 1;

    uint8_t res = 0;

    for (GameCellPos iy = ystart; iy <= yend; iy++)
    {
        for (GameCellPos ix = xstart; ix <= xend; ix++)
        {
            res += mCells[mCurGenerationOffset + iy * mSize + ix] == CellType::Alive;
        }
    }

    return res - Alive;
}

GameState CGameOfLife::State()
{
    return mState;
}

template<>
bool CGameOfLife::GameInputProcessor<GameInput::Run>(int32_t , int32_t )
{
    mState = GameState::Running;
    return false;
}

template<>
bool CGameOfLife::GameInputProcessor<GameInput::Stop>(int32_t , int32_t )
{
    mState = GameState::Stop;
    return false;
}

template<>
bool CGameOfLife::GameInputProcessor<GameInput::LButtonDown>(int32_t param_a, int32_t param_b)
{
    mCells[param_b * mSize + param_a] = CellType::Alive;
    return true;
}

template<>
bool CGameOfLife::GameInputProcessor<GameInput::RButtonDown>(int32_t param_a, int32_t param_b)
{
    mCells[param_b * mSize +  param_a] = CellType::Empty;
    return true;
}

template<>
bool CGameOfLife::GameInputProcessor<GameInput::UButtonDown>(int32_t param_a, int32_t param_b)
{
    mCells[param_b * mSize +  param_a] = CellType::Empty;
    return true;
}

template<>
bool CGameOfLife::GameInputProcessor<GameInput::DButtonDown>(int32_t param_a, int32_t param_b)
{
    mCells[param_b * mSize +  param_a] = CellType::Empty;
    return true;
}

void CGameOfLife::Input(GameInput type, int32_t param_a, int32_t param_b)
{
    mNeedUpdate = (this->*mGameInputProcessors[(size_t)type])(param_a, param_b);
}
