#-------------------------------------------------
#
# Project created by QtCreator 2018-12-16T19:42:32
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI_Genomics
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        ../src/BEDreader.cpp\
        ../src/fastareader.cpp\
        ../src/FastaWriter.cpp\
        ../src/LinksFile.cpp\
        ../src/Matrice.cpp\
        ../src/MatrixReader.cpp\
        ../src/MatrixWriter.cpp\
        ../src/TxtWriter.cpp\
        ../src/Writer.cpp

HEADERS  += mainwindow.h\
        ../src/BEDreader.h\
        ../src/fastareader.h\
        ../src/FastaWriter.h\
        ../src/LinksFile.h\
        ../src/Matrice.h\
        ../src/MatrixReader.h\
        ../src/MatrixWriter.h\
        ../src/TxtWriter.h\
        ../src/Writer.h

FORMS    += mainwindow.ui

RESOURCES += \
    genomics.qrc

DISTFILES += \
    tabs.png
