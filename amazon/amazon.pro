QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    astar.cpp \
    floor.cpp \
    main.cpp \
    mainwindow.cpp \
    package.cpp \
    robot.cpp \
    robotsupervisor.cpp \
    shelf.cpp \
    supervisor.cpp \
    tile.cpp

HEADERS += \
    floor.h \
    mainwindow.h \
    package.h \
    robot.h \
    robotsupervisor.h \
    shelf.h \
    supervisor.h \
    tile.h

FORMS += \
    floor.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/robot.png \
    images/shelf.png \
    images/tile.png

RESOURCES += \
    images.qrc
