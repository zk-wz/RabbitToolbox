import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import "./controls" as OctoonControls


Rectangle{
    color: "#323232"
    Column{
        anchors.fill:parent

        Row{
            OctoonControls.OTextArea{
                text:"width:"+parent.parent.width
            }
            OctoonControls.OTextArea{
                text:"height:"+parent.parent.height
            }
        }

        Flow{
            width: parent.width
            spacing: 10
            OctoonControls.OSearchBar{
            }
        }

        Row{

        }
    }
}

