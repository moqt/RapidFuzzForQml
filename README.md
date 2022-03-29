# RapidFuzzForQml
QML API to [rapidfuzz-cpp](https://github.com/maxbachmann/rapidfuzz-cpp).

RapidFuzzForQml contains copy of [rapidfuzz-cpp](https://github.com/maxbachmann/rapidfuzz-cpp) impl files to simplify dependencies. 

***Tested with Qt 6.2.3, 5.15.2***

## Integration
RapidFuzzForQml is a static library. See [example](https://github.com/moqt/RapidFuzzForQml/tree/main/example) folder and [RapidFuzzExample.pro](https://github.com/moqt/RapidFuzzForQml/blob/main/example/RapidFuzzExample.pro) how to link library and register qml types.

## QML

Import module:
```qml
import org.moqt.rapidfuzz 1.0
```

RapidFuzz is a singleton:
```qml
const score = RapidFuzz.ratio("this is a test", "this is a test!")
```

## Example
```
RapidFuzz.ratio("this is a test", "this is a test!")
score: 96.55172413793103

RapidFuzz.partialRatio("test", "this is a test!")
score: 100

RapidFuzz.tokenSortRatio("fuzzy wuzzy was a bear", "wuzzy fuzzy was a bear")
score: 100

RapidFuzz.tokenSortRatio("fuzzy was a bear", "fuzzy fuzzy was a bear")
score: 84.21052631578947

RapidFuzz.tokenSetRatio("fuzzy was a bear", "fuzzy fuzzy was a bear")
score: 100

RapidFuzz.extractOne(["fuzzy wuzzy", "was a bear"], ["fuzzy logic", "was a beer"])
result: [90,"was a beer"]

RapidFuzz.extract(["fuzzy wuzzy", "was a bear"], ["fuzzy logic", "was a beer"])
results: [[54.54545454545454,"fuzzy logic"],[90,"was a beer"]]

```

