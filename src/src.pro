#-------------------------------------------------
#
# Project created by QtCreator 2018-10-07T17:32:35
#
#-------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT          += core gui
TEMPLATE    = app

CONFIG      += c++11

DESTDIR     = ../bin
MOC_DIR     = ../moc
RCC_DIR     = ../rcc
OBJECTS_DIR = ../obj
INCLUDEPATH = ../include
INCLUDEPATH += /usr/local/include
DEPENDPATH  += /usr/local/include

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES     += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


# Use deferent name to identify the debug and release version
CONFIG(debug, debug|release){
    TARGET  = CommentsToolsD
    LIBS    += -L$$PWD/lib
    macx: QMAKE_CFLAGS = -std=c++11 -stdlib=libc++
    macx: QMAKE_CXXFLAGS = -std=c++11 -stdlib=libc++
    macx: LIBS += -L/usr/local/lib/ -lboost_system -lboost_filesystem
}else{
    TARGET  = CommentsTools
    LIBS    += -L$$PWD/lib
    macx: QMAKE_CFLAGS = -std=c++11 -stdlib=libc++
    macx: QMAKE_CXXFLAGS = -std=c++11 -stdlib=libc++
    macx: LIBS += -L/usr/local/lib/ -lboost_system  -lboost_filesystem
}

SOURCES     += \
            main.cpp \
    SMainWindow.cpp \
    STypeDialog.cpp \
    SEntryList.cpp

HEADERS     += \
    SMainWindow.h \
    STypeDialog.h \
    SEntryList.h

FORMS       += \
    MainWindow.ui \
    STypeDialog.ui

RESOURCES += \
    resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

macx: ICON = comments.icns
win32: RC_ICONS = comments.ico

