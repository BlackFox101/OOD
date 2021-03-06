QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    src/common/harmonicdto.cpp \
    src/common/harmonictype.cpp \
    src/controller/ChartDrawerController.cpp \
    src/model/Harmonic.cpp \
    src/model/HarmonicsStorage.cpp \
    src/view/chartdrawerview.cpp \
    src/view/chartgraphicview.cpp \
    src/view/createnewharmonicview.cpp \
    src/view/harmoniceditor.cpp \
    src/view/harmoniclist.cpp \
    src/view/harmoniclistitem.cpp

HEADERS += \
    src/common/harmonicdto.h \
    src/common/harmonictype.h \
    src/controller/ChartDrawerController.h \
    src/controller/ChartDrawerControllerInterface.h \
    src/controller/HarmonicEditorControllerInterface.h \
    src/model/EditedHarmonicInterface.h \
    src/model/Harmonic.h \
    src/model/HarmonicInterface.h \
    src/model/HarmonicsStorage.h \
    src/model/HarmonicsStorageInterface.h \
    src/view/chartdrawerview.h \
    src/view/chartgraphicview.h \
    src/view/createnewharmonicview.h \
    src/view/harmoniceditor.h \
    src/view/harmoniclist.h \
    src/view/harmoniclistitem.h

FORMS += \
    src/view/chartdrawerview.ui \
    src/view/createnewharmonicview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
