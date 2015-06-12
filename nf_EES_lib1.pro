#-------------------------------------------------
#
# Project created by QtCreator 2015-05-27T10:43:46
#
#-------------------------------------------------

QT       -= gui

TARGET = nf_EES_lib1
TEMPLATE = lib

DEFINES += NF_EES_LIB1_LIBRARY

SOURCES += nf_ees_lib1.cpp \
    refproper.cpp \
    ees_common.cpp \
    c_nfadd.cpp \
    c_nftliq.cpp \
    c_nfsatmix.cpp \
    c_nfmixtherm.cpp \
    c_libr_props.cpp \
    c_nfpcrit.cpp

HEADERS += nf_ees_lib1.h\
        nf_ees_lib1_global.h \
    REFPROP2.H \
    refproper.h \
    ees_common.h \
    c_nfadd.h \
    c_nftliq.h \
    c_nfsatmix.h \
    c_nfmixtherm.h \
    c_libr_props.h \
    c_nfpcrit.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += "C:/Users/nfette/Documents/GitHub/CoolProp/include"

LIBS += -L"C:/Program Files (x86)/REFPROP" -lrefprop \
    -L"C:/Users/nfette/Documents/GitHub/CoolProp/build/Release" -lCoolProp

OTHER_FILES += \
    exports.def

#QMAKE_CFLAGS += /Gr
#QMAKE_CXXFLAGS += /Gr
QMAKE_LFLAGS += /DEF:C:\Users\nfette\Documents\scratch\qt\nf_EES_lib1\exports.def
