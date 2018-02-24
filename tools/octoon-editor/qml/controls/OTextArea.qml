import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.3
import QtQml 2.2

TextArea {
    id: control
    placeholderText: qsTr("Enter description")

    color:"#c8c8c8"
    font.pixelSize:10
    font.family:"Helvetica Neue"
    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 14
        border.color: control.enabled ? "#141414" : "#0078d7"
        color: "#3c3c3c"
        radius: 2
    }
}