import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import Qt.labs.settings

import hoisavegames

ApplicationWindow {
    id: window
    width: 1024
    height: 768
    visible: true
    title: qsTr("钢铁雄心4存档管理器")
    Settings {
        id: windowSettings
        property alias x: window.x
        property alias y: window.y
        property alias width: window.width
        property alias height: window.height
        property alias currentFolder: listeningFolderDialog.currentFolder
        property alias listeningFolder: listeningFolderDialog.finalSelected
    }
    menuBar: MenuBar {
        Menu {
            title: qsTr("&设置")
            Action {
                text: qsTr("&选择监听目录")
                onTriggered: listeningFolderDialog.open()
            }
        }

        FolderDialog {
            id: listeningFolderDialog
            property url finalSelected
            onAccepted: {
                finalSelected = selectedFolder
            }
        }
    }
    SaveGameListener {
        listeningFolder: windowSettings.listeningFolder

        onFileChanged: path => {
                           console.log(path, typeof path)
                           hoiModel.addSaveNodeFromPath(path)
                       }

        Component.onCompleted: {
            console.log(windowSettings.listeningFolder)
        }
    }
    SplitView {
        anchors.fill: parent
        Rectangle {
            implicitWidth: 60
            ListView {
                anchors.fill: parent
                model: hoiModel.listeningFiles()

                delegate: Rectangle {
                    implicitHeight: fileNameText.height + 10
                    implicitWidth: fileNameText.width + 10
                    border.color: "#eee"
                    border.width: 2
                    radius: 3
                    Layout.alignment: Qt.AlignHCenter
                    Text {
                        id: fileNameText
                        anchors.centerIn: parent
                        text: qsTr(modelData)
                    }
                }
            }
        }

        Rectangle {
            implicitWidth: parent.width - 60
            ListView {
                anchors.fill: parent
                id: treeList
                model: HoiModel {
                    id: hoiModel
                }
                delegate: RowLayout {
                    width: treeList.width
                    Repeater {
                        model: display
                        Rectangle {
                            implicitHeight: dateText.height + 10
                            implicitWidth: dateText.width + 10
                            border.color: "#eee"
                            border.width: 2
                            radius: 3
                            Layout.alignment: Qt.AlignHCenter
                            Text {
                                id: dateText
                                anchors.centerIn: parent
                                text: qsTr(modelData.date)
                                Component.onCompleted: {
                                    if (modelData.parentNode) {
                                        console.log(modelData.parentNode.date)
                                    }
                                    console.log(modelData.children)
                                    console.log(modelData.parentNode)
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
