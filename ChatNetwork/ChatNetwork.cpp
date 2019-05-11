#include "ChatNetwork.h"

ChatNetwork::ChatNetwork(QSqlTableModel& TableModel,QObject* Parent):QObject (Parent)
{

    this->_DataModel=&TableModel;
    //初始化UI
    this->InitializeUI();
    //初始化网络资源
    this->InitializeNet();
    this->Login();

#if 0
    QSqlRecord Recprd;
    Recprd=TableModel.record();
    Recprd.setValue("IPAddress","192.168.11.230");
    Recprd.setValue("Port","1942");
    Recprd.setValue("UserName","Google");
    Recprd.setValue("PixPath","C:/Google.png");
    TableModel.insertRecord(-1,Recprd);
    TableModel.submitAll();
#endif

#if 0
    for(int i=0;i<this->_DataModel->columnCount();i++)
    {
        for(int j=0;j<this->_DataModel->record(i).count();j++)
        {
            qDebug()<<this->_DataModel->record(i).value(j);
        }
    }
#endif



}


void ChatNetwork::InitializeNet()
{
    //创建UDP套接字
    this->_UdpSocket=new QUdpSocket(this);
    //绑定IP和端口
    this->_UdpSocket->bind(QHostAddress::AnyIPv4,8848);
    //准备读取报文
    connect(this->_UdpSocket,
            SIGNAL(readyRead()),
            this,SLOT(SlotUdpReadyRead()));


    //创建TCP服务器
    this->_TcpServer=new QTcpServer(this);
    //监听IP和端口
    this->_TcpServer->listen(QHostAddress("192.168.11.219"),8848);
    //接收新的连接
    connect(this->_TcpServer,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
    //创建服务器套接字
    this->_TcpSocket=new QTcpSocket(this);
    //连接到服务器
    this->_TcpSocket->connectToHost(QHostAddress("192.168.11.218"),8848);

    connect(this->_TcpSocket,&QTcpSocket::connected,[](){
        qDebug()<<"Connection successed";
    });

}
//初始化UI
void ChatNetwork::InitializeUI()
{
    this->_MesDialog=new QDialog;
    QVBoxLayout* VL(new QVBoxLayout);
    VL->addWidget(this->_MesBrowser=new QTextBrowser);
    VL->addWidget(this->_EditMes=new QLineEdit);

    this->_MesDialog->setLayout(VL);
    this->_MesDialog->show();

    //测试UDP
#if 1
    connect(this->_EditMes,&QLineEdit::returnPressed,[=](){
        this->_UdpSocket->writeDatagram(this->_EditMes->text().toUtf8(),
                                        QHostAddress("192.168.11.218"),
                                        8848);
        this->_MesBrowser->append("Lenovo:"+this->_EditMes->text());
        this->_EditMes->clear();
    });
#endif

    //测试TCP
#if 0
    connect(this->_EditMes,&QLineEdit::returnPressed,[=](){


        this->_TcpSocket->write(this->_EditMes->text().toUtf8());
        this->_MesBrowser->append("Lenovo: "+this->_EditMes->text());
        this->_EditMes->clear();
    });
#endif
}

//读取报文
void ChatNetwork::SlotUdpReadyRead()
{
    while(this->_UdpSocket->hasPendingDatagrams())
    {
        qint64 DgramSize(this->_UdpSocket->pendingDatagramSize());
        QByteArray DgramByte(static_cast<int>(DgramSize),0);
        this->_UdpSocket->readDatagram(DgramByte.data(),DgramSize);
        this->_MesBrowser->append(MesBuf.data()+2);

    }
}

//接收新的连接
void ChatNetwork::SlotNewConnection()
{
    qDebug()<<"New connection";
    while(this->_TcpServer->hasPendingConnections())
    {
        this->_TcpSocket=this->_TcpServer->nextPendingConnection();
        //准备读取数据
        connect(this->_TcpSocket,SIGNAL(readyRead()),this,SLOT(SlotTcpReadyRead()));
    }
}

//读取TCP的传来的数据
void ChatNetwork::SlotTcpReadyRead()
{
    qDebug()<<"New message";
    while(this->_TcpSocket->bytesAvailable())
    {
        QByteArray MesByte=this->_TcpSocket->readAll();
        this->_MesBrowser->append(MesByte);
    }
}

void ChatNetwork::Login()
{
    MesBuf.clear();
    MesBuf[0]='L';
    MesBuf+="asdasda";
    this->_UdpSocket->writeDatagram(MesBuf,
                                    QHostAddress::Broadcast,
                                    8848);
}



