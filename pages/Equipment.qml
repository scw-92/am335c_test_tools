import QtQuick 2.6
import QtQuick.Layouts 1.0
import Qt.labs.controls 1.0


    Page {
        Label {
            id: label1
            x: 214
            y: 188
            width: 90
            height: 25
            text: qsTr("NAME")
        }

        Label {
            id: label2
            x: 214
            y: 228
            width: 90
            height: 25
            text: qsTr("SD")
        }

        Label {
            id: label3
            x: 343
            y: 188
            width: 70
            height: 25
            text: qsTr("status")
        }

        Label {
            id: label4
            x: 343
            y: 228
            width: 70
            height: 25
            text: "statu"
            Image {
                id: sd
                objectName: "sd"
                anchors.fill: parent

               source: "qrc:/images/no_avi.png"
            }
        }

        Label {
            id: label5
            x: 214
            y: 268
            width: 90
            height: 25
            text: qsTr("i2c2")
        }

        Label {
            id: label6
            x: 343
            y: 268
            width: 70
            height: 25
            text: "statu"
            Image {
                id: i2c2
                objectName: "i2c2"
                anchors.fill: parent

               source: "qrc:/images/no_avi.png"
            }
        }

        Label {
            id: label7
            x: 214
            y: 308
            width: 90
            height: 25
            text: qsTr("usb")
        }

        Label {
            id: label8
            x: 343
            y: 308
            width: 70
            height: 25
            text: "statu"
            Image {
                id: usb2
                objectName: "usb2"
                anchors.fill: parent
                source: "qrc:/images/no_avi.png"
            }
        }

        Label {
            id: label9
            x: 214
            y: 349
            width: 90
            height: 25
            text: "rtc"
        }

        Label {
            id: label10
            x: 343
            y: 349
            width: 70
            height: 25
            text: qsTr("rtc_s")
            Image {
                id: rtc
                objectName: "rtc"
                anchors.fill: parent
                source: "qrc:/images/no_avi.png"
            }
        }

    }



