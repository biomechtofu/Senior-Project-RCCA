import QtQuick 2.0
import QtDataVisualization 1.3
import QtQuick.Controls.Material 2.1

Item {
    Scatter3D {
        id: scatter3D
        objectName: "graph"
        anchors.fill: parent
        theme: mytheme
        shadowQuality: AbstractGraph3D.ShadowQualitySoftLow
        Scatter3DSeries {
            ItemModelScatterDataProxy {
                xPosRole: "x"
                zPosRole: "z"
                yPosRole: "y"
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

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:1;anchors_height:480;anchors_width:640;anchors_x:0;anchors_y:0}
}
##^##*/
