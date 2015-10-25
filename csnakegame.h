#ifndef CSNAKEGAME_H
#define CSNAKEGAME_H

#include "IGame.h"
#include <vector>
#include <queue>
#include <QtGlobal>

class CSnakeGame : public IGame
{
public:

    enum class CellType : GameCellType
    {
        Empty,
        Fill,
    };

    CSnakeGame(GameCellPos s);
    virtual ~CSnakeGame();

    virtual GameCellType Cell(GameCellPos x, GameCellPos y) const override;
    virtual bool Update() override;
    virtual GameState State() override;
    virtual void Input(GameInput type, int32_t param_a, int32_t param_b) override;

protected:
    typedef std::pair <qint32, qint32> TPoint;

    template <GameInput input>
    bool GameInputProcessor(int32_t param_a, int32_t param_b);

    template <GameInput input>
    void GameInputRegistrator();

    TPoint getRandomEmptyCell();
    void releaseCell(const TPoint &p);
    void fillCell(const TPoint &p);
    inline qint32 getPointPos(const TPoint &p) const;



private:
    typedef bool (CSnakeGame::*TGameInputProcessor)(int32_t param_a, int32_t param_b);

    GameState mState;

    GameCellPos mSize;
    std::vector <TPoint> mEmptyCells;
    std::vector <CellType> mCellTypes;
    std::vector <qint32> mPosInEmptyList;
    qint32 mDirX;
    qint32 mDirY;
    std::queue <TPoint> mSnake;
    TPoint mFood;
    TPoint mHead;

    TGameInputProcessor mGameInputProcessors[(size_t)GameInput::Total];
};

#endif // CSNAKEGAME_H
