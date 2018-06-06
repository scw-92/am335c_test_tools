import QtQuick 2.6
import QtQuick.Layouts 1.0
import Qt.labs.controls 1.0


Page  {
               //visible:false

               id:port_page
               objectName: "port_page"

               Label {
                   id: label2
                   x: 55
                   y: 95
                   text: qsTr("接收区")
               }

               Label {
                   id: label3
                   x: 55
                   y: 233
                   text: qsTr("发送区")
               }

               Label {
                   id: label4
                   x: 62
                   y: 340
                   width: 65
                   height: 25
                   text: "串口文件:"
               }

               Label {
                   id: label5
                   x: 63
                   y: 376
                   width: 65
                   height: 25
                   text: qsTr("数据位:")
               }

               TextField {
                   id: port_nu_file
                   objectName: "port_nu_file"
                   x: 150
                   y: 340
                   width: 100
                   height: 25
                   text: qsTr("/dev/ttyS1")
                   horizontalAlignment: Text.AlignHCenter
                   font.pixelSize: 12
               }

               ComboBox {
                   id: port_data_bit
                   objectName: "port_data_bit"
                   x: 150
                   y: 376
                   width: 65
                   height: 25
                   model:[8,7,6,5]
               }

               Label {
                   id: label6
                   x: 259
                   y: 340
                   width: 65
                   height: 25
                   text: qsTr("波特率:")
               }

               Label {
                   id: label7
                   x: 259
                   y: 376
                   width: 65
                   height: 25
                   text: qsTr("停止位:")
               }

               ComboBox {
                   id: port_speed
                   objectName: "port_speed"
                   x: 334
                   y: 340
                   width: 100
                   height: 25
                   model:[115200,9600]
               }

               ComboBox {
                   id: port_stop
                   objectName: "port_stop"
                   x: 334
                   y: 376
                   width: 100
                   height: 25
                   model:[0,1,2]
               }

               Label {
                   id: label8
                   x: 436
                   y: 340
                   width: 65
                   height: 25
                   text: qsTr("检验位:")
               }

               Label {
                   id: label9
                   x: 436
                   y: 376
                   width: 65
                   height: 25
                   text: qsTr("流控制:")
               }

               ComboBox {
                   id: port_check
                   objectName: "port_check"
                   x: 520
                   y: 340
                   width: 100
                   height: 25
                   model: [0,1,2]
               }

               ComboBox {
                   id: port_flow_con
                   objectName: "port_flow_con"
                   x: 520
                   y: 376
                   width: 100
                   height: 25
                   model:["none","soft","hard"]
               }

               Label {
                   id: label10
                   x: 62
                   y: 417
                   width: 95
                   height: 25
                   text: "接收间隔(ms):"
               }

               TextField {
                   id: port_recv_time
                   objectName: "port_recv_time"
                   x: 173
                   y: 417
                   width: 80
                   height: 25
                   font.pixelSize: 12
                   text: qsTr("1000")

               }

               Label {
                   id: label11
                   x: 436
                   y: 417
                   width: 95
                   height: 25
                   text: qsTr("发送间隔(ms):")
               }

               TextField {
                   id: port_send_time
                   objectName: "port_send_time"
                   x: 541
                   y: 417
                   width: 80
                   height: 25
                   text: qsTr("1000")
                   horizontalAlignment: Text.AlignLeft
                   font.pixelSize: 12
               }

               Button {
                   id: port_on
                   objectName: "port_on"
                   x: 63
                   y: 450
                   height: 30
                   text: qsTr("打开串口")

               }

               Button {
                   id: port_close
                   objectName: "port_close"
                   x: 436
                   y: 450
                   height: 30
                   text: qsTr("关闭串口")
               }

               TextArea {
                   id: port_data_recv
                   objectName: "port_data_recv"
                   x: 136
                   y: 52
                   width: 484
                   height: 115
                   text:""
                   verticalAlignment: Text.AlignTop
                   wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                   function set_text(str)
                   {
                      port_data_recv.text =  port_data_recv.text + str;
                      // port_data_recv.append()
                   }

               }

                TextArea {
                    id: port_data_send
                    objectName: "port_data_send"
                   // anchors.fill: parent
                    x: 136
                    y: 171
                    width: 485
                    height: 115
                    text:""
                    wrapMode: TextArea.Wrap


               }

       }
