#-------------------------------------------------
#
# Project created by QtCreator 2015-05-27T10:43:46
#
#-------------------------------------------------

QT       -= gui core

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
    c_nfpcrit.cpp \
    c_nfp_libr.cpp \
    c_nfpyadd.cpp \
    c_nft_libr.cpp

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
    c_nfpcrit.h \
    c_nfp_libr.h \
    c_nfpyadd.h \
    c_nft_libr.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += $$(HOMEPATH)/Documents/GitHub/CoolProp/include \
    C:/Python27/include \
    C:/installs/boost/boost_1_58_0

LIBS += -L"C:/Program Files (x86)/REFPROP" -lrefprop \
    -L$$(HOMEPATH)"/Documents/GitHub/CoolProp/build/Release" -lCoolProp \
    -L"C:/Python27/libs" -lpython27

OTHER_FILES += \
    exports.def

#QMAKE_CFLAGS += /Gr
#QMAKE_CXXFLAGS += /Gr
QMAKE_LFLAGS += /DEF:$$(HOMEPATH)\Documents\scratch\qt\nf_EES_lib1\exports.def
