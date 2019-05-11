#include <QApplication>
#include "ChatNetwork.h"



int main(int Argc,char** Argv)
{
    QApplication App(Argc,Argv);

    QSqlDatabase FriendData=QSqlDatabase::addDatabase("QSQLITE");
    FriendData.setDatabaseName("FriendData.db");

    //数据库表格模型
    QSqlTableModel* DataModel(new QSqlTableModel);
    //设置表格
    DataModel->setTable("FriendInfo");
    //选择
    DataModel->select();

    ChatNetwork Net(*DataModel);
    return App.exec();
}
