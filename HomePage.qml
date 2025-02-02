﻿import QtQuick 2.3
import VideoModel 1.0

Rectangle{
    id:root
    color: "#000000"

    function close(){
        timer.stop()
    }

    VideoModel{
        id:videoModel
    }


    Timer {
        id:timer
        interval: 3000  //毫秒
        running: false
        repeat: true
        triggeredOnStart:true
        onTriggered: {
            console.log("timer triggered...........")
            videoModel.getAllImg()

        }
    }

    Component.onCompleted: {
        videoModel.getAllName()
        //timer.start()
    }

    onVisibleChanged: {
        if(visible){
            gridView.forceActiveFocus()

            //timer.start()
        }else{
            //timer.stop()
        }
    }

    Component {
        id: videoDelegate
        Rectangle {
            id:videoRectangle
            width: gridView.cellWidth - root.gridSpacing
            height: gridView.cellHeight - root.gridSpacing
            color: Qt.rgba(1,1,1,0.3)
            radius: 2
            //color: GridView.isCurrentItem?"#157efb":"#53d769"

//            Image {
//                id:iconImage
//                anchors.horizontalCenter: parent.horizontalCenter
//                source:"qrc:/images/default.jpg"
//                anchors.fill: parent
//                anchors.margins: 7
//                cache: false
//                fillMode:Image.PreserveAspectFit
//                Connections{
//                    target: videoModel
//                    onImgUpdate:{
//                        var imgUrl = videoModel.getImgByName(dmVideoName)
//                        if(imgUrl.length>0){
//                            iconImage.source=""
//                            iconImage.source= "file:///"+imgUrl
//                        }
//                    }
//                }
//            }
//            Image {
//                anchors.bottom: parent.bottom
//                anchors.left: parent.left
//                anchors.right: parent.right
//                anchors.margins: 7
//                height: 50
//                source: "qrc:/images/bk.png"
                Text {
                    id: videoName
                    text: dmVideoName
                    //anchors.left: parent.left
                    //anchors.leftMargin: 10
                    font.pointSize: 30
                   // anchors.verticalCenter: parent.verticalCenter
                    anchors.centerIn: parent
                    color: "white"
                    wrapMode: Text.WordWrap
                }
           // }

             Keys.enabled: true
             Keys.onPressed: {
                 console.log("key...",event.key)
                switch(event.key){
                case 16777220:
                    videoModel.playUrl(dmVideoUrl)
                    break
                default:
                    return
                }
                event.accepted = true
             }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    gridView.currentIndex = index
                }
                onDoubleClicked: {
                    videoModel.playUrl(dmVideoUrl)
                }
            }
        }
    }





    property int gridSpacing: 30
    GridView {
        id: gridView
        anchors.fill: parent
        anchors.centerIn: parent
        anchors.margins: 20
        focus: true

        cellWidth: 200
        cellHeight: 80
        delegate: videoDelegate
        model: videoModel

        highlight: Rectangle{
            radius: 2
            color: "lightblue"
        }
    }
}
