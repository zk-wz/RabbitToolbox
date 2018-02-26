import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import "./controls" as OctoonControls


Rectangle{
    color: "#323232"
    Column{
        anchors.fill: parent

        Row{
            OctoonControls.OTextArea{
                text:"width:"+parent.parent.width
            }
            OctoonControls.OTextArea{
                text:"height:"+parent.parent.height
            }
        }

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


