#-------------------------------------------------
#
# Project created by QtCreator 2017-04-20T13:46:19
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MaterialManagementSystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    register.cpp \
    login.cpp \
    WarehouseManage.cpp \
    InventoryManage.cpp \
    materialinquiry.cpp \
    materialmodify.cpp \
    materialstorage.cpp \
    materialoutbound.cpp \
    materialdelete.cpp \
    warehousepassword.cpp \
    inventorylist.cpp \
    inquirymaterialoutbound.cpp \
    inventorypassword.cpp \
    inventoryinquiry.cpp

HEADERS  += \
    register.h \
    login.h \
    WarehouseManage.h \
    InventoryManage.h \
    materialinquiry.h \
    materialmodify.h \
    materialstorage.h \
    materialoutbound.h \
    materialdelete.h \
    warehousepassword.h \
    inventorylist.h \
    inquirymaterialoutbound.h \
    inventorypassword.h \
    inventoryinquiry.h

FORMS    += \
    register.ui \
    login.ui \
    WarehouseManage.ui \
    InventoryManage.ui \
    materialinquiry.ui \
    materialmodify.ui \
    materialstorage.ui \
    materialoutbound.ui \
    materialdelete.ui \
    warehousepassword.ui \
    inventorylist.ui \
    inquirymaterialoutbound.ui \
    inventorypassword.ui \
    inventoryinquiry.ui
TRANSLATIONS +=Resource/mms.ts

RESOURCES +=  Resource/reasource.qrc\
    Resource/reasource.qrc \
    Resource/ico.qrc

RC_FILE = my.rc

