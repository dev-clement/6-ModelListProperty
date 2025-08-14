import QtQuick 2.15
import QtQuick.Layouts
import QtQuick.Dialogs
import QtQuick.Controls
import ModelListProperty

Window {
    id: rootId
    width: 640
    height: 480
    visible: true
    title: qsTr("Decoupling the data source")

    ColumnLayout {
        anchors.fill: parent

        PersonModel {
            id: modelId
            persons: [
                Person{
                    names: "Daniel Gakwaya"
                    favoriteColor: "yellow"
                    age : 34
                },
                Person{
                    names: "Gwiza Luna"
                    favoriteColor: "blue"
                    age : 1
                },
                Person{
                    names: "Steve Barker"
                    favoriteColor: "yellowgreen"
                    age : 22
                }
            ]
        }

        ListView {
            id: listViewId
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: modelId
            delegate: Rectangle {
                height: 90
                width: rootId.width
                radius: 10
                color: favoriteColor

                RowLayout {
                    anchors {
                        fill: parent
                        margins: 20
                    }

                    TextField {
                        id: textFieldId
                        text: names
                        height: spinBoxId.height
                        Layout.fillWidth: true

                        onEditingFinished: {
                            console.log("Editing finished text: " + text + " at the index: " + index)
                            names = text
                        }
                    }

                    SpinBox {
                        id: spinBoxId
                        editable: true
                        Layout.fillWidth: true

                        onValueChanged: {
                            console.log("Editing age finished, age: " + value + " at the ndex: " + index)
                            age = value
                        }
                        Component.onCompleted: {
                            value = age
                        }
                    }

                    Rectangle {
                        width: 50
                        height: spinBoxId.height
                        color: favoriteColor
                        border.color: "black"

                        MouseArea {
                            anchors.fill: parent
                            ColorDialog {
                                id: colorDialogId
                                title: qsTr("Please, pick a color")
                                onAccepted: {
                                    console.log("You chose: " + colorDialogId.selectedColor)
                                    favoriteColor = colorDialogId.selectedColor
                                }
                                onRejected: {
                                    console.log("Abort")
                                }
                            }
                            onClicked: {
                                colorDialogId.open()
                            }
                        }
                    }
                }
            }
        }
        RowLayout {
            width: parent.width
            Button {
                Layout.fillWidth: true
                height: 50
                text: qsTr("Add a person")
                onClicked: {
                    inputId.openDialog()
                }

                InputDialog {
                    id: inputId
                    onInputDialogAccepted: {
                        console.log("Here in main, dialog is accepted !")
                        console.log("names: " + personNames + " age: " + personAge)
                        modelId.addPerson(personNames, "red", personAge)
                    }
                }
            }
            Button {
                Layout.fillWidth: true
                height: 50
                text: qsTr("Remove last person")
                onClicked: {
                    modelId.removeLastPerson()
                }
            }
        }
    }
}
