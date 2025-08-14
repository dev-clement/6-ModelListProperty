import QtQuick 2.15
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Controls

Item {
    id: rootId
    function openDialog() {
        inputDialogId.open()
    }

    property alias personNames: addPersonTextFieldId.text
    property alias personAge: addPersonAgeFieldId.value
    signal inputDialogAccepted

    Dialog {
        id: inputDialogId

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2

        width: parent.width / 2
        parent: Overlay.overlay

        focus: true
        modal: true
        title: qsTr("Person data")
        standardButtons: Dialog.Ok | Dialog.Cancel
        ColumnLayout {
            spacing: 20
            anchors.fill: parent
            Label {
                elide: Label.ElideRight
                text: qsTr("Please, enter the data")
                Layout.fillWidth: true
            }
            TextField {
                id: addPersonTextFieldId
                focus: true
                placeholderText: qsTr("Names")
                Layout.fillWidth: true
            }
            SpinBox {
                id: addPersonAgeFieldId
                editable: true
                value: 13
                Layout.fillWidth: true
            }
        }

        onAccepted: {
            console.log("Accepting person !")
            rootId.inputDialogAccepted()
        }

        onRejected: {
            console.log("Rejected adding person !")
        }
    }
}
