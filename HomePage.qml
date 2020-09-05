import QtQuick 2.10
import VideoModel 1.0

Rectangle{
    id:root
    color: "#000000"
    signal tvClick(string url)

    function close(){
        timer.stop()
    }

    VideoModel{
        id:videoModel
    }


    Timer {
        id:timer
        interval: 5000  //毫秒
        running: true
        repeat: true
        triggeredOnStart:true
        onTriggered: {
            videoModel.getAllImg()
        }
    }

    Component.onCompleted: {
        videoModel.getAllName()
        timer.start()
    }

    onVisibleChanged: {
        if(visible){
            gridView.forceActiveFocus()

            timer.start()
        }else{
            timer.stop()
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

            Image {
                id:iconImage
                anchors.horizontalCenter: parent.horizontalCenter
                source:"qrc:/images/default.jpg"
                anchors.fill: parent
                anchors.margins: 7
                cache: false
                fillMode:Image.PreserveAspectFit
                Connections{
                    target: videoModel
                    onImgUpdate:{
                        var imgUrl = videoModel.getImgByName(dmVideoName)
                        if(imgUrl.length>0){
                            iconImage.source=""
                            iconImage.source= "file:///"+imgUrl
                        }
                    }
                }
            }
            Image {
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 7
                height: 50
                source: "qrc:/images/bk.png"
                Text {
                    id: videoName
                    text: dmVideoName
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    font.pointSize: 20
                    anchors.verticalCenter: parent.verticalCenter
                    color: "white"
                    wrapMode: Text.WordWrap
                }
            }

             Keys.enabled: true
             Keys.onPressed: {
                 console.log("key...",event.key)
                switch(event.key){
                case 16777220:
                    tvClick(dmVideoUrl)
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
                    tvClick(dmVideoUrl)
                }
            }
        }
    }

    property int gridSpacing: 20
    GridView {
        id: gridView
        anchors.fill: parent
        anchors.margins: 20
        focus: true

        cellWidth: 350
        cellHeight: 350
        delegate: videoDelegate
        model: videoModel

        highlight: Rectangle{
            radius: 2
            color: "lightblue"
        }
    }
}
