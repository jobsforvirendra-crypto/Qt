import QtQuick
import QtQuick.Controls

Rectangle {

    color: "#2b2b2b"
    Column{
        spacing: 10
        anchors.centerIn: parent

        Repeater{
            model: ["Resistor","Battery","LED","Capacitor"]

            delegate: Rectangle{
                width: 140
                height: 50
                radius: 6
                color: "#404040"

                Text{
                    anchors.centerIn: parent
                    color: "white"
                    text: modelData
                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        ComponentModel.addComponent(
                                    modelData,
                                    300,
                                    200)
                    }
                }
            }
        }
    }
}
