import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    id:root
    visible: true
    ///width: 640
    //height: 480
    visibility: Window.FullScreen
    title: qsTr("LiveTV")

    onClosing:{
        console.log("closing........")
        homePage.close()
        close.accepted=true
    }

    HomePage{
        id:homePage
        anchors.fill: parent
    }
}
