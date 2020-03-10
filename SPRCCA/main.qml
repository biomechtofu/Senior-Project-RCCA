import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.13
import QtQuick.Controls.Material 2.1
import com.company.Communication 1.0
import QtDataVisualization 1.3

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

    Scatter3D {
        id: scatter3D
        x: 923
        width: 997
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        theme: mytheme
        shadowQuality: AbstractGraph3D.ShadowQualitySoftLow
        Scatter3DSeries {
            ItemModelScatterDataProxy {
                zPosRoleReplace: qsTr("")
                itemModel: com
                yPosRole: "y"
                xPosRole: "x"
                zPosRole: "z"
            }
        }
    }

    RoundButton {
        id: button
        x: 10
        y: 10
        width: 300
        height: 120
        text: qsTr("In")
        autoRepeat: true
        font.family: "Helvetica"
        font.pointSize: 20

        //Rectangle to draw the button
        background: Rectangle {
            radius: 60
            color: Material.color(Material.LightBlue)
        }

        onClicked: {
            console.log("In")
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
            console.log("Out")
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
            if(switch1.checked) {
                console.log("Up")
                com.up()
            }
            else {
                console.log("Tilt Up")
                com.tiltup()
            }
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
            if(switch1.checked) {
                console.log("Left")
                com.left()
            }
            else {
                console.log("Pan Left")
                com.panleft()
            }
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
            if(switch1.checked){
                console.log("Right")
                com.right()
            }
            else {
                console.log("Pan Right")
                com.panright()
            }
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
            if(switch1.checked) {
                console.log("Down")
                com.down()
            }
            else {
                console.log("Tilt Down")
                com.tiltdown()
            }
        }
    }

    RoundButton {
        id: button7
        x: 306
        y: 716
        width: 300
        height: 120
        text: qsTr("Record")
        font.pointSize: 20
        font.family: "Helvetica"

        background: Rectangle{
            color: Material.color(Material.LightBlue)
            radius: 60
        }

        onClicked: {
            console.log("Record")
            com.record()
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
            console.log("Replay")
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
                button.text = 'In'
                button1.text = 'Out'
                button2.text = 'Up'
                button3.text = 'Left'
                button4.text = 'Right'
                button5.text = 'Down'
            }
            else {
                switch1.text = 'Head Control'
                button.text = 'Roll Left'
                button1.text = 'Roll Right'
                button2.text = 'Tilt Up'
                button3.text = 'Pan Left'
                button4.text = 'Pan Right'
                button5.text = 'Tilt Down'
            }
        }
    }

    Theme3D {
        id: mytheme
        type: Q3DTheme.ThemeUserDefined
        backgroundColor: Material.color(Material.LightBlue)
        windowColor: Material.color(Material.Amber)
        labelTextColor: "black"
        labelBackgroundEnabled: false
        labelBorderEnabled: false
    }

}
