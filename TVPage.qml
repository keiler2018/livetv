import QtQuick 2.0
import VLCQt 1.0

Rectangle {
    id:root
    color: "#000000"
    signal exitTv()
    function close(){
        vidwidget.stop()
    }
    property string tvUrl: ""

    onVisibleChanged: {
        if(visible){
            root.forceActiveFocus()
            vidwidget.play()

            animation.paused=false
            animation.visible=true
        }else{
            vidwidget.stop()
            animation.paused=true
            animation.visible=false
        }
    }

    Keys.enabled: true
    Keys.onPressed: {
        console.log("key...",event.key)
       switch(event.key){
       case 16777216:
            exitTv()
           break
       default:
           return
       }
       event.accepted = true
    }

    VlcVideoPlayer {
        id: vidwidget
        anchors.fill: parent
        url: tvUrl
        onStateChanged:{
            console.log("videoPlay state",state)
        }
        onPositionChanged:{
            console.log("videoPlay posistion",position)
            if(position==0){
                animation.paused=true
                animation.visible=false
            }
        }
    }

    AnimatedImage {
        id: animation
        anchors.centerIn: parent
        source: "qrc:/images/loading.gif"
        paused: true
        visible: false
    }
}
