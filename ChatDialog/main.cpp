#include <QApplication>
#include <QSqlDatabase>

#include "ChatDialog.h"



int main(int Argc,char** Argv)
{
    QApplication App(Argc,Argv);
    QSqlDatabase Data=QSqlDatabase::addDatabase("QSQLITE");
    Data.setDatabaseName("FriendData.db");

    ChatDialog w;
    w.show();
    return App.exec();
}
