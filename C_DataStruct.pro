TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

include(SeqList/SeqList.pri)
include(TestCase/TestCase.pri)
include(LinkList/LinkList.pri)

SOURCES += main.c

HEADERS +=

# DEPENDPATH += SeqList

# INCLUDEPATH += SeqList
