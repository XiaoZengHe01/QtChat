#include "ChatDialog.h"

#include <QModelIndex>
#include <QSqlRecord>

ChatDialog::ChatDialog(QWidget* Parent):QDialog (Parent)
{

    this->resize(800,600);

    QHBoxLayout* HB(new QHBoxLayout);
    QVBoxLayout* VLA(new QVBoxLayout);
    VLA->addWidget(this->_MesList=new QListView);
    HB->addLayout(VLA);

    //添加堆栈窗体

    HB->addWidget(this->_StWidget=new QStackedWidget,1);


    this->setLayout(HB);

    //初始化视图和模型
    this->InitalizeVM();
}


void ChatDialog::SetViewModel(QAbstractItemModel* ViewModel)
{
    if(ViewModel!=nullptr)
    {
        this->_MesList->setModel(ViewModel);
    }
}


void ChatDialog::closeEvent(QCloseEvent* Ev)
{

    if(Ev->type()==QEvent::Close)
    {
        //隐藏所有的值
        for(int i(0);i<this->_TabData->rowCount();i++)
        {
            this->_MesList->setRowHidden(i,true);
        }


        //QMessageBox::warning(nullptr,"Close","Can't close!");
        //隐藏窗体
        this->hide();
        Ev->ignore();
        //  Ev->accept();
    }

}

//进入聊天状态
void ChatDialog::ReadyChat(const QModelIndex& MIndex)
{


    if(this->isHidden())
    {
        this->show();
    }

    QSqlRecord Record;
    //显示这一行的数据"MIndex.row()"
    this->_MesList->setRowHidden(MIndex.row(),false);
    //查阅这一行的数据“MIndex.row()”
    Record=this->_TabData->record(MIndex.row());
    //设置窗口标题
    this->setWindowTitle(Record.value(2).value<QString>());

    //映射一个聊天对话框
    MapChatDig.insert(0,new ChatMainDialg);
    //把聊天窗体加入到堆栈对话框
    this->_StWidget->insertWidget(MIndex.row(),new ChatMainDialg);
    if(this->_StWidget->isHidden())
    {
        this->_StWidget->show();
    }
    //切换对应的堆栈窗体
    if(this->_StWidget->currentIndex()!=MIndex.row())
    {
        this->_StWidget->setCurrentIndex(MIndex.row());
    }

}

//初始化视图和模型
void ChatDialog::InitalizeVM()
{

    //设置数据库模型
    this->_TabData=new QSqlTableModel(this);
    //设置数据框表格
    this->_TabData->setTable("FriendInfo");
    //选择数据库
    this->_TabData->select();

    //选择视图依赖的模型
    this->_MesList->setModel(this->_TabData);
    //选择要显示的的列
    this->_MesList->setModelColumn(2);

    //隐藏所有的值
    for(int i(0);i<this->_TabData->rowCount();i++)
    {
        this->_MesList->setRowHidden(i,true);
    }

    //尝试着显示一行
   // this->_MesList->setRowHidden(1,false);

    //设置为不可编辑
    this->_MesList->setEditTriggers(QAbstractItemView::NoEditTriggers);
#if 1
    //连接信号和槽，选中谁就和谁聊天
    connect(this->_MesList,
            SIGNAL(clicked(const QModelIndex&)),
            this,
            SLOT(ReadyChat(const QModelIndex&)));

#endif
}
