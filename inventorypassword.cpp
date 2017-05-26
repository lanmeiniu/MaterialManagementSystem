#include "inventorypassword.h"
#include "ui_inventorypassword.h"

Inventorypassword::Inventorypassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Inventorypassword)
{
    ui->setupUi(this);
    //创建model实现与数据库交互
    model = new QSqlTableModel(this);
    model->setTable("inventory");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //设置验证码
    QTime v;
    v = QTime::currentTime();
    qsrand(v.msec()+v.second()*1000);
    this->setyanzheng();
    //连接两个按钮的信号和槽
    connect(ui->confirmbtn,SIGNAL(clicked(bool)),this,SLOT(submitSlot()));
    connect(ui->canclebtn,SIGNAL(clicked(bool)),this,SLOT(backSlot()));
}

Inventorypassword::~Inventorypassword()
{
    delete ui;
}
void Inventorypassword::comeInventoryManage(QString number)
{
    inventorynumber=number;
}
void Inventorypassword::backSlot()
{
    if(ui->oldpassline->text().isEmpty()&&ui->newpassline->text().isEmpty()&&ui->confirmline->text().isEmpty())
    {
        emit EmitToInventoryManage();
        this->hide();
        this->clearAll();
        this->setyanzheng();
        return ;
    }
    if(QMessageBox::question(this,tr("Prompt"),tr("Password has not been modified,whether to exit?"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
        emit EmitToInventoryManage();
        this->hide();
        this->clearAll();
        this->setyanzheng();
    }
}
void Inventorypassword::submitSlot()
{
    if(!this->judgeEmpty())
    {
        this->clearAll();
        this->setyanzheng();
        return ;
    }
    model->setFilter("inventorynumber= "+inventorynumber);
    model->select();
    QSqlRecord record = model->record(0);
    //如果旧密码与数据库第二列中的数据不一致
    if(record.value(2)!=ui->oldpassline->text())
    {
        QMessageBox::warning(this,tr("Prompt"),tr("Old Password input is incorrect,plese re-set!"),QMessageBox::Yes);
        this->clearAll();
        this->setyanzheng();
        return ;
    }
    //如果新密码与再次确认密码行的密码不一致
    if(ui->newpassline->text() != ui->confirmline->text())
    {
        QMessageBox::warning(this,tr("warning"),tr("Two password entries are inconsistent,please reset"),QMessageBox::Yes);
        this->clearAll();
        this->setyanzheng();
        return ;
    }
    //如果旧密码与新密码一样
    if(ui->oldpassline->text()==ui->newpassline->text())
    {
        QMessageBox::warning(this,tr("warning"),tr("New and old passwords are consistent,please reset"),QMessageBox::Yes);
        this->clearAll();
        this->setyanzheng();
        return ;
    }
    //setaData()用于存储数据
    model->setData(model->index(0,2),ui->newpassline->text());
    if(model->submitAll())
        QMessageBox::information(this,tr("warning"),tr("Password reset complete"),QMessageBox::Yes);
    else
        QMessageBox::warning(this,tr("warning"),tr("Password modification failed"),QMessageBox::Yes);
        this->clearAll();
        this->setyanzheng();
}
void Inventorypassword::setyanzheng()
{
    yanzhengma = qrand()%10000;
    while (yanzhengma < 1000)
    yanzhengma = qrand()%1000;
    ui->yanzhenglabel->setText(QString::number(yanzhengma));
}
void Inventorypassword::clearAll()
{
    ui->oldpassline->clear();
    ui->newpassline->clear();
    ui->confirmline->clear();
    ui->yanzhengline->clear();
}
bool Inventorypassword::judgeEmpty()
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
    else if(ui->confirmline->text().isEmpty())
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
