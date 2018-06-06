
import QtQuick 2.6
import QtQuick.Layouts 1.3
import Qt.labs.controls 1.0
//import Qt.labs.controls.material 1.0
//import Qt.labs.controls.universal 1.0
import Qt.labs.settings 1.0
import "pages"


ApplicationWindow {
    id: window
    width: 360
    height: 520
    visible: true
    title: "Qt Labs Controls"

    Settings {
        id: settings
        property string style: "Material"
    }

    Timer{
            id:cmi_751_timer;
            interval: 1000;
            repeat:false;
            triggeredOnStart:false ;

            onTriggered: {
                emit:listView.send("PORT")
                console.log(listView.model.title)
            }

        }


    header: ToolBar {
        RowLayout {
            spacing: 20
            anchors.fill: parent

            ToolButton {
                label: Image {
                    anchors.centerIn: parent
                    source: "qrc:/images/drawer.png"
                }
                onClicked: drawer.open()
            }

            Label {
                id: titleLabel
                text: "Gallery"
                font.pixelSize: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            ToolButton {
                label: Image {
                    anchors.centerIn: parent
                    source: "qrc:/images/menu.png"
                }
                onClicked: optionsMenu.open()

                Menu {
                    id: optionsMenu
                    x: parent.width - width
                    transformOrigin: Menu.TopRight

                    MenuItem {
                        text: "Settings"
                        onTriggered: settingsPopup.open()
                    }
                    MenuItem {
                        text: "About"
                        onTriggered: aboutDialog.open()
                    }
                }
            }
        }
    }

    Drawer {
        id: drawer

        Pane {
            padding: 0
            width: Math.min(window.width, window.height) / 3 * 2
            height: window.height

            ListView {
                id: listView
                objectName: "ListView"
                currentIndex: -1
                property string src_page:"none"
                anchors.fill: parent
                signal send(string str,string str1);
                delegate: ItemDelegate {
                    width: parent.width
                    text: model.title
                    highlighted: ListView.isCurrentItem
                    onClicked: {
                        if (listView.currentIndex != index) {
                            listView.currentIndex = index;
                            titleLabel.text = model.title

                            emit:listView.send(model.name,listView.src_page)
                            console.log(listView.src_page +"    "+model.name);
                            listView.src_page=model.name
                            drawer.close()

                        }else
                        {
                            drawer.close();
                        }




                    }
                }

                model: ListModel {
                   ListElement { title: "PORT"; name:"port_page"}
                   ListElement { title: "GPIO";name:"gpio_page"}
                   ListElement { title: "Equipment";name:"equipment_page"}
                   ListElement { title: "Protocol";name:"protocol_page"}
                }

                ScrollIndicator.vertical: ScrollIndicator { }
            }
        }
        onClicked: close()
    }

    Port{
    id:port_page
    objectName: "port_page"
    visible:false
    }

    Gpio {
    id:gpio_page
    objectName: "gpio_page"
    visible:false
    }
    Equipment {
        id:equipment_page
        objectName: "equipment_page"
        visible:false
    }

    Protocol {
        id:protocol_page
        objectName: "protocol_page"
        visible:false
    }

    Popup {
        id: settingsPopup
        x: (window.width - width) / 2
        y: window.height / 6
        width: Math.min(window.width, window.height) / 3 * 2
        height: settingsColumn.implicitHeight + topPadding + bottomPadding
        modal: true
        focus: true
        closePolicy: Popup.OnEscape | Popup.OnPressOutside

        contentItem: ColumnLayout {
            id: settingsColumn
            spacing: 20

            Label {
                text: "Settings"
                font.bold: true
            }

            RowLayout {
                spacing: 10

                Label {
                    text: "Style:"
                }

                ComboBox {
                    id: styleBox
                    property int styleIndex: -1
                    model: ["Default", "Material", "Universal"]
                    Component.onCompleted: {
                        styleIndex = find(settings.style)
                        if (styleIndex !== -1)
                            currentIndex = styleIndex
                    }
                    Layout.fillWidth: true
                }
            }

            Label {
                text: "Restart required"
                color: "#e41e25"
                opacity: styleBox.currentIndex !== styleBox.styleIndex ? 1.0 : 0.0
                horizontalAlignment: Label.AlignHCenter
                verticalAlignment: Label.AlignVCenter
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            RowLayout {
                spacing: 10

                Button {
                    id: okButton
                    text: "Ok"
                    onClicked: {
                        settings.style = styleBox.displayText
                        settingsPopup.close()
                    }
                    Layout.preferredWidth: 0
                    Layout.fillWidth: true
                }

                Button {
                    id: cancelButton
                    text: "Cancel"
                    onClicked: {
                        styleBox.currentIndex = styleBox.styleIndex
                        settingsPopup.close()
                    }
                    Layout.preferredWidth: 0
                    Layout.fillWidth: true
                }
            }
        }
    }

    Popup {
        id: aboutDialog
        modal: true
        focus: true
        x: (window.width - width) / 2
        y: window.height / 6
        width: Math.min(window.width, window.height) / 3 * 2
        contentHeight: aboutColumn.height
        closePolicy: Popup.OnEscape | Popup.OnPressOutside

        Column {
            id: aboutColumn
            spacing: 20

            Label {
                text: "About"
                font.bold: true
            }

            Label {
                width: aboutDialog.availableWidth
                text: "The Qt Labs Controls module is a technology preview of the next generation user interface controls based on Qt Quick."
                wrapMode: Label.Wrap
                font.pixelSize: 12
            }

            Label {
                width: aboutDialog.availableWidth
                text: "In comparison to the desktop oriented Qt Quick Controls 1, the experimental Qt Labs "
                    + "Controls are an order of magnitude simpler, lighter and faster, and are primarily targeting embedded "
                    + "and mobile platforms."
                wrapMode: Label.Wrap
                font.pixelSize: 12
            }
        }
    }
}
