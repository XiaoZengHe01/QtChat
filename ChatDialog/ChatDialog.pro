QT += widgets gui sql

SOURCES += \
   #main.cpp \
    ChatDialog.cpp \
    ChatMainDialg.cpp

HEADERS += \
    ChatDialog.h \
    ChatMainDialg.h


TARGET = ChatDialog
TEMPLATE = lib
CONFIG += staticlib
