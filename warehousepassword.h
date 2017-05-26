#ifndef WAREHOUSEPASSWORD_H
#define WAREHOUSEPASSWORD_H

#include <QWidget>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QTime>
#include <QMessageBox>

namespace Ui {
class Warehousepassword;
}

class Warehousepassword : public QWidget
{
    Q_OBJECT

public:
    explicit Warehousepassword(QWidget *parent = 0);
    ~Warehousepassword();
    void setVerificationCode();
    void clearAll();
    bool judgeEmpty();
private:
    Ui::Warehousepassword *ui;
    QString warehousenumber;
    int verificationcode;
    QSqlTableModel *model;
private slots:
    void comeWarehouseManage(QString);
    void confirmbtnSlot();
    void returnbtnSlot();
signals:
    void EmitToWarehouseManage();
};

#endif // WAREHOUSEPASSWORD_H
