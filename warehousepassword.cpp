#include "warehousepassword.h"
#include "ui_warehousepassword.h"

Warehousepassword::Warehousepassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Warehousepassword)
{
    ui->setupUi(this);
    //创建model实现与数据库交互
    model = new QSqlTableModel(this);
    model->setTable("warehouse");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //设置输入lineedit为密码样式
    ui->oldpassline->setEchoMode(QLineEdit::PasswordEchoOnEdit);

    //设置验证码
    QTime v;
    v = QTime::currentTime();
    qsrand(v.msec()+v.second()*1000);
    this->setVerificationCode();
    //连接两个按钮的信号和槽
    connect(ui->confirmbtn,SIGNAL(clicked(bool)),this,SLOT(confirmbtnSlot()));
    connect(ui->returnbtn,SIGNAL(clicked(bool)),this,SLOT(returnbtnSlot()));
}

Warehousepassword::~Warehousepassword()
{
    delete ui;
}
void Warehousepassword::comeWarehouseManage(QString number)
{
    warehousenumber=number;
}
void Warehousepassword::returnbtnSlot()
{
    if(ui->oldpassline->text().isEmpty()&&ui->newpassline->text().isEmpty()&&ui->confirmpassline->text().isEmpty())
    {
        emit EmitToWarehouseManage();
        this->hide();
        this->clearAll();
        this->setVerificationCode();
        return ;
    }
    if(QMessageBox::question(this,tr("Prompt"),tr("Password has not been modified,whether to exit"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
        emit EmitToWarehouseManage();
        this->hide();
        this->clearAll();
        this->setVerificationCode();
    }
}
void Warehousepassword::confirmbtnSlot()
{
    if(!this->judgeEmpty())
    {
        this->clearAll();
        this->setVerificationCode();
        return ;
    }
    model->setFilter("warehousenumber = "+warehousenumber);
    model->select();
    QSqlRecord record = model->record(0);
    //如果旧密码与数据库第二列中的数据不一致
    if(record.value(2)!=ui->oldpassline->text())
    {
        QMessageBox::warning(this,tr("Prompt"),tr("Old Password input is incorrect,plese re-set"),QMessageBox::Yes);
        this->clearAll();
        this->setVerificationCode();
        return ;
    }
    //如果新密码与再次确认密码行的密码不一致
    if(ui->newpassline->text() != ui->confirmpassline->text())
    {
        QMessageBox::warning(this,tr("Prompt"),tr("Two password entries are inconsistent,please reset"),QMessageBox::Yes);
        this->clearAll();
        this->setVerificationCode();
        return ;
    }
    //如果旧密码与新密码一样
    if(ui->oldpassline->text()==ui->newpassline->text())
    {
        QMessageBox::warning(this,tr("warning"),tr("New and old passwords are consistent,please reset"),QMessageBox::Yes);
        this->clearAll();
        this->setVerificationCode();
        return ;
    }
    //setaData()用于存储数据
    model->setData(model->index(0,2),ui->newpassline->text());
    if(model->submitAll())
        QMessageBox::information(this,tr("Prompt"),tr("Password reset complete"),QMessageBox::Yes);
    else
        QMessageBox::warning(this,tr("Prompt"),tr("Password modification failed"),QMessageBox::Yes);
        this->clearAll();
        this->setVerificationCode();
}
void Warehousepassword::setVerificationCode()
{
    verificationcode = qrand()%10000;
    while (verificationcode < 1000)
    verificationcode = qrand()%1000;
    ui->yanzhenglabel->setText(QString::number(verificationcode));
}
void Warehousepassword::clearAll()
{
    ui->oldpassline->clear();
    ui->newpassline->clear();
    ui->confirmpassline->clear();
    ui->yanzhengline->clear();
}
bool Warehousepassword::judgeEmpty()
{
    if(ui->oldpassline->text().isEmpty())
    {
        QMessageBox::warning(this,tr("warning"),tr("The old password can not be empty"));
        return false;
    }
    else if(ui->newpassline->text().isEmpty())
    {
        QMessageBox::warning(this,tr("warning"),tr("The new password can not be empty"));
        return false;
    }
    else if(ui->confirmpassline->text().isEmpty())
    {
        QMessageBox::warning(this,tr("warning"),tr("The confirm password can not be empty"));
        return false;
    }
    else if(ui->yanzhengline->text().isEmpty())
    {
        QMessageBox::warning(this,tr("warning"),tr("The verification can not be empty"));
        return false;
    }
    else
        return true;

}
