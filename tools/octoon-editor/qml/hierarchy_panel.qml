import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import "./controls" as OctoonControls

Column{
    width: 260
    height: 400

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
        anchors.margins: 4
        spacing: 10
        OctoonControls.OSearchBar{
        }
    }

    Row{

    }
}