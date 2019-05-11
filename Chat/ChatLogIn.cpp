#include "ChatLogIn.h"
#include <QSettings>



ChatLogIn::ChatLogIn(QWidget *parent) : QWidget(parent)
{

    this->setPalette(QPalette(Qt::white));

    this->resize(800,480);
    QComboBox* IPAddress;
    QComboBox* Port;
    QPushButton* BtLog;
    QPushButton* BtQuit;
    QLabel* LAddr;
    QLabel* LPort;

    QGridLayout* GLayout(new QGridLayout(this));
    GLayout->addWidget(LAddr=new QLabel(tr("IPAddress")),1,1);
    GLayout->addWidget(IPAddress=new QComboBox,1,2);

    GLayout->addWidget(LPort=new QLabel(tr("Port")),2,1);
    GLayout->addWidget(Port=new QComboBox,2,2);
    Port->setEditable(true);

    GLayout->addWidget(BtLog=new QPushButton(tr("Login")),3,1,1,2);
    GLayout->addWidget(BtQuit=new QPushButton(tr("Quit")),6,6);

    GLayout->setRowStretch(0,1);
    GLayout->setRowStretch(4,1);
    GLayout->setColumnStretch(0,2);
    GLayout->setColumnStretch(5,1);

    QList<QHostAddress> AddrList(QNetworkInterface::allAddresses());
    foreach(QHostAddress Addr,AddrList)
    {
        if(Addr.toIPv4Address())
        {
            IPAddress->addItem(QHostAddress(Addr.toIPv4Address()).toString());
        }
    }

    Port->addItem("8848");
    IPAddress->setStyleSheet("QComboBox{width:256px;height:30px;font-size:16px;}");
    Port->setStyleSheet("QComboBox{width:256px;height:30px;font-size:16px;}");
    BtLog->setStyleSheet("QPushButton{width:240px;height:30px;font-size:16px;}");
    LAddr->setStyleSheet("QLabel{font-size:16px;}");
    LPort->setStyleSheet("QLabel{font-size:16px;}");

#if 1

    connect(BtLog,&QPushButton::clicked,[=](bool){

        //Qt中使用QSettings类读写ini文件
        //QSettings构造函数的第一个参数是ini文件的路径,第二个参数表示针对ini文件,第三个参数可以缺省
        QSettings *configIniWrite = new QSettings("Network.ini", QSettings::IniFormat);
        //向ini文件中写入内容,setValue函数的两个参数是键值对
        //向ini文件的第一个节写入内容,ip节下的第一个参数
        qDebug()<<IPAddress->currentText();
        configIniWrite->setValue("/Network/IPAddress",IPAddress->currentText());

        //向ini文件的第二个节写入内容,port节下的第一个参数
        configIniWrite->setValue("Network/Port", Port->currentText());

        //写入完成后删除指针
        delete configIniWrite;
    });


#endif


}


