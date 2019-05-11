#ifndef CHATDIALOG_H
#define CHATDIALOG_H


#include <QDialog>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QListWidget>
#include <QStackedWidget>
#include <QAbstractItemModel>
#include <QListView>
#include <QSqlTableModel>
#include <QDebug>
#include <QCloseEvent>
#include <QMenu>
#include <QCursor>
#include <QThread>
#include <QMap>
#include "ChatMainDialg.h"


class ChatDialog : public QDialog
{
    Q_OBJECT
public:
    ChatDialog(QWidget* Parent=nullptr);

private:
    //用来显示正在跟哪些好友聊天
    QListView* _MesList;
    QSqlTableModel* _TabData;
    //保存堆栈窗体
    QStackedWidget* _StWidget;
    //每个好友对应一个聊天窗口
    QMap<int,ChatMainDialg*> MapChatDig;

public:
    void SetViewModel(QAbstractItemModel* ViewModel);
private:
    //截取关闭信号
    void closeEvent(QCloseEvent* Ev);
    //初始化视图和模型
    void InitalizeVM();
public slots:
    //进入聊天状态
    void ReadyChat(const QModelIndex& MIndex);

};

#endif // CHATDIALOG_H
