#pragma once

#include <cstdint>
#include <qobject.h>
#include <QtQuick>

#include "IRenderer.h"
#include "IGame.h"

const qint32 DefaultGameFieldSize = 10;

class CGameComponent : public QQuickPaintedItem
{
    Q_ENUMS(RenderType)
    Q_ENUMS(GameComponentInput)
    Q_OBJECT
public:

    enum class RenderType
    {
        Cube,
        Circle,
    };

    enum class GameComponentInput
    {
        Run,
        Stop,
        LButtonDown,
        RButtonDown,
        UButtonDown,
        DButtonDown,
        Total,
    };

    explicit CGameComponent(QQuickItem *parent = 0);
    virtual ~CGameComponent();


    Q_INVOKABLE void Input(GameComponentInput input, qint32 param_a = 0, qint32 param_b = 0);
    Q_INVOKABLE void TimerEvent();

    Q_INVOKABLE void NewGame(quint8 size);
    Q_INVOKABLE void ShowHideGrid();
    Q_INVOKABLE void SetRenderer(RenderType type);

protected:

    virtual void paint(QPainter *) override;
    virtual void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;

    void UpdateSizeDerivatives();

private:
    qint32 mSize;
    qint32 mCellSizeHorizontal;
    qint32 mCellSizeVertical;

    QList<IRenderer *> mDrawList;
    QSharedPointer<IGame> mGame;

    RenderType mRenderType;
    IRenderer * mGridRenderer;
};
