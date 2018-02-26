import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls 2.3
import "./controls" as OctoonControls

Rectangle{
    id: consolePanel
    color: "#323232"
    Column{
        anchors.fill:parent
        padding: 5
        Row{
            id: consolePanelOutput
            width:parent.width
            ScrollView {
                id: scrollView
                width:parent.width
                height:consolePanel.height - consolePanelInput.height
                ListView {
                    id: consolePanelResultList
                    model: ListModel {
                        id: outputModel
                        ListElement {
                            line: "Bill Smith"
                        }
                        ListElement {
                            line: "John Brown"
                        }
                        ListElement {
                            line: "Sam Wise"
                        }
                    }
                    delegate: Column {
                        width: ListView.view.width
                        height: 14
                        Label {
                            width: parent.width
                            color: 'white'
                            text: " > " + model.line
                        }
                        Rectangle {
                            height: 1
                            width: parent.width
                            color: '#ffffff'
                            opacity: 0.2
                        }
                    }
                }
            }

        }
        
        Row{
            id: consolePanelInput
            width:parent.width
            padding: 5
            OctoonControls.OTextArea{
                height:25
                width:parent.width-60
            }
            OctoonControls.OButton{
                height:25
                width:60
                text: "send"
            }
        }
    }
}