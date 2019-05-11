#include "ChatMainWindow.h"

ChatMainWindow::ChatMainWindow(QWidget *parent) : QWidget(parent)
{

    this->setFixedSize(240,600);
    QVector<QPushButton*> Buts;
    Buts.append(new QPushButton("Messages"));
    Buts.append(new QPushButton("Contacts"));
    Buts.append(new QPushButton("Settings"));


    //堆栈窗体
    QStackedWidget* p;
    QHBoxLayout* HL(new QHBoxLayout);
    QVBoxLayout* VL(new QVBoxLayout);
    VL->addWidget(p=new QStackedWidget,600);


    //根据按钮来切换堆栈窗体
    for(int i(0);i<Buts.count();i++)
    {
        connect(Buts[i],&QPushButton::clicked,p,[=](){
            p->setCurrentIndex(i);
        });

        HL->addWidget(Buts[i]);
    }

    //消息列表
    ChatMessage* Message;

    //数据库表格模型
    QSqlTableModel* DataModel(new QSqlTableModel);
    //设置表格
    DataModel->setTable("FriendInfo");
    //选择
    DataModel->select();
    //好友列表
    ChatFriendList* Friend;

    VL->addStretch(1);
    p->addWidget(Message=new ChatMessage);
    p->addWidget(Friend=new ChatFriendList);
    p->addWidget(new QFrame);
    VL->addLayout(HL);
    this->setLayout(VL);


    //创建独立的聊天对话框
    this->_ChatDig=new ChatDialog;
    //设置聊天对话框
   // Friend->SetChatDialog(*this->_ChatDig);
    //设置聊天对话框
    Friend->SetViewModel(DataModel);
    //设置数据模型
    Message->SetViewModel(DataModel);

    Friend->Correlactoin(Message);
#if 1
    Friend->SetChatDialog(this->_ChatDig);
#endif
}

void ChatMainWindow::closeEvent(QCloseEvent* Ev)
{
    if(Ev->type()==QCloseEvent::Close)
    {

        //关闭聊天窗口
        if(nullptr!=this->_ChatDig)
        {
            this->_ChatDig->deleteLater();
        }
    }
}
