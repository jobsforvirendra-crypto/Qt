import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Shapes 1.15
import App 1.0

Window {
    id:rootId
    width: 800
    height: 400
    visible: true
    title: qsTr("Cluster Hood")
    property bool isEngineStarted: false
    property int speed: dialCtrlId.speed
    property string gaer: {
        if(speed == 0) return "0"
        else if (speed <10) return "1"
        else if(speed > 10 && speed <= 40 ) return "2"
        else if(speed > 40 && speed <= 60) return "3"
        else if(speed > 60 && speed <= 80) return "4"
        else if(speed > 80 && speed <= 100) return "5"
        else return "6"
    }

    SpeedTempAndDistanceCtrl{
        id:dialCtrlId
    }

    Rectangle{
        width: 800
        height: 400
        anchors.fill: parent
        anchors.centerIn: parent
        color: "#222222"

        SpeedMeter{
            id: speedoMeeterId
            controller: dialCtrlId
            title:"Speed (Km/h)"
            minValue: 0
            maxValue: 240
            currentValue: 80
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -100
        }

        CustomGauge{
            id: fuelGaugeId
            controller: dialCtrlId
            title:"Fuel Level"
            minValue: 0
            maxValue: 100
            currentValue: 100
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: 20
        }
        TemperatureGauge{
            id: tempGauge
            controller: dialCtrlId
            title: "Engine Temp (°C)"
            minValue: 0
            maxValue: 120
            currentValue: 90
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: 20
        }

        // Gear Indicator
        Rectangle {
            id: gearIndicatorId
            width: 120
            height: 120
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.margins: 30
            radius: 60
            color: "#444444"
            border.color: "#BBBBBB"
            border.width: 3

            Text {
                id:gearTextId
                text: rootId.gaer
                font.pixelSize: 48
                color: "white"
                anchors.centerIn: parent
            }
        }

        //overheating BusyIndicator
        Rectangle{
            id: overheatingIndicatorId
            width: 50
            height: 50
            anchors.right : parent.right
            anchors.bottom: tempGauge.top
            // anchors.top: parent.top
            anchors.rightMargin: 30
            anchors.bottomMargin: 30
            radius: 30
            color: dialCtrlId.isOverHeating ? "red" : "green"
        }
        Text{
            id: tempText
            text:"Temp Ind"
            color: "white"
            anchors.right : parent.right
            anchors.bottom: overheatingIndicatorId.top
            anchors.rightMargin: 30
        }


        //Start
        Button{
            id:startId
            width: 80
            height: 50
            anchors.right:  gearIndicatorId.left
            anchors.bottom: parent.bottom
            anchors.margins: 30
            text: isEngineStarted ? "STOP" : "START"
            background: Rectangle{
                width: parent.width
                height: parent.height
                color: isEngineStarted ? "red" : "green"
            }
            contentItem: Text {
                text: startId.text
                color: "white"
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                anchors.fill: parent

            }
            onClicked: {
                isEngineStarted = !isEngineStarted

                if(isEngineStarted)
                {
                    gearIndicatorId.color = "yellowgreen"
                    acceleratorId.enabled = true
                }
                else{
                    gearIndicatorId.color = "gray"
                    dialCtrlId.stopAcceleration()
                    acceleratorId.enabled = false
                }
            }


        }
        //Accelerator
        Button{
            id:acceleratorId
            width: 80
            height: 50
            anchors.left:  gearIndicatorId.right
            anchors.bottom: parent.bottom
            anchors.margins: 30
            text: "A"
            font.pointSize: 20
            enabled: false
            onPressedChanged: {
                fuelUpId.value = 0
                pressed ? dialCtrlId.startAcceleration() : dialCtrlId.stopAcceleration()
            }

        }

        Slider{
            id:fuelUpId
            from: 0
            to: 100
            anchors.right: startId.left
            anchors.bottom: parent.bottom
            anchors.margins: 30
            onMoved: {
                //console.log("value"+ value)
                if (value > dialCtrlId.fuel) {
                    dialCtrlId.fuel = value
                } else {
                    value = dialCtrlId.fuel   // snap back
                }
            }
        }



    }
}
