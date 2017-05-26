#ifndef WAREHOUSEMANAGE_H
#define WAREHOUSEMANAGE_H

#include <QWidget>
#include <QDebug>
#include <QTimer>
#include <QDateTime>

#include "materialinquiry.h"
#include "materialmodify.h"
#include "materialstorage.h"
#include "materialoutbound.h"
#include "materialdelete.h"
#include "warehousepassword.h"
#include "inquirymaterialoutbound.h"

namespace Ui {
class WarehouseManage;
}

class WarehouseManage : public QWidget
{
    Q_OBJECT

public:
    explicit WarehouseManage(QWidget *parent = 0);
    ~WarehouseManage();
    void setbtntrue();
    void setbtnfalse();
private:
    Ui::WarehouseManage *ui;
    QString warehousename;
    QString warehousenumber;
    QTimer *timelinetimer;
    Warehousepassword *warehousepassword;
    MaterialInquiry *materialinquiry;
    MaterialModify *materialmodify;
    MaterialStorage *materialstorage;
    MaterialOutbound *materialoutbound;
    MaterialDelete *materialdelete;
    InquiryMaterialOutbound *inquirymaterialoutbound;


private slots:
    void comeLoginDialog(QString, QString);
    void settimeline();
    void exitbtnSlot();
    void returnbtnSlot();
    void passwordbtnSlot();
    void inquirybtnSlot();
    void modifybtnSlot();
    void storagebtnSlot();
    void deletebtnSlot();
    void setbtnEnableSlot();
    void outboundSlot();
    void tosetStack();
    void inquiryoutboundbtnSlot();
signals:
    void toLoginDialog();
    void towarehousepassword(QString);
    void tomaterialinquiry();
    void tomaterialmodify();
    void tomaterialdelete();
    void tomaterialstorage();
    void tomaterialoutbound();
    void toinquirymaterialoutbound();
};

#endif // WAREHOUSEMANAGE_H
