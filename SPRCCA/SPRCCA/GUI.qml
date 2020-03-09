import QtQuick 2.0
import Qt.labs.location 1.0
import QtQuick.Layouts 1.3
import Qt3D.Input 2.1
import QtDataVisualization 1.3


Rectangle{
    id: mainView

    width: 500
    height: 500

    Theme3D{
        id: themeIsabelle
        type: Theme3d.ThemeIsabelle
        font.family: "Helvetica"
        font.pointSize:  40
    }

    Theme3D{
        id: themeArmyBlue
        type: Theme3D.ThemeArmyBlue
    }

    Item{
        id: dataView
        anchors.bottom: parent.bottom

        width: parent.width
        height: parent.height

        Scatter3D{
            id: scatterGraph
            anchors.fill: parent

            theme: themeIsabelle
            shadowQuality: AbstractGraph3D.ShadowQualitySoftLow

            Scatter3DSeries{
                id: scatterSeries
                itemLabelFormat: "Series 1: X:@xLabel Y:@yLabel Z: @zLabel"

                ItemModelScatterDataProxy{
                    itemModel: seriesData.mel
                    xPosRole: "xPos"
                    yPosRole: "yPos"
                    zPosRole: "zPos"
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:4;anchors_height:500;anchors_width:500}
}
##^##*/
