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
include(RecursiveAlgorithm/RecursiveAlgorithm.pri)
include(SeqQueue/SeqQueue.pri)
include(LinkQueue/LinkQueue.pri)
include(SQueue/SQueue.pri)
include(SStack/SStack.pri) 
include(SortAlgorithm/SortAlgorithm.pri)
include(GTree/GTree.pri)
include(BTree/BTree.pri)
include(MGraph/MGraph.pri)
include(LGraph/LGraph.pri)
include(Search/Search.pri)
include(BSTree/BSTree.pri)
include(Hash/Hash.pri)

SOURCES += main.c

HEADERS +=

# DEPENDPATH += SeqList

# INCLUDEPATH += SeqList
