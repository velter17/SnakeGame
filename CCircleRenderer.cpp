#include "CCircleRenderer.h"

CCircleRenderer::CCircleRenderer(QSharedPointer<IGame> game, qint32 w, qint32 h, qint32 c)
    : mGame(game)
    , mWidth(w)
    , mHeight(h)
    , mCount(c)
{

}

CCircleRenderer::~CCircleRenderer()
{

}

void CCircleRenderer::Draw(QPainter &painter)
{
    if (!mGame.data())
    {
        return;
    }

    QColor c(255, 0, 0);
    QBrush b(c);

    painter.setPen(c);
    painter.setBrush(b);

    for (GameCellPos y = 0; y < mCount; y++)
    {
        for (GameCellPos x = 0; x < mCount; x++)
        {
            GameCellType v = mGame->Cell(x, y);
            if (v != 0)
            {
                painter.drawEllipse(x * mWidth + 1, y * mHeight + 1, mWidth - 2, mHeight - 2);
            }
        }
    }
}

bool CCircleRenderer::Visible()
{
    return true;
}

void CCircleRenderer::Show(bool )
{
}
