#ifndef INVENTORYPASSWORD_H
#define INVENTORYPASSWORD_H

#include <QWidget>
#include <QTime>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QMessageBox>

namespace Ui {
class Inventorypassword;
}

class Inventorypassword : public QWidget
{
    Q_OBJECT

public:
    explicit Inventorypassword(QWidget *parent = 0);
    ~Inventorypassword();
    void setyanzheng();
    void clearAll();
    bool judgeEmpty();
private:
    Ui::Inventorypassword *ui;
    int yanzhengma;
    QString inventorynumber;
    QSqlTableModel *model;
private slots:
    void comeInventoryManage(QString);
    void submitSlot();
    void backSlot();
signals:
    void EmitToInventoryManage();
};

#endif // INVENTORYPASSWORD_H
