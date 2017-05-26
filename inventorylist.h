#ifndef INVENTORYLIST_H
#define INVENTORYLIST_H

#include <QWidget>
#include <QSqlTableModel>
#include <QDebug>
#include <QStringList>
#include <QMessageBox>
#include <QButtonGroup>
#include <QItemDelegate>


namespace Ui {
class InventoryList;
class ReadOnlyDelegate;

}
class ReadOnlyDelegate : public QItemDelegate
{
public:
    ReadOnlyDelegate(QObject *parent = 0);
    ~ReadOnlyDelegate();
    //createEditor 是双击item后创建什么控件
    QWidget *createEditor(QWidget*parent, const QStyleOptionViewItem &option,
        const QModelIndex &index) const;

};

class InventoryList : public QWidget
{
    Q_OBJECT
public:
    explicit InventoryList(QWidget *parent = 0);
    ~InventoryList();  

private:
    Ui::InventoryList *ui;
    int judge;
    QSqlTableModel *model,*_model;
    QButtonGroup *buttongroup;

private slots:
    void searchbtnSlot();
    void comeMaterialManage();
    void returnbtnSlot();
    void inputeditSlot(QString);
    void buttongroupSlot(int);
    void submitSlot();
signals:
    void EmitToInventoryManage();
    void EmitToInventoryToListManage();
};


#endif // INVENTORYLIST_H
