import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.0
import game.common 1.0

ApplicationWindow
{
    id: mainwindow
    visible: true

    property double window_size: Screen.height * 4 / 5
    property int default_margin: 5


    x: (Screen.width - window_size) / 2
    y: (Screen.height - window_size) / 2
    width: window_size
    height: window_size
    title: qsTr("Game of Life")


    menuBar: MenuBar
    {
        Menu
        {
            title: qsTr("Game")

            MenuItem
            {
                text: qsTr("New...")
                onTriggered:
                {
                    game_settings.show();
                }
            }

            MenuItem
            {
                text: qsTr("Start")
                onTriggered:
                {
                    game.Input(GameComponent.Run);
                }
            }

            MenuItem
            {
                text: qsTr("Stop")
                onTriggered:
                {
                    game.Input(GameComponent.Stop);
                }
            }

            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }

        Menu
        {
            id: render_menu
            title: qsTr("Rendering")

            MenuItem
            {
                text: qsTr("Show grid")
                checkable: true
                checked: true
                onTriggered:
                {
                    game.ShowHideGrid();
                }
            }

            MenuSeparator
            {
            }

            MenuItem
            {
                id: cube_renderer
                checkable: true
                text: qsTr("Cube renderer")
                onTriggered:
                {
                    setRenderer(GameComponent.Cube);
                    checked = true;
                }
            }

            MenuItem
            {
                id: circle_renderer
                checkable: true
                text: qsTr("Circle renderer")
                onTriggered:
                {
                    setRenderer(GameComponent.Circle);
                    checked = true;
                }
            }
        }
    }

    function update()
    {
        rect.width = mainwindow.window_size / game_settings.field_size
        rect.height = mainwindow.window_size / game_settings.field_size
    }

    function setInterval(new_interval)
    {
        game_timer.interval = new_interval;
    }

    function setRenderer(render_type)
    {
        cube_renderer.checked = false;
        circle_renderer.checked = false;
        game.SetRenderer(render_type);
    }

    GameComponent
    {
        id: game
        width: parent.width
        height: parent.height
    }

    Timer
    {
        id: game_timer
        running: true
        repeat: true
        interval: 100
        onTriggered:
        {
            game.TimerEvent();
        }
    }

    MouseArea
    {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        /*onPositionChanged:
        {
            game.Input(mouse.buttons == Qt.LeftButton ? GameComponent.UButtonDown : GameComponent.RButtonDown, mouseX, mouseY);
        }
        onClicked:
        {
            game.Input(mouse.button == Qt.LeftButton ? GameComponent.UButtonDown : GameComponent.RButtonDown, mouseX, mouseY);
        }*/
    }
Item {
    focus: true
    Keys.onUpPressed: game.Input(GameComponent.UButtonDown, 0, 0);
    Keys.onDownPressed: game.Input(GameComponent.DButtonDown, 0, 0);
    Keys.onLeftPressed: game.Input(GameComponent.LButtonDown, 0, 0);
    Keys.onRightPressed: game.Input(GameComponent.RButtonDown, 0, 0);
   // TextField {}
}


    ApplicationWindow
    {
        id: game_settings
        title: "New game"
        x: mainwindow.x + (window_size - width) / 2
        y: mainwindow.y + (window_size - height) / 2
        visible: false
        modality: Qt.WindowModal

        property int field_size: 50
        property int interval_length: 100

        Text
        {
            id: label_size
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.margins: default_margin
            text: qsTr("Field size:")
        }

        TextField
        {
            id: textfield_size
            anchors.top: label_size.bottom
            anchors.left: parent.left
            anchors.margins: default_margin
            inputMask: "99"
            text: parseInt(game_settings.field_size)
        }

        Text
        {
            id: label_speed
            anchors.top: textfield_size.bottom
            anchors.left: parent.left
            anchors.margins: default_margin
            text: qsTr("Step interval:")
        }

        TextField
        {
            id: textfield_speed
            anchors.top:  label_speed.bottom
            anchors.left: parent.left
            anchors.margins: default_margin
            inputMask: "9999"
            text: parseInt(game_settings.interval_length)
        }


        Button
        {
            id: button_create
            anchors.top: textfield_speed.bottom
            anchors.right: parent.right
            anchors.margins: default_margin
            text: qsTr("Create")
            onClicked:
            {
                setInterval(parseInt(textfield_speed.text));
                game_settings.field_size = parseInt(textfield_size.text)
                game_settings.hide()
                game.NewGame(game_settings.field_size);
            }
        }
    }
}
