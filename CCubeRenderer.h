#pragma once

#include "IRenderer.h"
#include "IGame.h"

class CCubeRenderer : public IRenderer
{
public:
    CCubeRenderer(QSharedPointer<IGame> game, qint32 w, qint32 h, qint32 c);
    virtual ~CCubeRenderer();

    virtual void Draw(QPainter & painter) override;
    virtual bool Visible() override;
    virtual void Show(bool show) override;

private:
    QSharedPointer<IGame> mGame;
    qint32 mWidth;
    qint32 mHeight;
    qint32 mCount;
};
