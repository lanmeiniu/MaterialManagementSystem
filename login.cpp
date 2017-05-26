#include "login.h"
#include "ui_login.h"
#include <QVBoxLayout>


Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    model =new QSqlTableModel(this);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->setWindowIcon(QIcon(":/icon.png"));

    //设置groupbox，放置两个radiobutton
    radiogroup = new QButtonGroup(this);
    radiogroup->addButton(ui->WMradioButton,0);
    radiogroup->addButton(ui->IMradioButton,1);

    //登录按钮，不可用，为灰色
    ui->LoginpushButton->setEnabled(false);
   // 密码显示模式
    ui->passwordlineEdit->setEchoMode(QLineEdit::Password);
    //设置调色板,用于设置titlelabel的颜色
//    QPalette pa;
//    pa.setColor(QPalette::WindowText,Qt::blue);
//    ui->titlelabel->setPalette(pa);
    //设置调色板,用于设置logindialog的背景
    QPalette p;
    p.setBrush(QPalette::Background,QBrush(QPixmap(":/loginbg.png").scaled(this->size())));
    this->setPalette(p);
    //三个按钮键，链接信号和槽
    connect(ui->LoginpushButton,SIGNAL(clicked(bool)),this,SLOT(loginbtnSlot()));
    connect(ui->RegisterpushButton,SIGNAL(clicked(bool)),this,SLOT(registerbtnSlot()));
    connect(ui->ExitpushButton,SIGNAL(clicked(bool)),this,SLOT(exitbtnSlot()));
    //设置三个按钮的图标
    ui->ExitpushButton->setIcon(QIcon(":/exit.png"));
    ui->RegisterpushButton->setIcon(QIcon(":/register.png"));
    ui->LoginpushButton->setIcon(QIcon(":/login.png"));
    ui->WMradioButton->setIcon(QIcon(":/cang.png"));
    ui->IMradioButton->setIcon(QIcon(":/pan.png"));


    //设置右边图标
    ui->iconlabel->setPixmap(QPixmap(":/icon.png").scaled(ui->iconlabel->size()));
   // account password 进行信号与槽链接

    connect(ui->accountlineEdit,SIGNAL(textChanged(QString)),this,SLOT(loginbtnSetSlot(QString)));
    connect(ui->passwordlineEdit,SIGNAL(textChanged(QString)),this,SLOT(loginbtnSetSlot(QString)));

}

Login::~Login()
{
    delete ui;
}
void Login::loginbtnSlot()
{
    if(! this ->judgeEmpty())
    {
        ui->passwordlineEdit->clear();
        return;
    }
    //判断是否是仓管员登录
    if(radiogroup->checkedId()==0)
    {
        model->setTable("warehouse");
        model->select();
        int i;
        //rowcount 用于设置行数

        for(i=0;i<model->rowCount();i++)
        {
            QSqlRecord record = model->record(i);

            if(record.value(0)==ui->accountlineEdit->text()&&record.value(2)==ui->passwordlineEdit->text())
            {
               QString str1 = " 登录成功 ! ";
               QString str2 = record.value(1).toString();

               QMessageBox::information(this,"提示",str2 + str1 ,QMessageBox::Yes);
               this->clearAll();

                //创建仓储物资管理窗口

                warehouse = new WarehouseManage;
                connect(warehouse,SIGNAL(toLoginDialog()),this,SLOT(showNormal()));
                warehouse->show();

                connect(this,SIGNAL(toWarehouseManage(QString,QString)),warehouse,SLOT(comeLoginDialog(QString,QString)));
                emit toWarehouseManage(str2,record.value(0).toString());
                this->hide();
                return;
            }
            else if (record.value(0)==ui->accountlineEdit->text()&&record.value(2)!=ui->passwordlineEdit->text())
            {
                QMessageBox::information(this,"提示",tr("Password entered incorrectly"),QMessageBox::Yes);
                this->clearAll();
                return ;
            }

        }
        QMessageBox::warning(this,"提示",tr("The user does't exist,please register"),QMessageBox::Yes);
        this->clearAll();
        return;
    }
    //盘点员登录界面

    else if (radiogroup->checkedId()==1)
    {
        model->setTable("inventory");
        model->select();
        int i;

        for(i=0;i<model->rowCount();i++)
        {
            QSqlRecord record = model->record(i);
            if(record.value(0)==ui->accountlineEdit->text()&&record.value(2)==ui->passwordlineEdit->text())
            {
                QString str1=" 登录成功 ";
                QString str2=record.value(1).toString();

                QMessageBox::information(this,"提示",str2+str1,QMessageBox::Yes);

                //创建盘点员管理界面窗口
                inventory = new InventoryManage;
                inventory->show();
                connect(this,SIGNAL(toInventoryManage(QString,QString)),inventory,SLOT(comeLoginDialog(QString,QString)));
                connect(inventory,SIGNAL(toLoginDialog()),this,SLOT(showNormal()));
                emit toInventoryManage(str2,record.value(0).toString());
                this->clearAll();
                this->hide();
                return ;
            }
            else if(record.value(0)==ui->accountlineEdit->text()&&record.value(2)!=ui->passwordlineEdit->text())
            {
                QMessageBox::information(this,"提示",tr("Password entered incorrectly"),QMessageBox::Yes);
                this->clearAll();
                return;
            }
        }
        QMessageBox::warning(this,"提示",tr("The account doesn't exist,please register"),QMessageBox::Yes);
        this->clearAll();
        return ;
    }
    else
        QMessageBox::warning(this,"警告",tr("Please select the login method"),QMessageBox::Yes);
}

void Login::registerbtnSlot()
{
    Register d (this);
    this->hide();
    if(d.exec()==QDialog::Accepted)
    {
        this->showNormal();
    }
        d.clearAll();

}
void Login::exitbtnSlot()
{
    this->close();
}
void Login::loginbtnSetSlot(QString)
{
    ui->LoginpushButton->setEnabled(true);
}
void Login::clearAll()
{
    ui->accountlineEdit->setEnabled(true);
    ui->passwordlineEdit->clear();
}
bool Login::judgeEmpty()
{
    if(ui->accountlineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"警告",tr("Account can not be Empty"));
        return  false;
    }
    if(ui->passwordlineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"警告",tr("Password can not be blank"));
        return false;
    }
    else
        return true;
}
