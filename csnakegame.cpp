#include "CSnakeGame.h"

#include <QDebug>

CSnakeGame::CSnakeGame(GameCellPos s)
    : mSize(s)
    , mCellTypes(mSize * mSize, CellType::Empty)
    , mPosInEmptyList(mSize * mSize)
    , mState(GameState::Stop)
    , mDirX(1)
    , mDirY(0)
{
    GameInputRegistrator<(GameInput)0>();

    for(qint32 i = mSize / 2 - 2; i < mSize/2+2; i++)
    {
        TPoint pt(i, mSize / 2);
        mCellTypes[getPointPos(pt)] = CellType::Fill;
        mSnake.push(pt);
    }
    mHead = mSnake.back();

    for(qint32 i = 0; i < mSize; i++)
    {
        for(qint32 j = 0; j < mSize; j++)
        {
            if(mCellTypes[getPointPos(TPoint(i, j))] == CellType::Empty)
            {
                mPosInEmptyList[getPointPos(TPoint(i, j))] = (qint32)mEmptyCells.size();
                mEmptyCells.push_back(std::make_pair(i, j));
            }
        }
    }

    mFood = getRandomEmptyCell();
    fillCell(mFood);
}

CSnakeGame::~CSnakeGame()
{

}

GameCellType CSnakeGame::Cell(GameCellPos x, GameCellPos y) const
{
    return static_cast<GameCellType>(mCellTypes[getPointPos(TPoint(x, y))]);
}

bool CSnakeGame::Update()
{
    if (mState != GameState::Running)
    {
        return false;
    }

    mHead.first += mDirX + mSize;
    mHead.second += mDirY + mSize;
    mHead.first %= mSize;
    mHead.second %= mSize;
    mSnake.push(mHead);

    bool isOnFood = mHead == mFood;

    if(!isOnFood)
    {
        releaseCell(mSnake.front());
        mSnake.pop();
    }

    if(mCellTypes[getPointPos(mHead)] == CellType::Fill && !isOnFood)
    {
        mState = GameState::Stop;
        return false;
    }
    else
    {
        if(isOnFood)
        {
            mFood = getRandomEmptyCell();
            fillCell(mFood);
        }
        else
        {
            fillCell(mHead);
        }
    }

    return true;
}

GameState CSnakeGame::State()
{
    return mState;
}

void CSnakeGame::Input(GameInput type, int32_t param_a, int32_t param_b)
{
    (this->*mGameInputProcessors[(size_t)type])(param_a, param_b);
}

CSnakeGame::TPoint CSnakeGame::getRandomEmptyCell()
{
    if(mEmptyCells.empty())
        std::exception();

    qint32 rand_idx = rand() % ((qint32)mEmptyCells.size());
    return mEmptyCells[rand_idx];
}

void CSnakeGame::releaseCell(const TPoint &p)
{
    mPosInEmptyList[getPointPos(p)] = (qint32)mEmptyCells.size();
    mEmptyCells.push_back(p);
    mCellTypes[getPointPos(p)] = CellType::Empty;
}

void CSnakeGame::fillCell(const TPoint &p)
{
    qint32 pos = mPosInEmptyList[getPointPos(p)];
    mPosInEmptyList[getPointPos(mEmptyCells.back())] = pos;
    swap(mEmptyCells[pos], mEmptyCells.back());
    mEmptyCells.pop_back();
    mCellTypes[getPointPos(p)] = CellType::Fill;
}

qint32 CSnakeGame::getPointPos(const CSnakeGame::TPoint &p) const
{
    return p.first * mSize + p.second;
}


template <>
bool CSnakeGame::GameInputProcessor<GameInput::Run>(int32_t param_a, int32_t param_b)
{
    mState = GameState::Running;
    return false;
}

template <>
bool CSnakeGame::GameInputProcessor<GameInput::Stop>(int32_t param_a, int32_t param_b)
{
    mState = GameState::Stop;
    return false;
}

template <>
bool CSnakeGame::GameInputProcessor<GameInput::UButtonDown>(int32_t param_a, int32_t param_b)
{
    if(mDirY == 1)
        return false;
    mDirX = 0;
    mDirY = -1;
    return true;
}

template <>
bool CSnakeGame::GameInputProcessor<GameInput::DButtonDown>(int32_t param_a, int32_t param_b)
{
    if(mDirY == -1)
        return false;
    mDirX = 0;
    mDirY = 1;
    return true;
}

template <>
bool CSnakeGame::GameInputProcessor<GameInput::LButtonDown>(int32_t param_a, int32_t param_b)
{
    if(mDirX == 1)
       return false;
    mDirX = -1;
    mDirY = 0;
    return true;
}

template <>
bool CSnakeGame::GameInputProcessor<GameInput::RButtonDown>(int32_t param_a, int32_t param_b)
{
    if(mDirX == -1)
       return false;
    mDirX = 1;
    mDirY = 0;
    return true;
}

template <GameInput input>
void CSnakeGame::GameInputRegistrator()
{
    mGameInputProcessors[(size_t)input] = &CSnakeGame::GameInputProcessor<input>;
    GameInputRegistrator<(GameInput)((size_t)input + 1)>();
}

template <>
void CSnakeGame::GameInputRegistrator<GameInput::Total>()
{

}
