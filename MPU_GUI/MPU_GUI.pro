QT += widgets serialport printsupport
requires(qtConfig(combobox))

TARGET = MPU_GUI
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    settingsdialog.cpp \
    console.cpp \
    geometryengine.cpp \
    viz3D.cpp

HEADERS += \
    mainwindow.h \
    qcustomplot.h \
    settingsdialog.h \
    console.h \
    geometryengine.h \
    viz3D.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui

RESOURCES += \
    terminal.qrc \
    shaders.qrc \
    textures.qrc

target.path = /tmp/$${TARGET}/bin
INSTALLS += target

CONFIG += c++17
