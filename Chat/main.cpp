#include <QApplication>
#include "ChatLogIn.h"
#include "ChatMainWindow.h"
#include <QSqlDatabase>
#include <QMessageBox>



int main(int Argc,char** Argv)
{


    QApplication App(Argc,Argv);
    //连接数据库
    QSqlDatabase FriendData=QSqlDatabase::addDatabase("QSQLITE");
    FriendData.setDatabaseName("FriendData.db");

#if 1
    ChatMainWindow w;
    w.show();
#endif

    return App.exec();
}



