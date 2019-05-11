#ifndef CHATNETWORK_H
#define CHATNETWORK_H

#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>
#include <QUdpSocket>
#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextBrowser>
#include <QObject>
#include <QSqlTableModel>
#include <QSqlRecord>


class ChatNetwork:public QObject
{

    Q_OBJECT
public:

    ChatNetwork(QSqlTableModel& TableModel,QObject* Parent=nullptr);

    //UDP 套接字
    QUdpSocket* _UdpSocket;
    //TCP 套接字
    QTcpSocket* _TcpSocket;
    //TCP 服务器
    QTcpServer* _TcpServer;
    QByteArray MesBuf;
#if 1
    QDialog* _MesDialog;
    QTextBrowser* _MesBrowser;
    QLineEdit* _EditMes;

public:

#endif
public:
    void Login();
private:
    //初始化网络资源
    void InitializeNet();
    //初始化UI
    void InitializeUI();

private:
    QSqlTableModel* _DataModel;
signals:

public slots:
    //读取报文
    void SlotUdpReadyRead();
    //接收新的连接
    void SlotNewConnection();
    //读取TCP的传来的数据
    void SlotTcpReadyRead();
};

#endif // CHATNETWORK_H
