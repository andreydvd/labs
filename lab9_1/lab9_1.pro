TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Functions.c \
        input.c \
        main.c \
        prev.c

HEADERS += \
    Functions.h \
    constants.h \
    format/format.h \
    input.h
