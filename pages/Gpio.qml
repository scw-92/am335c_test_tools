import QtQuick 2.6
import QtQuick.Layouts 1.0
import Qt.labs.controls 1.0

    Page {
        id:gpio
        height: 800
        Label {
            id: label1
            x: 46
            y: 66
            width: 70
            height: 25
            text: qsTr("name")
            horizontalAlignment: Text.AlignLeft

        }

        Label {
            id: label3
            x: 226
            y: 66
            width: 70
            height: 25
            text: "available"

        }

        Label {
            id: label5
            x: 136
            y: 66
            width: 90
            height: 25
            text: qsTr("gpio_nu")
        }

        Label {
            id: label6
            x: 316
            y: 66
            width: 90
            height: 25
            text: "operation"
        }

        Label {
            id: label22
            x: 226
            y: 107
            width: 70
            height: 25
            text: "statu1"
            Image {
                id: led3
                objectName: "led3"
                anchors.fill: parent

               //source: "qrc:/images/ok_1.png"
            }
        }

        Label {
            id: label23
            x: 226
            y: 186
            width: 70
            height: 25
            text: "statu2"
            Image {
                id: led6
                objectName: "led6"
                anchors.fill: parent

               //source: "qrc:/images/ok_1.png"
            }
        }

        Label {
            id: label24
            x: 226
            y: 146
            width: 70
            height: 25
            text: "statu3"
            Image {
                id: led4
                objectName: "led4"
                anchors.fill: parent

              // source: "qrc:/images/ok_1.png"
            }
        }

        Label {
            id: label26
            x: 226
            y: 226
            width: 70
            height: 25
            //text: "ai1"

            TextField {
                id: ai1
                anchors.rightMargin: 0
                anchors.bottomMargin: 0
                anchors.topMargin: 25
                objectName: "ai1"
                anchors.fill: parent
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 12
                function set_text(voltage)
                {
                   voltage.toFixed(2);
                    ai1.text = voltage.toFixed(2) + "(mA)";
                }
            }
        }

        Label {
            id: label27
            x: 226
            y: 267
            width: 70
            height: 25
           // text: "ai2"

            TextField {
                id: ai2
                anchors.rightMargin: 0
                anchors.bottomMargin: 0
                anchors.topMargin: 25
                objectName: "ai2"
                anchors.fill: parent
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 12
                function set_text(voltage)
                {
                   voltage.toFixed(2);
                    ai2.text = voltage.toFixed(2) + "(mA)";
                }
            }

        }

        Label {
            id: label28
            x: 226
            y: 306
            width: 70
            height: 25
           // text: "ai3"

            TextField {
                id: ai3
                anchors.rightMargin: 0
                anchors.bottomMargin: 0
                anchors.topMargin: 25
                objectName: "ai3"
                anchors.fill: parent
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 12
                function set_text(voltage)
                {
                   voltage.toFixed(2);
                    ai3.text = voltage.toFixed(2) + "(mA)";
                }
            }
        }

        Label {
            id: label29
            x: 226
            y: 386
            width: 70
            height: 25
            text: "statu7"
            Image {
                id: ji115
                objectName: "ji115"
                anchors.fill: parent

               //source: "qrc:/images/ok_1.png"
            }
        }

        Label {
            id: label30
            x: 226
            y: 345
            width: 70
            height: 25
            text: "statu8"
            Image {
                id: ji116
                objectName: "ji116"
                anchors.fill: parent

               //source: "qrc:/images/ok_1.png"
            }



        }

        Label {
            id: label31
            x: 226
            y: 426
            width: 70
            height: 25
            text: "statu9"
            Image {
                id: mio2_7
                objectName: "mio2_7"
                anchors.fill: parent

               //source: "qrc:/images/ok_1.png"
            }
         }
            Label {
                id: label45
                x: 226
                y: 462
                width: 70
                height: 25
                text: "statu10"
                Image {
                    id: mio2_8
                    objectName: "mio2_8"
                    anchors.fill: parent

                   //source: "qrc:/images/ok_1.png"
                }
            }

        Label {
            id: label7
            x: 46
            y: 186
            width: 90
            height: 25
            text: qsTr("led6")
        }

        Label {
            id: label2
            x: 46
            y: 146
            width: 90
            height: 25
            text: qsTr("led4")
        }

        Label {
            id: label8
            x: 46
            y: 107
            width: 90
            height: 25
            text: qsTr("led3")
        }

        Label {
            id: label9
            x: 46
            y: 226
            width: 90
            height: 25
            text: qsTr("MIO1-1")
        }

        Label {
            id: label11
            x: 46
            y: 386
            width: 90
            height: 25
            text: "继电器2"
        }

        Label {
            id: label12
            x: 46
            y: 266
            width: 90
            height: 25
            text: "MIO1-2"
        }

        Label {
            id: label13
            x: 46
            y: 306
            width: 90
            height: 25
            text: "MIO1-3"
        }

        Label {
            id: label14
            x: 46
            y: 345
            width: 90
            height: 25
            text: "继电器1"
        }

        Label {
            id: label10
            x: 136
            y: 107
            width: 90
            height: 25
            text: qsTr("22")
        }

        Label {
            id: label15
            x: 135
            y: 146
            width: 90
            height: 25
            text: qsTr("23")
        }

        Label {
            id: label16
            x: 135
            y: 186
            width: 90
            height: 25
            text: qsTr("29")
        }

        Label {
            id: label17
            x: 135
            y: 226
            width: 90
            height: 25
            text: qsTr("AI1")
        }

        Label {
            id: label18
            x: 136
            y: 266
            width: 90
            height: 25
            text: qsTr("AI2")
        }

        Label {
            id: label19
            x: 135
            y: 306
            width: 90
            height: 25
            text: qsTr("AI3")
        }

        Label {
            id: label20
            x: 135
            y: 345
            width: 90
            height: 25
            text: qsTr("116")
        }

        Label {
            id: label21
            x: 136
            y: 386
            width: 90
            height: 25
            text: qsTr("115")
        }

        Label {
            id: label25
            x: 46
            y: 426
            width: 90
            height: 25
            text: "mio2-7"
        }

        Label {
            id: label32
            x: 135
            y: 426
            width: 90
            height: 25
            text: qsTr("45(wet1)")
        }

        Button {
            id: led3_bt
            objectName: "led3_bt"
            x: 317
            y: 107
            width: 90
            height: 25
            signal send(int nu)
            text: qsTr("operater1")
            onClicked: {
                emit:led3_bt.send(22);
            }
        }

        Button {
            id: led4_bt
            objectName: "led4_bt"
            x: 317
            y: 146
            width: 90
            height: 25
            signal send(int nu)
            text: qsTr("operater2")
            onClicked: {
                emit:led4_bt.send(23);
            }
        }

        Button {
            id: led6_bt
            objectName: "led6_bt"
            x: 317
            y: 186
            width: 90
            height: 25
            signal send(int nu)
            text: qsTr("operater3")
            onClicked: {
                emit:led6_bt.send(29);
            }
        }

        Button {
            id: ai1_bt
            objectName: "ai1_bt"
            x: 317
            y: 226
            width: 90
            height: 25
            signal send(int nu)
            text: qsTr("operater4")
            onClicked: {
                emit:ai1_bt.send(0);
            }
        }

        Button {
            id: ai2_bt
            objectName: "ai2_bt"
            x: 317
            y: 266
            width: 90
            height: 25
            signal send(int nu)
            text: qsTr("operater5")
            onClicked: {
                emit:ai2_bt.send(1);
            }
        }

        Button {
            visible: false
            id: mio2_7_bt
            objectName: "mio2_7_bt"
            x: 317
            y: 426
            width: 90
            height: 25
            signal send(int nu)
            text: qsTr("operater6")
            onClicked: {
               // emit:mio2_7_bt.send(45);
            }
        }

        Button {
            id: ai3_bt
            objectName: "ai3_bt"
            x: 317
            y: 306
            width: 90
            height: 25
            signal send(int nu)
            text: qsTr("operater7")
            onClicked: {
                emit:ai3_bt.send(2);
            }
        }

        Button {
            id: ji116_bt
            objectName: "ji116_bt"
            x: 317
            y: 345
            width: 90
            height: 25
            signal send(int nu)
            text: qsTr("operater8")
            onClicked: {
                emit:ji116_bt.send(116);
            }
        }

        Button {
            id: ji115_bt
            objectName: "ji115_bt"
            x: 317
            y: 386
            width: 90
            height: 25
            signal send(int nu)
            text: qsTr("operater9")
            onClicked: {
                emit:ji115_bt.send(115);
            }
        }

        Button {
            visible: false
            id: mio2_8_bt
            objectName: "mio2_8_bt"
            x: 319
            y: 460
            width: 90
            height: 25
            signal send(int nu)
            text: qsTr("operater10")
            onClicked: {
                //emit:mio2_8_bt.send(46);
            }
        }

        Label {
            id: label33
            x: 46
            y: 462
            width: 90
            height: 25
            text: "MIO2-8"
        }

        Label {
            id: label34
            x: 136
            y: 462
            width: 90
            height: 25
            text: qsTr("46(wet2)")
        }

        Button {
            id: button1
            objectName: "auto_open"
            x: 46
            y: 532
            text: qsTr("auto_open")
        }

        Button {
            id: button2
            objectName: "auto_close"
            x: 226
            y: 532
            text: "auto_close"
        }


    }
