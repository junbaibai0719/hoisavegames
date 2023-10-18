import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import QtCore

import hoisavegames

ApplicationWindow {
    id: window
    width: 1024
    height: 768
    visible: true
    title: qsTr("钢铁雄心4存档管理器")
    property var notify: ({})

    Component.onCompleted: {
        console.log(notify)
    }

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
                           if (!hoiModel.restoring) {
                               hoiModel.addSaveNodeFromPath(path)
                           }
                       }
    }

    SplitView {
        anchors.fill: parent
        anchors.topMargin: 10

        Rectangle {
            implicitWidth: 60
            ListView {
                id: fileNameList
                anchors.fill: parent
                clip: true
                ScrollBar.vertical: ScrollBar {}

                model: hoiModel.listeningFiles()
                signal cleanSelected
                TapHandler {
                    onTapped: {
                        fileNameList.cleanSelected()
                    }
                }

                delegate: Rectangle {
                    id: fileNameRect

                    implicitHeight: fileNameText.height + 5
                    implicitWidth: fileNameList.width + 10
                    border.color: "#eee"
                    border.width: 2
                    radius: 3
                    Layout.alignment: Qt.AlignHCenter
                    states: [
                        State {
                            name: "hovered"
                            PropertyChanges {
                                target: fileNameRect
                                color: "#d8eaf9"
                            }
                        },
                        State {
                            name: "selected"
                            PropertyChanges {
                                target: fileNameRect
                                color: "#cce8ff"
                            }
                        }
                    ]
                    Connections {
                        target: fileNameList
                        function onCleanSelected() {
                            fileNameRect.state = ""
                        }
                    }

                    Text {
                        id: fileNameText
                        anchors.centerIn: parent
                        text: modelData.substring(modelData.lastIndexOf(
                                                      "／") + 1)
                    }
                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        propagateComposedEvents: true
                        onEntered: {
                            if (fileNameRect.state === "") {
                                fileNameRect.state = "hovered"
                            }
                        }
                        onExited: {
                            if (fileNameRect.state === "hovered") {
                                fileNameRect.state = ""
                            }
                        }
                        onPressed: {
                            fileNameRect.state = "selected"
                            hoiModel.currentFileName = modelData
                        }
                    }
                }
            }
        }

        Rectangle {
            id: treeContainer
            implicitWidth: parent.width - 60
            ListView {
                id: treeList
                anchors.fill: parent
                model: HoiModel {
                    id: hoiModel
                    onNotify: function (title, msg) {
                        var component = Qt.createComponent("Message.qml")
                        var dialog = component.createObject(window, {
                                                                "title": title,
                                                                "informativeText": msg
                                                            })
                        dialog.open()
                    }
                }

                spacing: 10
                clip: true
                ScrollBar.vertical: ScrollBar {}

                property var linePos: ({})
                signal linePosAdd
                signal cleanSelected
                TapHandler {
                    onTapped: {
                        treeList.cleanSelected()
                    }
                }
                delegate: Rectangle {
                    implicitWidth: treeContainer.width
                    implicitHeight: 30
                    RowLayout {
                        implicitWidth: display.length * 100
                        anchors.centerIn: parent
                        spacing: 30
                        Repeater {
                            model: display

                            Rectangle {
                                id: nodeRect
                                required property var modelData
                                height: dateText.height + 10
                                width: dateText.width + 10
                                border.color: "#eee"
                                border.width: 2
                                radius: 3
                                Layout.alignment: Qt.AlignHCenter
                                states: [
                                    State {
                                        name: "hovered"
                                        PropertyChanges {
                                            target: nodeRect
                                            color: "#d8eaf9"
                                        }
                                    },
                                    State {
                                        name: "selected"
                                        PropertyChanges {
                                            target: nodeRect
                                            color: "#cce8ff"
                                        }
                                    }
                                ]
                                Dialog {
                                    id: detailDialog
                                    title: modelData.date
                                    parent: Overlay.overlay
                                    x: (parent.width - width) / 2
                                    y: (parent.height - height) / 2
                                    width: parent.width * 0.7
                                    modal: false
                                    closePolicy: Dialog.NoAutoClose | Dialog.CloseOnEscape
                                    header: Rectangle {
                                        width: parent.width
                                        height: 20
                                        color: "#eee"
                                        Text {
                                            id: name
                                            text: qsTr(modelData.date)
                                        }
                                        Rectangle {
                                            id: closeRect
                                            anchors.right: parent.right
                                            anchors.rightMargin: 10
                                            anchors.topMargin: 0
                                            implicitWidth: 18
                                            implicitHeight: 18
                                            color: parent.color
                                            states: [
                                                State {
                                                    name: "hovered"
                                                    PropertyChanges {
                                                        target: closeRect
                                                        color: "#fb4d3f"
                                                    }
                                                }
                                            ]
                                            MouseArea {
                                                anchors.fill: parent
                                                hoverEnabled: true

                                                onEntered: {
                                                    closeRect.state = "hovered"
                                                }
                                                onExited: {
                                                    closeRect.state = ""
                                                }
                                                onPressed: {
                                                    detailDialog.close()
                                                }
                                            }

                                            Text {
                                                id: closeText
                                                text: "x"
                                                anchors.centerIn: parent
                                                font.bold: true
                                                font.pixelSize: 16
                                            }
                                        }

                                        MouseArea {
                                            anchors.fill: parent
                                            anchors.rightMargin: 30
                                            propagateComposedEvents: true
                                            property var startP
                                            onPressed: mouse => {
                                                           startP = Qt.point(
                                                               mouse.x, mouse.y)
                                                       }
                                            onPositionChanged: function (e) {
                                                if (pressed) {
                                                    var offset = Qt.point(
                                                                e.x - startP.x,
                                                                e.y - startP.y)
                                                    if (detailDialog.x + offset.x < 0) {
                                                        return
                                                    }
                                                    if (detailDialog.y + offset.y < 0) {
                                                        return
                                                    }

                                                    detailDialog.x += offset.x
                                                    detailDialog.y += offset.y
                                                }
                                            }
                                        }
                                    }

                                    ColumnLayout {
                                        Layout.preferredWidth: parent.width
                                        ColumnLayout {
                                            Repeater {
                                                model: ["id", "parentId", "srcPath", "filePath", "updateTime", "player", "ideology", "date", "difficulty", "version", "ironman"]
                                                delegate: RowLayout {
                                                    required property var index
                                                    required property var modelData
                                                    Text {
                                                        text: qsTr(modelData + ":")
                                                    }
                                                    Text {
                                                        Layout.maximumWidth: 500
                                                        text: nodeRect.modelData[modelData]
                                                        wrapMode: Text.WrapAnywhere
                                                    }
                                                }
                                            }
                                        }
                                        RowLayout {
                                            Layout.preferredWidth: parent.width
                                            Button {
                                                Layout.alignment: Qt.AlignRight
                                                highlighted: true
                                                text: qsTr("回档")
                                                onClicked: {
                                                    hoiModel.restore(
                                                                nodeRect.modelData)
                                                }
                                            }
                                        }
                                    }
                                }

                                Connections {
                                    target: treeList
                                    function onCleanSelected() {
                                        nodeRect.state = ""
                                    }
                                }
                                MouseArea {
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    propagateComposedEvents: true
                                    onEntered: {
                                        if (nodeRect.state === "") {
                                            nodeRect.state = "hovered"
                                        }
                                    }
                                    onExited: {
                                        if (nodeRect.state === "hovered") {
                                            nodeRect.state = ""
                                        }
                                    }
                                    onPressed: {
                                        treeList.cleanSelected()
                                        nodeRect.state = "selected"
                                        detailDialog.open()
                                    }
                                }
                                Line {
                                    id: line
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    onScenePosChanged: {
                                        treeList.linePos[modelData.id + ""]
                                                = [scenePos, Qt.point(
                                                       parent.width,
                                                       parent.height)]
                                        treeList.linePosAdd()
                                    }
                                    Connections {
                                        target: treeList
                                        function onLinePosAdd() {
                                            if (!modelData.parentNode) {
                                                return
                                            }

                                            var rect = treeList.linePos[modelData.parentNode.id
                                                                        + ""]
                                            if (!rect) {
                                                return
                                            }

                                            var pos = rect[0]
                                            var wh = rect[1]
                                            line.relativeX = pos.x - line.scenePos.x
                                            line.relativeY = (pos.y + wh.y) - line.scenePos.y
                                        }
                                    }
                                }
                                Text {
                                    id: dateText
                                    anchors.centerIn: parent
                                    text: qsTr(modelData.date)
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
