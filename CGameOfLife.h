#pragma once

#include <vector>

#include "IGame.h"

class CGameOfLife : public IGame
{
public:

    enum class CellType : GameCellType
    {
        Empty,
        Alive,
    };

    CGameOfLife(GameCellPos s);
    virtual ~CGameOfLife();

    virtual GameCellType Cell(GameCellPos x, GameCellPos y) const override;
    virtual bool Update() override;
    virtual GameState State() override;
    virtual void Input(GameInput type, int32_t param_a, int32_t param_b) override;

protected:

    template<uint8_t Alive>
    inline uint8_t CountNeighbours(GameCellPos x, GameCellPos y);

    template<GameInput input>
    bool GameInputProcessor(int32_t param_a, int32_t param_b);

    template<GameInput input>
    void GameInputRegistrator();

private:

    typedef bool (CGameOfLife::*TGameInputProcessor)(int32_t param_a, int32_t param_b);

    GameState mState;

    GameCellPos mSize;
    std::vector<CellType> mCells;
    uint32_t mCurGenerationOffset;

    bool mNeedUpdate;

    TGameInputProcessor mGameInputProcessors[(size_t)GameInput::Total];
};
