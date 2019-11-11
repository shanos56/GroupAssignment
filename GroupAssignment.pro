#-------------------------------------------------
#
# Project created by QtCreator 2019-10-16T13:30:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GroupAssignment
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

SOURCES += \
        abstractassetregister.cpp \
        abstractentityfactory.cpp \
        asset.cpp \
        assetform.cpp \
        assetregister.cpp \
        assettype.cpp \
        assettypeform.cpp \
        commonentityfactory.cpp \
        concretevalidators.cpp \
        custodian.cpp \
        custodianform.cpp \
        formstatushandler.cpp \
        loadfile.cpp \
        login.cpp \
        main.cpp \
        mainwindow.cpp \
        registeredentity.cpp \
        tester.cpp \
        typeduserproperty.cpp \
        userproperty.cpp \
        userpropertydefinition.cpp \
        userpropertyform.cpp \
        userpropertyvalidator.cpp

HEADERS += \
        abstractassetregister.h \
        abstractentityfactory.h \
        asset.h \
        assetform.h \
        assetregister.h \
        assettype.h \
        assettypeform.h \
        commonentityfactory.h \
        concretevalidators.h \
        custodian.h \
        custodianform.h \
        formstatus.h \
        formstatushandler.h \
        loadfile.h \
        login.h \
        mainwindow.h \
        registeredentity.h \
        tester.h \
        typeduserproperty.h \
        userproperty.h \
        userpropertydefinition.h \
        userpropertyform.h \
        userpropertyvalidator.h

FORMS += \
        assetform.ui \
        assettypeform.ui \
        custodianform.ui \
        loadfile.ui \
        login.ui \
        mainwindow.ui \
        userpropertyform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Mainwindow.qml \
    MainwindowForm.ui.qml
