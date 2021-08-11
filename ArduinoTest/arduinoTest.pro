QT += widgets serialport charts
requires(qtConfig(combobox))

TARGET = arduinoTest
TEMPLATE = app

SOURCES += \
    graph2d.cpp \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp \
    console.cpp \
    geometryengine.cpp \
    viz3D.cpp

HEADERS += \
    graph2d.h \
    mainwindow.h \
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