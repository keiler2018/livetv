import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    id:root
    visible: true
    width: 640
    height: 480
    //visibility: Window.FullScreen
    title: qsTr("LiveTV")

    property string tvUrl: ""
    Loader{
        id:mainLoader
        anchors.fill: parent
    }
    Component.onCompleted: {
        showHome()
    }

    onClosing:{
        console.log("closing........")
        homePage.close()
        tvPage.close()
    }

    function showHome(){
       tvPage.visible=false
       homePage.visible=true
    }

    function showTV(){
        tvPage.visible=true
        homePage.visible=false
    }


    HomePage{
        id:homePage
        anchors.fill: parent
        onTvClick:{
            console.log("url",url)
            root.tvUrl = url
            showTV()
        }
    }



    TVPage{
        id:tvPage
        anchors.fill: parent
        visible: false
        tvUrl: root.tvUrl
        onExitTv: {
            showHome()
        }
    }

}
