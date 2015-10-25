#include <qpainter.h>

#include "CGameComponent.h"
#include "CGridRenderer.h"
#include "CCubeRenderer.h"
#include "CCircleRenderer.h"
//#include "CGameOfLife.h"
#include "CSnakeGame.h"

#define CREATE_ELEMENT_RENDERER(type) do { if (RenderType::type == mRenderType) { mDrawList.append(new C##type##Renderer(mGame, mCellSizeHorizontal, mCellSizeVertical, mSize)); } } while (false)

CGameComponent::CGameComponent(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , mSize(DefaultGameFieldSize)
    //, mGame(new CGameOfLife(mSize))
    , mGame(new CSnakeGame(mSize))
    , mRenderType(RenderType::Cube)
    , mGridRenderer(nullptr)
{
    UpdateSizeDerivatives();
}

CGameComponent::~CGameComponent()
{
    qDeleteAll(mDrawList);
    mGridRenderer = nullptr;
}

void CGameComponent::UpdateSizeDerivatives()
{
    mCellSizeHorizontal = (width() - 1) / mSize;
    mCellSizeVertical = (height() - 1) / mSize;

    bool show_grid = mGridRenderer ? mGridRenderer->Visible() : true;

    qDeleteAll(mDrawList);
    mDrawList.clear();

    mGridRenderer = new CGridRenderer(show_grid, mCellSizeHorizontal, mCellSizeVertical, mSize);

    mDrawList.append(mGridRenderer);
    CREATE_ELEMENT_RENDERER(Cube);
    CREATE_ELEMENT_RENDERER(Circle);

    update();
}

void CGameComponent::geometryChanged(const QRectF &, const QRectF &)
{
    UpdateSizeDerivatives();
}

void CGameComponent::Input(GameComponentInput input, qint32 param_a, qint32 param_b)
{
    if (param_a > mCellSizeHorizontal * mSize || param_b > mCellSizeVertical * mSize)
    {
        return;
    }

    mGame->Input((GameInput)input, param_a / mCellSizeHorizontal, param_b / mCellSizeVertical);
}

void CGameComponent::TimerEvent()
{
    if (mGame->Update())
    {
        update();
    }
}

void CGameComponent::NewGame(quint8 size)
{
    mSize = size;
    //mGame.reset(new CGameOfLife(size));
    mGame.reset(new CSnakeGame(mSize));
    UpdateSizeDerivatives();
}

void CGameComponent::ShowHideGrid()
{
    mGridRenderer->Show(!mGridRenderer->Visible());
    update();
}

void CGameComponent::SetRenderer(RenderType type)
{
    mRenderType = type;
    UpdateSizeDerivatives();
}

void CGameComponent::paint(QPainter * painter)
{
    for (auto i : mDrawList)
    {
        if (i->Visible())
        {
            i->Draw(*painter);
        }
    }
}
