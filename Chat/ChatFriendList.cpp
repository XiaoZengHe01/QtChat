#include "ChatFriendList.h"


ChatFriendList::ChatFriendList(QWidget* Parent):QFrame(Parent)
{
    this->Initialize();

    //搜索框
    QLineEdit* EditSearch;
    //搜索按钮
    QPushButton* ButSearch;


    QVBoxLayout* VL(new QVBoxLayout);
    QHBoxLayout* HL(new QHBoxLayout);
    HL->addWidget(EditSearch=new QLineEdit,2);
    HL->addWidget(ButSearch=new QPushButton(""));
    VL->addLayout(HL);
    VL->addWidget(this->_DataView=new QListView);
    this->setLayout(VL);

    //禁止编辑
    this->_DataView->setEditTriggers(QListView::EditTrigger::NoEditTriggers);
    //连接信号和槽
#if 0
    connect(this->_DataView,
            &QListView::doubleClicked,
            [=](const QModelIndex& MI){
        if(nullptr!=this->_ChatDig)
        {
            this->_ChatDig->ReadyChat(MI);
        }
        qDebug()<<MI.row();
    });
#endif
}


void ChatFriendList::Initialize()
{

    this->_ChatDig=nullptr;
    this->setStyleSheet("QFrame{border:0px;background-color:#F0F0F0;}");
}


void ChatFriendList::SetViewModel(QAbstractItemModel* ViewModel)
{

    if(nullptr!=ViewModel)
    {

        this->_DataView->setModel(ViewModel);
        this->_DataView->setModelColumn(2);
    }
}


void ChatFriendList::SetChatDialog(ChatDialog* ChatDig)
{

    connect(this->_DataView,
            &QListView::doubleClicked,
            [=](const QModelIndex& MI){
         ChatDig->ReadyChat(MI);
    });

}


void ChatFriendList::Correlactoin(ChatMessage* ChatMes)
{

    connect(this->_DataView,
            &QListView::doubleClicked,
            [=](const QModelIndex& MI){
            ChatMes->ReadyChat(MI);

    });
}

