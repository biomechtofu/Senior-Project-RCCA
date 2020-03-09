import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.13
import QtQuick.Controls.Material 2.1
import com.company.Communication 1.0

Window {
    id: window
    visible: true
    width: 1920
    height: 1000
    title: qsTr("SPRCCA")
    color: Material.color(Material.Amber)

    Communication{
        id: com
    }

    Graph {
        id: graph
        x: 920
        width: 1000
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
    }

    RoundButton {
        id: button
        x: 10
        y: 10
        width: 300
        height: 120
        text: qsTr("IN")
        autoRepeat: true
        font.family: "Helvetica"
        font.pointSize: 20

        //Rectangle to draw the button
        background: Rectangle {
            radius: 60
            color: Material.color(Material.LightBlue)
        }

        onClicked: {
            console.log("IN")
            com.in()
        }

    }

    RoundButton {
        id: button1
        x: 604
        y: 10
        width: 300
        height: 120
        text: qsTr("Out")
        autoRepeat: true
        font.family: "Helvetica"
        font.pointSize: 20

        background: Rectangle{
            color: Material.color(Material.LightBlue)
            radius: 60
        }

        onClicked: {
            console.log("OUT")
            com.out()
        }
    }

    RoundButton {
        id: button2
        x: 306
        y: 151
        width: 300
        height: 120
        text: qsTr("Up")
        autoRepeat: true
        font.family: "Helvetica"
        font.pointSize: 20

        background: Rectangle{
            color: Material.color(Material.LightBlue)
            radius: 60
        }

        onClicked: {
            console.log("UP")
            com.up()
            color: Material.color(Material.BlueGrey)
        }


    }

    RoundButton {
        id: button3
        x: 10
        y: 277
        width: 300
        height: 120
        text: qsTr("Left")
        autoRepeat: true
        font.family: "Helvetica"
        font.pointSize: 20

        background: Rectangle{
            color: Material.color(Material.LightBlue)
            radius: 60
        }

        onClicked: {
            console.log("LEFT")
            com.left()
            color: Material.color(Material.BlueGrey)
        }
    }

    RoundButton {
        id: button4
        x: 604
        y: 277
        width: 300
        height: 120
        text: qsTr("Right")
        autoRepeat: true
        font.family: "Helvetica"
        font.pointSize: 20

        background: Rectangle{
            color: Material.color(Material.LightBlue)
            radius: 60
        }

        onClicked: {
            console.log("RIGHT")
            com.right()
            color: Material.color(Material.BlueGrey)
        }
    }

    RoundButton {
        id: button5
        x: 306
        y: 403
        width: 300
        height: 120
        text: qsTr("Down")
        autoRepeat: true
        font.family: "Helvetica"
        font.pointSize: 20

        background: Rectangle{
            color: Material.color(Material.LightBlue)
            radius: 60
        }

        onClicked: {
            console.log("DOWN")
            com.down()
            color: Material.color(Material.BlueGrey)
        }
    }

    RoundButton {
        id: button7
        x: 306
        y: 716
        width: 300
        height: 120
        text: qsTr("Record")
        autoRepeat: true
        font.pointSize: 20
        font.family: "Helvetica"

        background: Rectangle{
            color: Material.color(Material.LightBlue)
            radius: 60
        }

        onClicked: {
            console.log("RECORD")
            color: Material.color(Material.BlueGrey)
        }
    }

    RoundButton {
        id: button8
        x: 306
        y: 870
        width: 300
        height: 120
        text: qsTr("Replay")
        autoRepeat: true
        font.pointSize: 20
        font.family: "Helvetica"

        background: Rectangle{
            color: Material.color(Material.LightBlue)
            radius: 60
        }

        onClicked: {
            console.log("REPLAY")
        }
    }

    Switch {
        id: switch1
        x: 306
        y: 569
        width: 300
        height: 120
        text: qsTr("Arm Control")
        antialiasing: false
        layer.enabled: false
        clip: false
        autoRepeat: true
        checked: true
        font.pointSize: 20

        onToggled: {
            if(switch1.checked){
                switch1.text = 'Arm Control'
                button.text = 'IN'
                button1.text = 'OUT'
                button2.text = 'Up'
                button3.text = 'LEFT'
                button4.text = 'RIGHT'
                button5.text = 'DOWN'
            }
            else {
                switch1.text = 'Head Control'
                button.text = 'ROLL LEFT'
                button1.text = 'ROLL RIGHT'
                button2.text = 'TILT UP'
                button3.text = 'PAN LEFT'
                button4.text = 'PAN RIGHT'
                button5.text = 'TILT DOWN'
            }
        }
    }
}
