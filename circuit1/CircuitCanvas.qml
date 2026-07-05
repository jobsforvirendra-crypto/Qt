import QtQuick

import QtQuick.Controls

Rectangle {

    color: "#1e1e1e"

    property int gridSize: 25

    property real zoomFactor: 1.0

    Flickable{

        id: flick

        anchors.fill: parent

        contentHeight: canvasContainer.width * zoomFactor
        contentWidth:  canvasContainer.height * zoomFactor

        clip: true

        boundsBehavior: Flickable.StopAtBounds
        Rectangle{
            id: canvasContainer
            width: 4000
            height: 4000
            color:"#d2d4d6"

            scale: zoomFactor
            transformOrigin: Item.TopLeft

            Canvas{
                id: gridCanvas
                anchors.fill: parent
                onPaint: {
                    var ctx= getContext("2d")
                    ctx.reset()

                    ctx.strokeStyle = "white"
                    ctx.lineWidth = 1

                    for(var x =0; x < width; x += gridSize)
                    {
                        ctx.beginPath()
                        ctx.moveTo(x,0)
                        ctx.lineTo(x,height)
                        ctx.stroke()
                    }

                    for(var y = 0; y < height; y += gridSize)
                    {
                        ctx.beginPath()
                        ctx.moveTo(0, y)
                        ctx.lineTo(width, y)
                        ctx.stroke()
                    }


                }
            }

            Repeater{
                model: ComponentModel

                delegate: ComponentItem{
                    componentIndex: index
                    componentType: type

                    x: posX
                    y: posY
                    pinsModel: pins

                }
            }
        }
        WheelHandler{
            target: null
            onWheel: (event)=> {
                         if(event.modifiers & Qt.ControlModifier)
                         {
                            if(event.angleDelta.y > 0 )
                            {
                                zoomFactor *= 1.1
                            }
                            else
                            {
                                zoomFactor *= 0.9
                            }
                         }

                         zoomFactor = Math.max(0.3 , Math.min(zoomFactor, 3.0))

                     }
        }
    }



}
