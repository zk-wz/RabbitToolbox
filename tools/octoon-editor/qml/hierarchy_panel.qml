import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls 2.3
import "./controls" as OctoonControls


Rectangle{
    id: hierarchyPanel
    color: "#323232"
    Column{
        anchors.fill:parent

        Flow{
            id: hierarchyDockTest
            width:parent.width
            OctoonControls.OTextArea{
                text:"width:"+parent.parent.width
            }

            OctoonControls.OTextArea{
                text:"height:"+parent.parent.height
            }
        }

        Row{
            id: hierarchyPanelSearchBar
            width: parent.width
            spacing: 10
            OctoonControls.OSearchBar{
            }
        }

        Row{
            id: hierarchyPanelTreeView
            width:parent.width
            OctoonControls.OTreeView {
                id: hierarchyTree
                width:parent.width
                height: hierarchyPanel.height - hierarchyDockTest.height - hierarchyPanelSearchBar.height
                horizontalScrollBarPolicy:Qt.ScrollBarAlwaysOff
                verticalScrollBarPolicy:Qt.ScrollBarAsNeeded

                TableViewColumn {
                    title: "Name"
                    role: "name"
                }

                model: ListModel {
                    ListElement {
                        name: "A"
                    }
                    ListElement {
                        name: "B"
                    }
                }
            }
        }
    }
}

