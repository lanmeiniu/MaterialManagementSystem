#ifndef LOGIN_H
#define LOGIN_H

#include "register.h"
#include "InventoryManage.h"
#include "WarehouseManage.h"

#include <QDialog>
#include <QDebug>
#include <QPalette>
#include <QButtonGroup>
#include <QMessageBox>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    void clearAll();
    bool judgeEmpty();
private:
    Ui::Login *ui;
    QButtonGroup *radiogroup;
    QSqlTableModel *model;
    WarehouseManage *warehouse;
    InventoryManage *inventory;
signals:
    void toWarehouseManage(QString,QString);
    void toInventoryManage(QString,QString);
private slots:
    void registerbtnSlot();
    void exitbtnSlot();
    void loginbtnSlot();
    void loginbtnSetSlot(QString);
};

#endif // LOGIN_H
