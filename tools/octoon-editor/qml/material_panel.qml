import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import "./controls" as OctoonControls

Row{
    anchors.centerIn: parent
    spacing: parent.width/6

    OctoonControls.OButton{
        id: loadButton
        text: "open"
    }
    OctoonControls.OButton{
        id: saveButton
        text: "Save"
    }
    OctoonControls.OButton{
        id: exitButton
        text: "Exit"
    }
}