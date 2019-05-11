QT += widgets\
 gui\
 network\
sql

HEADERS += \
    ChatLogIn.h \
    ChatMainWindow.h \
    ChatMessage.h \
    ChatFriendList.h

SOURCES += \
    main.cpp \
    ChatLogIn.cpp \
    ChatMainWindow.cpp \
    ChatMessage.cpp \
    ChatFriendList.cpp

RESOURCES += \
    resources.qrc


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-ChatDialog-Desktop_Qt_5_11_2_MinGW_32bit-Debug/release/ -lChatDialog
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-ChatDialog-Desktop_Qt_5_11_2_MinGW_32bit-Debug/debug/ -lChatDialog
else:unix: LIBS += -L$$PWD/../build-ChatDialog-Desktop_Qt_5_11_2_MinGW_32bit-Debug/ -lChatDialog

INCLUDEPATH += $$PWD/../ChatDialog
DEPENDPATH += $$PWD/../ChatDialog
