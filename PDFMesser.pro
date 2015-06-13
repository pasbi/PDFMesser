#-------------------------------------------------
#
# Project created by QtCreator 2015-06-12T21:20:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PDFMesser
TEMPLATE = app

unix {
LIBS += -L/usr/local/lib -lpoppler-qt5
}

win32 {
INCLUDEPATH += C:\Users\dev\Desktop\poppler\include
LIBS += -LC:\Users\dev\Desktop\poppler\lib -lpoppler-qt5
}



SOURCES += main.cpp\
        mainwindow.cpp \
    canvas.cpp

HEADERS  += mainwindow.h \
    canvas.h

FORMS    += mainwindow.ui
