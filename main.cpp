#include <QtQuick>
#include <qguiapplication.h>

#include "CGameComponent.h"
#include <ctime>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<CGameComponent>("game.common", 1, 0, "GameComponent");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    srand(time(NULL));

    return app.exec();
}

