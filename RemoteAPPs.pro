QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    widget.cpp

HEADERS += \
    ui_dialog.h \
    widget.h

FORMS += \
    dialog.ui \
    widget.ui

# Default rules for deployment.
target.path = /usr/local/bin
library.path = /usr/local/lib
!isEmpty(target.path):
INSTALLS += target library



