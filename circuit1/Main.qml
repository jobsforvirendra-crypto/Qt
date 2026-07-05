import QtQuick

import QtQuick.Controls
import QtQuick.Layouts
ApplicationWindow {
    width: 1400
    height: 900
    visible: true
    title: qsTr("Dragable Canvas")

    RowLayout{
        anchors.fill: parent

        Toolbox{
            Layout.preferredWidth: 200

        }

        CircuitCanvas{
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }

}
