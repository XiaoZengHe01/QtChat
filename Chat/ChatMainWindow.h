#ifndef CHATMAINWINDOW_H
#define CHATMAINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QStackedWidget>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QSqlTableModel>
#include <QCloseEvent>
#include "ChatMessage.h"
#include "ChatFriendList.h"
#include "../ChatDialog/ChatDialog.h"


class ChatMainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ChatMainWindow(QWidget *parent = nullptr);

private:
    //用于聊天的对话框
    ChatDialog* _ChatDig;
    void closeEvent(QCloseEvent* Ev);
signals:

public slots:
};

#endif // CHATMAINWINDOW_H
