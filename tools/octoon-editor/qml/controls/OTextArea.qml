import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.3
import QtQml 2.2

 TextArea {
      id: control
      placeholderText: qsTr("Enter description")

      background: Rectangle {
          implicitWidth: 100
          implicitHeight: 20
          border.color: control.enabled ? "#666666" : "#0078d7"
          radius: 4
      }
  }