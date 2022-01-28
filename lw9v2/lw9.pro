QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    src/common/HarmonicDTO.cpp \
    src/common/HarmonicType.cpp \
    src/controller/ChartDrawerController.cpp \
    src/model/Harmonic.cpp \
    src/model/HarmonicStorage.cpp \
    src/view/ChartDrawerView.cpp \
    src/view/ChartGraphicView.cpp \
    src/view/CreateNewHarmonicView.cpp \
    src/view/HarmonicEditor.cpp \
    src/view/HarmonicList.cpp \
    src/view/HarmonicListItem.cpp

HEADERS += \
    src/common/HarmonicDTO.h \
    src/common/HarmonicType.h \
    src/controller/ChartDrawerController.h \
    src/controller/IChartDrawerController.h \
    src/controller/IChartDrawerControllerCreator.h \
    src/controller/IControllerHarmonicEditor.h \
    src/model/Harmonic.h \
    src/model/HarmonicStorage.h \
    src/model/IEditedHarmonic.h \
    src/model/IGetSumYHarmonicStorage.h \
    src/model/IHarmonic.h \
    src/model/IHarmonicStorage.h \
    src/model/IHarmonicsStorageGetter.h \
    src/view/ChartDrawerView.h \
    src/view/ChartGraphicView.h \
    src/view/CreateNewHarmonicView.h \
    src/view/HarmonicEditor.h \
    src/view/HarmonicList.h \
    src/view/HarmonicListItem.h

FORMS += \
    src/view/ChartDrawerView.ui \
    src/view/CreateNewHarmonicView.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
