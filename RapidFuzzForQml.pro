TEMPLATE = lib
CONFIG += static plugin
CONFIG += c++17
CONFIG += qmltypes
QT += qml

QML_IMPORT_NAME = org.moqt.rapidfuzz
QML_IMPORT_MAJOR_VERSION = 1
QMLTYPES_FILENAME = $$PWD/qmlimports/org/moqt/rapidfuzz/plugins.qmltypes

DESTDIR = $$PWD/libs/$$first(QMAKE_PLATFORM)
TARGET = $$qtLibraryTarget($$TARGET)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/sources # Generated cpp files need access to headers

SOURCES += \
    sources/plugin.cpp \
    sources/rapidfuzz.cpp

HEADERS += \
    rapidfuzz/details/SplittedSentenceView.hpp \
    rapidfuzz/details/common.hpp \
    rapidfuzz/details/common_impl.hpp \
    rapidfuzz/details/intrinsics.hpp \
    rapidfuzz/details/matching_blocks.hpp \
    rapidfuzz/details/type_traits.hpp \
    rapidfuzz/details/types.hpp \
    rapidfuzz/distance.hpp \
    rapidfuzz/distance/Hamming.hpp \
    rapidfuzz/distance/Hamming.impl \
    rapidfuzz/distance/Indel.hpp \
    rapidfuzz/distance/Indel.impl \
    rapidfuzz/distance/LCSseq.hpp \
    rapidfuzz/distance/LCSseq.impl \
    rapidfuzz/distance/Levenshtein.hpp \
    rapidfuzz/distance/Levenshtein.impl \
    rapidfuzz/fuzz.hpp \
    rapidfuzz/fuzz.impl \
    rapidfuzz/rapidfuzz_all.hpp \
    sources/rapidfuzz.h
