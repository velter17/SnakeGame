#include "CCubeRenderer.h"

CCubeRenderer::CCubeRenderer(QSharedPointer<IGame> game, qint32 w, qint32 h, qint32 c)
    : mGame(game)
    , mWidth(w)
    , mHeight(h)
    , mCount(c)
{

}

CCubeRenderer::~CCubeRenderer()
{

}

void CCubeRenderer::Draw(QPainter &painter)
{
    if (!mGame.data())
    {
        return;
    }

    QColor c(255, 0, 0);

    for (GameCellPos y = 0; y < mCount; y++)
    {
        for (GameCellPos x = 0; x < mCount; x++)
        {
            GameCellType v = mGame->Cell(x, y);
            if (v != 0)
            {
                painter.fillRect(x * mWidth + 1, y * mHeight + 1, mWidth - 1, mHeight - 1, c);
            }
        }
    }
}

bool CCubeRenderer::Visible()
{
    return true;
}

void CCubeRenderer::Show(bool )
{
}
