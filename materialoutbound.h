#ifndef MATERIALOUTBOUND_H
#define MATERIALOUTBOUND_H

#include <QWidget>
#include <QSqlTableModel>
#include <QDebug>
#include <QStringList>
#include <QMessageBox>
#include <QButtonGroup>
#include <QScrollArea>
#include <QItemDelegate>


namespace Ui {
class MaterialOutbound;
class ReadOnly;

}
//QItemDelegate 是Readonly的子类
class ReadOnly:public QItemDelegate
{
public:
    ReadOnly(QObject *parent =0);
    ~ReadOnly();
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;
};

class MaterialOutbound : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialOutbound(QWidget *parent = 0);
    ~MaterialOutbound();
private:
    Ui::MaterialOutbound *ui;
    //使用sql模型
    QSqlTableModel *model,*_model;
    QButtonGroup *buttongroup;
    int judge;
private slots:
    void searchbtnSlot();
    void comeMaterialManage();
    void returnbtnSlot();
    void submitSlot();
    void inputeditSlot(QString);
    void buttongroupSlot(int);
signals:
    void EmitToWarehouseManage();
    void EmitToWarehouseManageToModifyStack();
};
#endif // MATERIALOUTBOUND_H
