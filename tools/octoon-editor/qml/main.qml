import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import "./controls" as OctoonControls

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    OctoonControls.OMenuBar {
        contentWidth: parent.width
        OctoonControls.OMenu {
            title: qsTr("File")
            Action { text: qsTr("New...") }
            Action { text: qsTr("Open...") }
            Action { text: qsTr("Save") }
            Action { text: qsTr("Save As...") }
            MenuSeparator { }
            Action { text: qsTr("Quit") }
        }
        OctoonControls.OMenu {
            title: qsTr("Edit")
            Action { text: qsTr("Cut") }
            Action { text: qsTr("Copy") }
            Action { text: qsTr("Paste") }
        }
        OctoonControls.OMenu {
            title: qsTr("Help")
            Action { text: qsTr("About") }
        }
    }

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
}
