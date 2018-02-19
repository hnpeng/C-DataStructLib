TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

include(SeqList/SeqList.pri)
include(TestCase/TestCase.pri)
include(LinkList/LinkList.pri)
include(StaticList/StaticList.pri)
include(CircleList/CircleList.pri)

SOURCES += main.c

HEADERS +=

# DEPENDPATH += SeqList

# INCLUDEPATH += SeqList
