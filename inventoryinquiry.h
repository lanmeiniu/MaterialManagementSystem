#ifndef INVENTORYINQUIRY_H
#define INVENTORYINQUIRY_H

#include <QWidget>
#include <QSqlTableModel>
#include <QDebug>
#include <QStringList>
#include <QMessageBox>
#include <QButtonGroup>
#include <QScrollArea>
namespace Ui {
class Inventoryinquiry;
}

class Inventoryinquiry : public QWidget
{
    Q_OBJECT

public:
    explicit Inventoryinquiry(QWidget *parent = 0);
    ~Inventoryinquiry();

private:
    Ui::Inventoryinquiry *ui;
    QSqlTableModel *model,*_model;
    QButtonGroup *buttongroup;
private slots:
    void searchbtnSlot();
    void comeMaterialManage();
    void returnbtnSlot();
    void inputeditSlot(QString);
    void buttongroupSlot(int);

signals:
    void EmitToInventoryManage();
    void EmitToInventoryToListStack();
};

#endif // INVENTORYINQUIRY_H
