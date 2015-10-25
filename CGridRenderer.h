#pragma once

#include "IRenderer.h"

class CGridRenderer : public IRenderer
{
public:
    CGridRenderer(bool show, qint32 w, qint32 h, qint32 c);
    virtual ~CGridRenderer();

    virtual void Draw(QPainter &painter) override;
    virtual bool Visible() override;
    virtual void Show(bool show) override;

private:

    bool mShowing;

    qint32 mWidth;
    qint32 mHeight;
    qint32 mCount;

    QVector<QLine> mLines;
};
