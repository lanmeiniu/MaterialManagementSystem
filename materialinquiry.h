#ifndef MATERIALINQUIRY_H
#define MATERIALINQUIRY_H

#include <QWidget>
#include <QSqlTableModel>
#include <QDebug>
#include <QStringList>
#include <QMessageBox>
#include <QButtonGroup>
#include <QScrollArea>


namespace Ui {
class MaterialInquiry;
}

class MaterialInquiry : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialInquiry(QWidget *parent = 0);
    ~MaterialInquiry();

private:
    Ui::MaterialInquiry *ui;
    QSqlTableModel *model,*_model;
    QButtonGroup *buttongroup;
private slots:
    void searchbtnSlot();
    void comeMaterialManage();
    void returnbtnSlot();
    void inputeditSlot(QString);
    void buttongroupSlot(int);
//    void comeOutboundManage(QString);
signals:
    void EmitToWarehouseManage();
    void EmitToWarehouseManageToModifyStack();
};

#endif // MATERIALINQUIRY_H
