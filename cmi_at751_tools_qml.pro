QT += qml quick   serialport

CONFIG += c++11

SOURCES += main.cpp \
    port.cpp \
    main_ui.cpp \
    port_read_thread.cpp \
    port_write_thread.cpp \
    gpio.cpp \
    equipment.cpp \
    equipment_thread.cpp \
    gpio_thread.cpp \
    ping.cpp \
    protocol.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES +=

HEADERS += \
    QmlPort.h \
    main_ui.h \
    port_read_thread.h \
    port_write_thread.h \
    gpio.h \
    equipment.h \
    equipment_thread.h \
    gpio_thread.h \
    ping.h \
    protocol.h
