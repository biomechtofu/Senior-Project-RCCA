import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Controls.Imagine 2.3
import QtQuick.Controls.impl 2.3
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Styles.Desktop 1.0
import QtQuick.Controls.Universal 2.0

Item {
    id: button

    property alias text: buttonText.text

    signal pressAndHold

    Button {
        id: buttonText
        x: 170
        y: 180
        width: 300
        height: 120
        text: buttonText.text
        font.capitalization: Font.AllUppercase
        font.pointSize: 20
        font.family: "Helvetica"
        hoverEnabled: true
        spacing: 6
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        flat: false
        icon.color: "#03A9F4"
        onClicked: newbutton.clicked()
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:1;anchors_height:120;anchors_width:300;anchors_x:170;anchors_y:180}
}
##^##*/
