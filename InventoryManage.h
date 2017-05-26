#ifndef INVENTORYMANAGE_H
#define INVENTORYMANAGE_H

#include <QWidget>
#include <QDebug>
#include <QPalette>
#include <QDateTime>
#include <QTimer>
#include "inventorypassword.h"
#include "inventoryinquiry.h"
#include "inventorylist.h"

namespace Ui {
class InventoryManage;
}

class InventoryManage : public QWidget
{
    Q_OBJECT

public:
    explicit InventoryManage(QWidget *parent = 0);
    ~InventoryManage();
    void btnsettrue();
    void btnsetfalse();
private slots:
    void comeLoginDialog(QString,QString);
    void settimeline();
    void passwordbtnSlot();
    void inquirybtnSlot();
    void inventorylistbtnSlot();
    void exitbtnSlot();
    void setbtnEnableSlot();
    void returnbtnSlot();
signals:
    void toInventorynumber(QString);
    void toInventoryinquiry();
    void toLoginDialog();
    void toInventoryCheck();
private:
    Ui::InventoryManage *ui;
    QString inventoryname,inventorynumber;
    QTimer *timelinetimer;
    Inventorypassword *inventorypassword;
    Inventoryinquiry *inventoryinquiry;
    InventoryList *inventorylist;
};

#endif // INVENTORYMANAGE_H
