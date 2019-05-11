#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H


#include <QListWidget>
#include <QStringList>
#include <QTreeWidgetItem>
#include <QListWidgetItem>
#include <QLabel>
#include <QModelIndex>
#include <QDebug>
#include <QMap>
#include <QListView>
#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSqlRecord>

class ChatMessage:public QFrame
{
public:
    ChatMessage(QWidget *Parent = nullptr);
    //设置模型
    void SetViewModel(QAbstractItemModel* ViewModel);
private:

private:
    //初始化当前窗体
    void Initialize();
    QListView* _DataView;
public slots:
    void ReadyChat(const QModelIndex& MIndex);
};

#endif // CHATMESSAGE_H
