import QtQuick

Item {

    id: root

    property int componentIndex
    property string componentType
    property var pinsModel

    width: 100
    height: 50



    rotation: rotationAngle

    transformOrigin: Item.Center

    function componentSource()
    {
        switch(componentType)
        {
        case "Resistor":
            return "qrc:/qt/qml/circuit1/resources/resistor.svg"
        case "Battery":
            return "qrc:/qt/qml/circuit1/resources/battery.svg"
        case "LED":
            return "qrc:/qt/qml/circuit1/resources/LED.svg"
        case "Capacitor":
            return "qrc:/qt/qml/circuit1/resources/capacitor.svg"
        }

        return ""
    }

    Repeater{
        model: pinsModel

        delegate: Rectangle{
            width: 12
            height: 12
            radius: 6
            color: "red"

            x: modelData.x - width/2
            y: modelData.y - height/2

            border.color: "black"
            border.width: 1
        }
    }

    Image {
        id: componentImageId
        anchors.fill: parent
        source: componentSource()

        fillMode: Image.PreserveAspectFit

        smooth: true
        mipmap: true
    }

    MouseArea{
        anchors.fill: parent
        drag.target: parent

        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onDoubleClicked: {
            ComponentModel.rotateComponent(componentIndex)
        }

        onPositionChanged: {
            let grid = 25
            let snappedX = Math.round(root.x/grid) * grid

            let snappedY= Math.round(root.y/grid) * grid

            root.x = snappedX
            root.y = snappedY

            ComponentModel.moveComponent( componentIndex, snappedX, snappedY)
        }
    }
}
