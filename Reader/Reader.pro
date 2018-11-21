QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Reader
TEMPLATE = app


SOURCES += main.cpp\
    NaviViewer.cpp \
    MainViewer.cpp \
    ChildViewer.cpp \
    Kit.cpp \
    DocViewer.cpp \
    PDFkit.cpp \
    ViewModel.cpp \
    ViewState.cpp \
    SingleContinuousState.cpp \
    DocWidget.cpp \
    ThumbnailWidget.cpp

HEADERS  += \
    PDFkit.h \
    NaviViewer.h \
    MainViewer.h \
    ChildViewer.h \
    Kit.h \
    DocViewer.h \
    MultiViewer.h \
    IChildViewer.h \
    ViewModel.h \
    IMainViewer.h \
    ViewState.h \
    SingleContinuousState.h \
    DocWidget.h \
    IDocWidget.h \
    ReadDefine.h \
    ThumbnailWidget.h

RESOURCES += \
    resource.qrc

INCLUDEPATH += $$PWD/3rdparty/ubuntu/Poppler/Include

unix: PKGCONFIG += poppler-qt5
unix: CONFIG += c++11 link_pkgconfig

DISTFILES +=
