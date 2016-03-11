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
    c_nft_libr.cpp \
    c_nfh_libr.cpp \
    c_nfv_libr.cpp \
    c_nfx_libr.cpp \
    c_nfq_libr.cpp

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
    c_nft_libr.h \
    c_nfh_libr.h \
    c_nfv_libr.h \
    c_nfx_libr.h \
    c_nfq_libr.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES += \
    exports.def

CoolPropIncludes = C:/Users/nfette/Documents/GitHub/CoolProp/externals/Eigen \
    C:/Users/nfette/Documents/GitHub/CoolProp/externals/REFPROP-headers \
    C:/Users/nfette/Documents/GitHub/CoolProp/externals/msgpack-c/include \
    C:/Users/nfette/Documents/GitHub/CoolProp/externals/IF97 \
    C:/Users/nfette/Documents/GitHub/CoolProp/include \
    C:/Users/nfette/Documents/GitHub/CoolProp/include/rapidjson/rapidjson \
    C:/Users/nfette/Documents/GitHub/CoolProp/include/rapidjson/rapidjson/internal \
    C:/Users/nfette/Documents/GitHub/CoolProp/include/rapidjson \
    C:/Users/nfette/Documents/GitHub/CoolProp/src/Backends/Helmholtz \
    C:/Users/nfette/Documents/GitHub/CoolProp/src/Backends/Helmholtz/Fluids \
    C:/Users/nfette/Documents/GitHub/CoolProp/src/Backends/IF97 \
    C:/Users/nfette/Documents/GitHub/CoolProp/src/Backends/Incompressible \
    C:/Users/nfette/Documents/GitHub/CoolProp/src/Backends/REFPROP \
    C:/Users/nfette/Documents/GitHub/CoolProp/src/Backends/Tabular \
    C:/Users/nfette/Documents/GitHub/CoolProp/src/l10n

INCLUDEPATH += $${CoolPropIncludes} \
    C:/installs/boost/boost_1_58_0 #\
    #C:/Python27/include \
    #$$(HOMEPATH)/Documents/GitHub/openACHP/src/cython

DEPENDPATH += $${CoolPropIncludes}

# Visual studio

LIBS += -L$$(HOMEPATH)"/Documents/GitHub/CoolProp/build/Release" -lCoolProp #\
    #-L"C:/Program Files (x86)/REFPROP" -lrefprop \
    #-L"C:/Python27/libs" -lpython27 \
    #-L$$(HOMEPATH)"/Documents/GitHub/openACHP/src/cython/build/temp.win32-2.7/Release" -lhelloworld

QMAKE_LFLAGS += /DEF:$$(HOMEPATH)\Documents\scratch\qt\nf_EES_lib1\exports.def

# MinGW
#LIBS += $$(HOMEPATH)\Documents\scratch\qt\nf_EES_lib1\exports.def \
#    -LC:\Qt\Qt5.4.2\Tools\mingw491_32\i686-w64-mingw32\lib -lmingw32 \
#    \ #-L"C:/Program Files (x86)/REFPROP" -lrefprop \
#    -L$$(HOMEPATH)"/Documents/GitHub/CoolProp/buildmingw" -lCoolProp \
#    -LC:/Python27/libs -lpython27 \
#    \ #-LC:/Windows/SysWOW64 -lpython27 \
#    -L$$(HOMEPATH)"/Documents/GitHub/openACHP/src/cython/build/lib.win32-2.7" -lhelloworld

# If you are curious:
#QMAKE_LFLAGS += -Xlinker --output-def=show_me_the_symbols.DEF
# Omit the linker warnings about resolving symbols in the export file.
#QMAKE_LFLAGS += -Xlinker --enable-stdcall-fixup

