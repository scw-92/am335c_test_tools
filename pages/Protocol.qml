import QtQuick 2.6
import QtQuick.Layouts 1.0
import Qt.labs.controls 1.0


Page {
    width: 800
    height: 800


        Label {
            id: label2
            x: 36
            y: 87
            width: 85
            height: 25
            text: qsTr("本机IP:eth1")
        }

        Label {
            id: label3
            x: 36
            y: 129
            width: 85
            height: 25
            text: qsTr("目标机IP:")
        }

        TextField {
            id: local1_ip
            objectName: "local1_ip"
            x: 134
            y: 87
            height: 30
            text: qsTr("192.168.2.1")
        }

        TextField {
            id:  t_machine_ip
            objectName: "t_machine_ip"
            x: 134
            y: 129
            height: 30
            text: qsTr("192.168.1.2")
        }

        Button {
            id: set_ip1_bt
            objectName: "set_ip1_bt"
            x: 364
            y: 87
            height: 25
            text: qsTr("set_ip")
        }

        Button {
            id: ping_bt
            objectName: "ping_bt"
            x: 36
            y: 212
            width: 85
            height: 25
            text: qsTr("ping")
        }

        TextArea {
            id: ping_result
            objectName: "ping_result"
            x: 134
            y: 174
            width: 611
            height: 143
            text: qsTr("")
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            function set_text(str)
            {
               ping_result.text =  ping_result.text + str;
                // port_data_recv.append()
            }
            function set_clean()
            {
                 ping_result.text = "";
            }
        }

        Label {
            id: label1
            x: 36
            y: 45
            width: 85
            height: 25
            text: "本机IP:eht0"
        }

        TextField {
            id: local0_ip
            objectName: "local0_ip"
            x: 134
            y: 50
            width: 200
            height: 30
            text: qsTr("192.168.1.1")
        }

        Button {
            id: set_ip0_bt
            objectName: "set_ip0_bt"
            x: 364
            y: 50
            height: 25
            text: qsTr("set_ip")
        }

}
