#-------------------------------------------------
#


#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab2_client
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    dataoperationssl.cpp


HEADERS  += dialog.h \
    dataoperationssl.h
    #../ssl/DataOperationSSL.h


INCLUDEPATH += /usr/local/Cellar/openssl/1.0.2o_2/include

LIBS += /usr/local/Cellar/openssl/1.0.2o_2/lib/libcrypto.1.0.0.dylib \
        /usr/local/Cellar/openssl/1.0.2o_2/lib/libssl.1.0.0.dylib




FORMS    += dialog.ui




