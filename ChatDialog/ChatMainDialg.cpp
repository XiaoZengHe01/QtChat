#include "ChatMainDialg.h"


ChatMainDialg::ChatMainDialg(QWidget* Parent):QWidget (Parent)
{


    //选择表情的按钮
    QPushButton* ButFace;
    //选择图片的按钮
    QPushButton* ButPhoto;
    //选择文件的按钮
    QPushButton* ButFile;

    //发送消息的按钮
    QPushButton* ButSend;


    QHBoxLayout* AllLayout(new QHBoxLayout);
    QVBoxLayout* VLB(new QVBoxLayout);
    VLB->addWidget(this->_TxtBrowser=new QTextBrowser,2);
    VLB->addWidget(this->_TxtEdit=new QTextEdit,1);



    QHBoxLayout* HL_VLB(new QHBoxLayout);
    HL_VLB->addWidget(ButFace=new QPushButton("表情"));
    HL_VLB->addWidget(ButPhoto=new QPushButton("图片"));
    HL_VLB->addWidget(ButFile=new QPushButton("文件"));
    HL_VLB->addWidget(this->_ComTool=new QComboBox);
    HL_VLB->addSpacing(200);
    HL_VLB->addWidget(ButSend=new QPushButton("发送"));
    VLB->addLayout(HL_VLB);


    AllLayout->addLayout(VLB);
    AllLayout->addWidget(this->_BackTask=new QListWidget,2);
    this->setLayout(AllLayout);



    //用来显示图片的
    this->_Label=new QLabel;
    QHBoxLayout* ImgHL(new QHBoxLayout);
    ImgHL->addWidget(this->_ImgView=new QGraphicsView);
    this->_ImgScene=new QGraphicsScene;
    this->_Label->resize(800,600);
    this->_ImgView->setScene(this->_ImgScene);
    this->_Label->setLayout(ImgHL);

    //为选择表情的按钮连接限号和槽
    connect(ButFace,SIGNAL(clicked(bool)),this,SLOT(SeleceFace(bool)));

    //为图片选择的按钮连接信号和槽
    connect(ButPhoto,SIGNAL(clicked(bool)),
            this,
            SLOT(SeleceImage(bool)));

    //为选择文件的按钮连接信号和槽
    connect(ButFile,SIGNAL(clicked(bool)),this,SLOT(SelectFile(bool)));

    //为发送按钮连接信号和槽
    connect(ButSend,SIGNAL(clicked(bool)),
            this,
            SLOT(SendMess(bool)));

    //失能超链接打开功能
    this->_TxtBrowser->setOpenLinks(false);
    //为超链接标签连接信号和槽，用来显示图片
    connect(this->_TxtBrowser,&QTextBrowser::anchorClicked,[=](const QUrl& r){
        this->_Img.load(r.toString());
        this->_ImgScene->addPixmap(this->_Img);
        this->_Label->show();
    });

    this->_ComTool->addItem("更多");
    this->_ComTool->addItem("请求对方桌面共享");
    this->_ComTool->addItem("截图工具");

    //为工具选择下拉选项连接信号和槽
    connect(this->_ComTool,SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(SeleceTool(int)));


}

void ChatMainDialg::SeleceFace(bool)
{
    QMessageBox::question(nullptr,"选择选择表情","请等待更新...");
}


//选择图片的槽函数
void ChatMainDialg::SeleceImage(bool)
{
    this->_MessType=ChatMainDialg::PHOTO;

    //这里保存着选择的所有图片路径
    QStringList PhotoNames=QFileDialog::getOpenFileNames(nullptr,"请选择图片",
                                                         QString(),
                                                         "image(*.jpg *.png);");

    for(auto i:PhotoNames)
    {
        //吧选择的所有图片添加到消息编辑框里
        this->_TxtEdit->append(QString("<a  href=%1><img src=%2 width=%3></img></a>").arg(i).arg(i).arg(this->_TxtEdit->width()/2));

    }
}


//选择文件
void ChatMainDialg::SelectFile(bool)
{

    //这里保存着所有的文件路径
    this->_MessType=ChatMainDialg::FILE;
    QStringList FileNames=QFileDialog::getOpenFileNames(nullptr,
                                                        "请选择图片",
                                                        QString(),
                                                        "所有文件(*.*);");

    for(auto i:FileNames)
    {

        this->_BackTask->addItem(QFileInfo(i).fileName());
        this->_TxtEdit->append(i);
    }
}

//发送按钮的槽函数
void ChatMainDialg::SendMess(bool)
{

    if(!this->_TxtEdit->toPlainText().isEmpty())
    {
        switch (this->_MessType) {
        case ChatMainDialg::PHOTO:
            //为了显示图片所有要"this->_TxtEdit->toHtml()"
            this->_TxtBrowser->append(this->_TxtEdit->toHtml());
            break;
        case ChatMainDialg::FILE:
            this->_TxtBrowser->append("发送文件："+this->_TxtEdit->toPlainText());
            break;
        default:
            this->_TxtBrowser->append(this->_TxtEdit->toPlainText());
            break;
        }
        this->_TxtEdit->clear();
    }
}

void ChatMainDialg::SeleceTool(int Index)
{

    qDebug()<<Index;
    switch(Index)
    {
    case 1:
        this->SheardScreen();
        break;
    case 2:
        break;
    default:
        break;
    }
    this->_ComTool->setCurrentIndex(0);
}

void ChatMainDialg::SheardScreen()
{

}
