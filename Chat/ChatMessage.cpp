#include "ChatMessage.h"
#include <QDirModel>


ChatMessage::ChatMessage(QWidget* Parent):QFrame (Parent)
{

    this->Initialize();

    QVBoxLayout* VL(new QVBoxLayout);
    VL->addWidget(this->_DataView=new QListView);
    this->setLayout(VL);




}

void ChatMessage::Initialize()
{
     this->setStyleSheet("QFrame{border:0px;background-color:#F0F0F0;}");
}



void ChatMessage::SetViewModel(QAbstractItemModel* ViewModel)
{

    if(nullptr!=ViewModel)
    {

        this->_DataView->setModel(ViewModel);
        this->_DataView->setModelColumn(2);
        //隐藏所有的值
        for(int i(0);i<ViewModel->rowCount();i++)
        {
            this->_DataView->setRowHidden(i,true);
        }

    }
}


//进入聊天状态
void ChatMessage::ReadyChat(const QModelIndex& MIndex)
{
    this->_DataView->setRowHidden(MIndex.row(),false);
}
