#-------------------------------------------------
#
# Project created by QtCreator 2017-07-20T15:44:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fm
TEMPLATE = app

#QMAKE_CFLAGS += -std=c99

SOURCES += main.cpp\
        mainwindow.cpp \
#    debug_frmwrk.c \
 #   IO.c \
    AmpTDF8546.cpp \
    Audio_Func.cpp \
    Audio_Proc.cpp \
    Display.cpp \
    eeprom.cpp \
    I2C.cpp \
    key.cpp \
    Lcd.cpp \
    LcdDrv.cpp \
    RTC.cpp \
    system.cpp \
    timer.cpp \
    Tuner_Api.cpp \
    Tuner_Api_Lithio.cpp \
    Tuner_Boot_Lithio.cpp \
    Tuner_Drv_Lithio.cpp \
    Tuner_Proc.cpp
#    Uart.c

HEADERS  += mainwindow.h \
    AmpTDF8546.h \
    Audio_Func.h \
    Audio_Proc.h \
#    debug_frmwrk.h \
    Display.h \
    EEPRom.h \
    I2C.h \
#    IO.h \
    key.h \
    Lcd.h \
    LcdDrv.h \
#    LPC17xx_UM.h \
    NxTypes.h \
    public.h \
    RTC.h \
    system.h \
    timer.h \
    Tuner_Api_Lithio.h \
    Tuner_Api.h \
    Tuner_Boot_Lithio.h \
    Tuner_Drv_Lithio.h \
    Tuner_Patch_Lithio_V101_p116.h \
    Tuner_Patch_Lithio_V101_p119.h \
    Tuner_Patch_Lithio_V102_p209.h \
    Tuner_Patch_Lithio_V102_p212.h \
    Tuner_Patch_Lithio_V102_p213.h \
    Tuner_Proc.h \
    Typedef.h
#    Uart.h

FORMS    += mainwindow.ui

#DISTFILES += \
#    startup_LPC17xx.s

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
