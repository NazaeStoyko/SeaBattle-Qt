QT       += core gui sql
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    board.cpp \
    choose.cpp \
    coordinate.cpp \
    dbmanager.cpp \
    field.cpp \
    form.cpp \
    getdata.cpp \
    images.cpp \
    main.cpp \
    mainwindow.cpp \
    player.cpp \
    sqlitedbmanager.cpp

HEADERS += \
    board.h \
    choose.h \
    coordinate.h \
    dbmanager.h \
    field.h \
    form.h \
    getdata.h \
    images.h \
    mainwindow.h \
    player.h \
    sqlitedbmanager.h

FORMS += \
    choose.ui \
    form.ui \
    getdata.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

