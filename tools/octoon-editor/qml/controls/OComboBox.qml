import QtQuick 2.6
import QtQuick.Controls 2.1

ComboBox {
    id: control

    delegate: ItemDelegate {
        width: control.width
        contentItem: Text {
            text: modelData
            color: "#000000"
            font: control.font
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }
        highlighted: control.highlightedIndex === index
    }

    indicator: Canvas {
        id: canvas
        x: control.width - width - control.rightPadding
        y: control.topPadding + (control.availableHeight - height) / 2
        width: 6
        height: 4
        contextType: "2d"

        Connections {
            target: control
            onPressedChanged: canvas.requestPaint()
        }

        onPaint: {
            context.reset();
            context.lineWidth=1;
            context.moveTo(0, 0);
            context.lineTo(width / 2, height);
            context.lineTo(width, 0);
            context.strokeStyle = "#ffffff";
            context.stroke();
        }
    }

    contentItem: Text {
        leftPadding: 5
        rightPadding: control.indicator.width + control.spacing

        text: control.displayText
        font: control.font
        color: "#ffffff"
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 120
        implicitHeight: 40
        color: "#383838"
        border.color: control.pressed ? "#0078d7" : "#666666"
        border.width: control.visualFocus ? 3 : 2
        radius: 4
    }

    popup: Popup {
        y: control.height - 1
        width: control.width
        implicitHeight: contentItem.implicitHeight
        padding: 1

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: control.popup.visible ? control.delegateModel : null
            currentIndex: control.highlightedIndex

            ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: Rectangle {
            border.color: "#666666"
            radius: 2
        }
    }
}