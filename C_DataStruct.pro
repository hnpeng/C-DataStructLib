TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

include(SeqList/SeqList.pri)
include(TestCase/TestCase.pri)
include(LinkList/LinkList.pri)
include(StaticList/StaticList.pri)
include(CircleList/CircleList.pri)
include(DLinkList/DLinkList.pri)
include(SeqStack/SeqStack.pri)
include(LinkStack/LinkStack.pri)
include(LittleAlgorithm/LittleAlgorithm.pri)

SOURCES += main.c

HEADERS +=

# DEPENDPATH += SeqList

# INCLUDEPATH += SeqList
