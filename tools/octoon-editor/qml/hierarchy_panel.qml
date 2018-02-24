import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import "./controls" as OctoonControls

Column{
    anchors.fill: parent

    Row{
        OctoonControls.OComboBox{
            model: ["First", "Second", "Third"]
            width: 64
            height: 24
        }
        OctoonControls.OTextArea{
            
        }

 
    }

    Row{

    }
}