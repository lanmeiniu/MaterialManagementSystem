#ifndef MATERIALSTORAGE_H
#define MATERIALSTORAGE_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlRecord>


namespace Ui {
class MaterialStorage;
}

class MaterialStorage : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialStorage(QWidget *parent = 0);
    ~MaterialStorage();
    bool judgeEmpty();
    void clearAll();
private:
    Ui::MaterialStorage *ui;
    QSqlTableModel *model;
private slots:
    void returnbtnSlot();
    void confirmbtnSlot();
signals:
    void EmitToWarehouseManage();
};

#endif // MATERIALSTORAGE_H
