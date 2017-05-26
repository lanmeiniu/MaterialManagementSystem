#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

    //创建model,进行数据库操作
    model = new QSqlTableModel(this);
    model ->setEditStrategy(QSqlTableModel::OnManualSubmit);
    QPalette p;
    p.setBrush(QPalette::Background,QBrush(QPixmap(":/loginbg.png").scaled(this->size())));
    this->setPalette(p);
    ui->returnpushButton->setIcon(QIcon(":/exit.png"));
    ui->registrationpushButton->setIcon(QIcon(":/register.png"));
    ui->warehouseradioButton->setIcon(QIcon(":/cang.png"));
    ui->inventoryradioButton->setIcon(QIcon(":/pan.png"));
    //密码，半隐藏式 输入完时候，隐藏

    ui->passwordlineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    ui->confirmpasslineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);

    ui->registrationpushButton->setEnabled(false);

    connect(ui->registrationpushButton,SIGNAL(clicked(bool)),this,SLOT(registerbuttonSlot()));
    connect(ui->returnpushButton,SIGNAL(clicked(bool)),this,SLOT(returnbuttonSlot()));
    //设置随机验证码
    QTime time;
    time = QTime ::currentTime();
    this->setVerification();
    //设置QButtonGroup
    radiogroup = new QButtonGroup(this);
    radiogroup->addButton(ui->warehouseradioButton,0);
    radiogroup->addButton(ui->inventoryradioButton,1);

    //lineedit与槽连接
    connect(ui->accoutlineEdit,SIGNAL(textChanged(QString)),this,SLOT(registerbuttonSetSlot(QString)));
    connect(ui->passwordlineEdit,SIGNAL(textChanged(QString)),this,SLOT(registerbuttonSetSlot(QString)));
    connect(ui->accoutnamelineEdit,SIGNAL(textChanged(QString)),this,SLOT(registerbuttonSetSlot(QString)));
}

Register::~Register()
{
    delete ui;
}

void Register::registerbuttonSlot()
{
    int i;
    if(! this->judgeEmpty())
    {
        ui->accoutlineEdit->clear();
        ui->accoutnamelineEdit->clear();
        ui->passwordlineEdit->clear();
        ui->confirmpasslineEdit->clear();
        ui->verificationlineEdit->clear();
        return;
    }

    //校验两次密码是否输入正确

    if(ui->passwordlineEdit->text()!=ui->confirmpasslineEdit->text())
    {
        QMessageBox::warning(this,tr("warning"),tr("Two passwords are inconsistent"),QMessageBox::Yes);
        ui->accoutlineEdit->clear();
        ui->accoutnamelineEdit->clear();
        ui->passwordlineEdit->clear();
        ui->confirmpasslineEdit->clear();
        ui->verificationlineEdit->clear();
        this->setVerification();

        return;
    }
    //验证码是否输入正确
    if(ui->verificationlabel->text()!=ui->verificationlineEdit->text())
    {
        QMessageBox::warning(this,tr("warning"),tr("Incorrect verification code"),QMessageBox::Yes);
        ui->accoutlineEdit->clear();
        ui->accoutnamelineEdit->clear();
        ui->passwordlineEdit->clear();
        ui->confirmpasslineEdit->clear();
        ui->verificationlineEdit->clear();
        //重置校验码
        this->setVerification();
        return;
    }

    //判断是否是仓管员注册
    if(radiogroup->checkedId()==0)
    {
        model->setTable("Warehouse");
        model->select();

        for(i=0;i<model->rowCount();i++)
        {
            QSqlRecord record = model->record(i);

            if((record.value(0)==ui->accoutlineEdit->text()&&record.value(2)!=""))
            {
                QMessageBox::critical(this,tr("warning"),tr("The user already exists"),QMessageBox::Yes);
                this->clearAll();
                this->setVerification();
                return ;
            }
        }
        //如果仓管员信息不存在，则添加仓管员信息进数据库
        if(i==model->rowCount())
        {
            QSqlRecord recordl = model->record();
            recordl.setValue("warehousenumber",ui->accoutlineEdit->text());
            recordl.setValue("warehousename",ui->accoutnamelineEdit->text());
            recordl.setValue("wpassword",ui->passwordlineEdit->text());
            model->insertRecord(-1,recordl);
        }
        //判断仓管员信息是否上传数据库

        if(model->submitAll())
        {
            QMessageBox::information(this,tr("prompt"),tr("congratulations on your success~"),QMessageBox::Yes);
            this->accept();
        }
        else
        QMessageBox::information(this,tr("Prompt"),tr("registration failed please re-register"),QMessageBox::Yes);
        this->clearAll();
        this->setVerification();
    }
    //判断是否是盘点员
    else if (radiogroup->checkedId()==1)
    {
        int i;
        model->setTable("inventory");
        model->select();
        for(i=0;i<model->rowCount();i++)
        {
            QSqlRecord record = model->record(i);
            if(record.value(0) == ui->accoutlineEdit->text())
            {
                QMessageBox::warning(this,tr("prompt"),tr("The user already exists"),QMessageBox::Yes);
                this->clearAll();
                this->setVerification();
                return;
            }
        }
        if(i==model->rowCount())
        {
            QSqlRecord record = model->record();
            record.setValue("inventorynumber",ui->accoutlineEdit->text());
            record.setValue("inventoryname",ui->accoutnamelineEdit->text());
            record.setValue("ipassword",ui->passwordlineEdit->text());
            model->insertRecord(-1,record);
        }
        //判断盘点员信息是否上传数据库
        if(model->submitAll())
        {
            QMessageBox::information(this,tr("prompt"),tr("Successful"),QMessageBox::Yes);
            this->accept();
        }
        else
        QMessageBox::information(this,tr("prompt"),tr("Fail!Please re-register"),QMessageBox::Yes);
        this->clearAll();
        this->setVerification();

    }
    else
         QMessageBox::warning(this,tr("warning"),tr("Select the registration method"),QMessageBox::Yes);
}

void Register::returnbuttonSlot()
{
    this->accept();
}

void Register::registerbuttonSetSlot(QString)
{
    ui->registrationpushButton->setEnabled(true);
}

//清空lineedit的上的文本
void Register::clearAll()
{
    ui->accoutlineEdit->clear();
    ui->passwordlineEdit->clear();
    ui->confirmpasslineEdit->clear();
    ui->accoutlineEdit->clear();
    ui->verificationlineEdit->clear();
}
//设置验证码

void Register::setVerification()
{
    verification = qrand()%10000;
    while(verification<1000)
        verification = qrand()%10000;
    ui->verificationlabel->setText(QString::number(verification));
}
//判断lineedit是否为空

bool Register::judgeEmpty()
{
    if(ui->accoutnamelineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,tr("warning"),tr("accountname can not be empty"));
        return false;
    }
    else if(ui->accoutlineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,tr("warning"),tr("Accout can not be empty"));
        return false;
    }
    else if(ui->passwordlineEdit->text().isEmpty()||
            ui->confirmpasslineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,tr("warning"),tr("The password can not be empty"));
        return false;
    }
    else if (ui->verificationlineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,tr("warning"),tr("Verification code must be filled"));
        return false;
    }
    else
        return true;
}
