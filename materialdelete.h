#ifndef MATERIALDELETE_H
#define MATERIALDELETE_H

#include <QWidget>
#include <QDebug>
#include <QSqlTableModel>
#include <QMessageBox>


namespace Ui {
class MaterialDelete;
}

class MaterialDelete : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialDelete(QWidget *parent = 0);
    ~MaterialDelete();

private:
    Ui::MaterialDelete *ui;
    QSqlTableModel *model;
private slots:
    void deletebtnSlot();
    void returnbtnSlot();
    void comeMaterialManage();

signals:
    void EmitToWarehouseManage();
};

#endif // MATERIALDELETE_H
