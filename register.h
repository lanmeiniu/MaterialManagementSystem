#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QDebug>
#include <QPalette>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <QTime>
#include <QMessageBox>
#include <QButtonGroup>

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();
    void clearAll();
    void setVerification();
    bool judgeEmpty();

private:
    Ui::Register *ui;
    QSqlTableModel *model;
    QButtonGroup *radiogroup;
    int verification;
private slots:
    void registerbuttonSlot();
    void returnbuttonSlot();
    void registerbuttonSetSlot(QString);
};

#endif // REGISTER_H
