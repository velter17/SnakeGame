#include "CGridRenderer.h"

CGridRenderer::CGridRenderer(bool show, qint32 w, qint32 h, qint32 c)
    : mShowing(show)
    , mWidth(w)
    , mHeight(h)
    , mCount(c)
    , mLines(mCount * 2 + 2)
{

}

CGridRenderer::~CGridRenderer()
{

}

void CGridRenderer::Draw(QPainter &painter)
{
    for (qint32 i = 0; i <= mCount; i++)
    {
        mLines[i].setLine(0, i * mHeight, mWidth * mCount, i * mHeight);
        mLines[i + mCount + 1].setLine(i * mWidth, 0, i * mWidth, mHeight * mCount);
    }

    painter.drawLines(mLines);
}

bool CGridRenderer::Visible()
{
    return mShowing;
}

void CGridRenderer::Show(bool show)
{
    mShowing = show;
}
