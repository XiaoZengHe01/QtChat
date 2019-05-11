#ifndef CHATMAINDIALG
#define CHATMAINDIALG

#include <QDialog>
#include <QVBoxLayout>
#include <QComboBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextBrowser>
#include <QTextEdit>
#include <QFrame>
#include <QFileDialog>
#include <QStringList>
#include <QString>
#include <QDebug>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QUrl>
#include <QMessageBox>
#include <QListWidget>
#include <QCloseEvent>
#include <QFileInfo>


class ChatMainDialg : public QWidget
{
    Q_OBJECT
public:
    ChatMainDialg(QWidget* Parent=nullptr);


    enum MES_TYPE
    {
        PHOTO,
        FILE
    }_MessType;

public:

private:


private:
    //用来显示消息
    QTextBrowser* _TxtBrowser;

    //选择工具的下拉选项
    QComboBox* _ComTool;

    //显示后台任务
    QListWidget* _BackTask;
    //用来编辑消息
    QTextEdit* _TxtEdit;
    //用来显示图片
    QLabel* _Label;
    QPixmap _Img;

    QGraphicsView* _ImgView;
    QGraphicsScene* _ImgScene;

    QLabel* _ShowSharedScreen;
    void SheardScreen();

public slots:
    //选择表情
    void SeleceFace(bool);
    //选择图片
    void SeleceImage(bool);
    //选择文件
    void SelectFile(bool);
    //发送消息
    void SendMess(bool);
    //选择工具
    void SeleceTool(int Index);

};

#endif // CHATMAINDIALG
