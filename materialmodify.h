#ifndef MATERIALMODIFY_H
#define MATERIALMODIFY_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlRecord>

namespace Ui {
class MaterialModify;
}

class MaterialModify : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialModify(QWidget *parent = 0);
    ~MaterialModify();

private:
    Ui::MaterialModify *ui;
    QSqlTableModel *model;
    int judge;
private slots:
    void comeWarehouseManage();
    void confirmbtnSlot();
    void returnbtnSlot();
    void judgeSlot(QModelIndex,QModelIndex);
signals:
    void EmitToWarehouseManage();
    void EmitToWarehouseManageToModifyStack();
};

#endif // MATERIALMODIFY_H
