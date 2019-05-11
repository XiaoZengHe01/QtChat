#ifndef CHATFRIENDLIST_H
#define CHATFRIENDLIST_H

#include <QListView>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDebug>
#include <QPushButton>

#include "../ChatDialog/ChatDialog.h"
#include "ChatMessage.h"

class ChatFriendList:public QFrame
{
public:
    ChatFriendList(QWidget* Parent=nullptr);
    //设置模型
    void SetViewModel(QAbstractItemModel* ViewModel);
    void SetChatDialog(ChatDialog* ChatDig);
    void Correlactoin(ChatMessage* ChatMes);
private:
    //初始化当前窗体
    void Initialize();
    //用来显示好友列表
    QListView* _DataView;
    //聊天窗体
    ChatDialog* _ChatDig;

};

#endif // CHATFRIENDLIST_H
