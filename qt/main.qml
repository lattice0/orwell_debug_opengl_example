import QtQuick 2.0

import OpenGlVideoQtQuick2 1.0

Grid {
    columns: 2
    spacing: 2    
    width: 1280
    height: 720
  
    OpenGlVideoQtQuick2 {
        width: 640
        height: 360
        uri: "rtsp://admin:19929394@192.168.1.198:10554/tcp/av0_0"
    }
    
}
