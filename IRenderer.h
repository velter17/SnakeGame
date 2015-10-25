#pragma once

#include <qpainter.h>

class IRenderer
{
public:
    virtual ~IRenderer() {}

    virtual void Draw(QPainter & painter) = 0;
    virtual bool Visible() = 0;
    virtual void Show(bool show) = 0;
};
