import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15
import App 1.0

Item {
    id:gaugeId
    property alias title: titleText.text
    property real minValue: 0
    property real maxValue: 100
    property real currentValue: 50
    property SpeedTempAndDistanceCtrl controller
    property int temperature : controller ? controller.temperature : 0
    width: 150
    height: 150


    property color gaugeColor: {
        //  console.log("fuelLavel: ",fuelLavel)
        if (temperature < 50) return "#4CAF50"
        else if (temperature >= 50 && temperature <100 ) return "#FFC107"
        else return "#F44336"
    }


   // signal fuelLavel

    Rectangle{
        anchors.fill: parent
        radius: gaugeId.width/2
        border.color: "white"
        color: "#1E1E1E"
        // Title
        Text {
            id: titleText
            text: "Gauge"
            font.pixelSize: 16
            color: "white"
            anchors.centerIn: parent
            anchors.top: parent.top
            anchors.topMargin: 8
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                console.log("clicked at :",mouse.x,mouse.y)
            }
        }
    }
    Shape{
        id: gaugeShapeId
        anchors.centerIn: parent
        width: 150
        height:150
        //Geometry defined at shape level
        property real r: width/2 -20
        property real cx: width/2
        property real cy: height /2
        ShapePath{
            strokeWidth: 5
            strokeColor: gaugeId.gaugeColor
            fillColor: "transparent"
            capStyle: ShapePath.RoundCap
            startX: gaugeShapeId.cx - gaugeShapeId.r
            startY: gaugeShapeId.cy

            PathArc{
                x: gaugeShapeId.cx + gaugeShapeId.r
                y: gaugeShapeId.cy
                radiusX: gaugeShapeId.r - 20
                radiusY: gaugeShapeId.r - 20
                useLargeArc: false
                direction: PathArc.Clockwise
            }


            Component.onCompleted: {
                console.log(
                            "cx:", gaugeShapeId.cx,
                            "cy:", gaugeShapeId.cy,
                            "r:", gaugeShapeId.r,
                            "startX:", startX,
                            "startY:", startY
                            )
            }

        }
    }
    //Needle
    Rectangle{
        id: needleId
        width: 4
        height: parent.height/2 -20
        color: "red"
        radius: 2
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        transform: Rotation{
            id: needleRotationId
            origin.x: 0
            origin.y: needleId.height
            angle: -60 + (gaugeId.temperature * 1 )
            Behavior on angle {
                NumberAnimation { duration: 500; easing.type:
                        Easing.InOutQuad }
            }
        }
    }
    Text {
        id: textId
        font.pixelSize: 20
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        text: gaugeId.temperature + "C"
    }


}
