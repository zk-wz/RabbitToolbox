import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.3
import QtQml 2.2

Button {
     contentItem: Text {
         text: parent.text
         font: parent.font
         opacity: enabled ? 1.0 : 0.3
         color: "#ffffff"
         horizontalAlignment: Text.AlignHCenter
         verticalAlignment: Text.AlignVCenter
         elide: Text.ElideRight
     }

     background: Rectangle {
         implicitWidth: 100
         implicitHeight: 40
         opacity: enabled ? 1 : 0.3
         color: parent.down ? "#5f8ac1" : "#646464"
         border.color: "#4a4a4a"
         border.width: 1
         radius: 2
     }
 }
