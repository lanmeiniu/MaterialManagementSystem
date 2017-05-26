#ifndef INQUIRYMATERIALOUTBOUND_H
#define INQUIRYMATERIALOUTBOUND_H

#include <QWidget>
#include <QSqlTableModel>
#include <QDebug>
#include <QStringList>
#include <QMessageBox>
#include <QButtonGroup>
#include <QScrollArea>

namespace Ui {
class InquiryMaterialOutbound;
}

class InquiryMaterialOutbound : public QWidget
{
    Q_OBJECT

public:
    explicit InquiryMaterialOutbound(QWidget *parent = 0);
    ~InquiryMaterialOutbound();

private:
    Ui::InquiryMaterialOutbound *ui;
    QSqlTableModel *model,*_model;
    QButtonGroup *buttongroup;
private slots:
    void searchbtnSlot();
    void comeMaterialManage();
    void returnbtnSlot();
    void inputeditSlot(QString);
    void buttongroupSlot(int);
signals:
    void EmitToWarehouseManage();
    void EmitToWarehouseManageToinquiryStack();
};

#endif // INQUIRYMATERIALOUTBOUND_H
