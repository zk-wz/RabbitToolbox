import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4
import QtQuick.Controls 2.3
import QtQml 2.2

TreeView {
    headerDelegate: Component{  
        Rectangle{ 
            height: 20
            color:"#1e1e1e"
            Text{
                text: styleData.value  
                anchors.centerIn: parent  
                font.family: "Helvetica Neue"
                font.pixelSize: 12
                color: "white"
            }
        }  
    }

    rowDelegate: Component{  
        Rectangle{
            height: 20
            color: "#323232"
        }
    }

    itemDelegate: Rectangle{
        anchors.fill: parent
        anchors.margins: 3
        color: styleData.selected ? "#3a3a3a" : "#323232"
    
        Text{
            anchors.left: parent.left
            anchors.leftMargin: 10
            text:styleData.value
            font.family: "Helvetica Neue"
            font.pixelSize: 12
            color: styleData.selected ? "#17bcb9" : "white"
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter  
            horizontalAlignment: Text.AlignHCenter  
        }
    }
}