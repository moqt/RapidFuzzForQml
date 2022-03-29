import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

import org.moqt.rapidfuzz 1.0

Window {
    id: window

    width: 640
    height: 640
    visible: true
    title: qsTr("RapidFuzzForQml Example")

    TextArea {
        anchors.fill: parent
        anchors.margins: 10
        readOnly: true

        Component.onCompleted: {
            let txt =""

            txt += 'RapidFuzz.ratio("this is a test", "this is a test!")\n'
            txt += "score: " + RapidFuzz.ratio("this is a test", "this is a test!") + "\n\n"

            txt += 'RapidFuzz.partialRatio("test", "this is a test!")\n'
            txt += "score: " + RapidFuzz.partialRatio("test", "this is a test!") + "\n\n"

            txt += 'RapidFuzz.tokenSortRatio("fuzzy wuzzy was a bear", "wuzzy fuzzy was a bear")\n'
            txt += "score: " + RapidFuzz.tokenSortRatio("fuzzy wuzzy was a bear", "wuzzy fuzzy was a bear") + "\n\n"

            txt += 'RapidFuzz.tokenSortRatio("fuzzy was a bear", "fuzzy fuzzy was a bear")\n'
            txt += "score: " + RapidFuzz.tokenSortRatio("fuzzy was a bear", "fuzzy fuzzy was a bear") + "\n\n"

            txt += 'RapidFuzz.tokenSetRatio("fuzzy was a bear", "fuzzy fuzzy was a bear")\n'
            txt += "score: " + RapidFuzz.tokenSetRatio("fuzzy was a bear", "fuzzy fuzzy was a bear") + "\n\n"

            txt += 'RapidFuzz.extractOne(["fuzzy wuzzy", "was a bear"], ["fuzzy logic", "was a beer"])\n'
            const extractOneResult = RapidFuzz.extractOne(["fuzzy wuzzy", "was a bear"], ["fuzzy logic", "was a beer"])
            txt += "result: " + JSON.stringify(extractOneResult)  + "\n\n"

            txt += 'RapidFuzz.extract(["fuzzy wuzzy", "was a bear"], ["fuzzy logic", "was a beer"])\n'
            const extractResult = RapidFuzz.extract(["fuzzy wuzzy", "was a bear"], ["fuzzy logic", "was a beer"])
            txt += "results: " + JSON.stringify(extractResult) + "\n\n"

            text = txt
        }
    }
}
