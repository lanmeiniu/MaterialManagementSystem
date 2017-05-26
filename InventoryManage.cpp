#include "InventoryManage.h"
#include "ui_InventoryManage.h"

InventoryManage::InventoryManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InventoryManage)
{
    ui->setupUi(this);
     this->setWindowIcon(QIcon(":/pandianguanli.png"));
    QPalette p;
    p.setBrush(QPalette::Background,QBrush(QPixmap(":/loginbg.png").scaled(this->size())));
    this->setPalette(p);
    ui->MIpushButton->setIcon(QIcon(":/search.png"));
    ui->ILpushButton->setIcon(QIcon(":/pandian.png"));
    ui->CPpushButton->setIcon(QIcon(":/cpassword.png"));
    ui->SOpushButton->setIcon(QIcon(":/signout.png"));
    ui->ESpushButton->setIcon(QIcon(":/exit2.png"));
    ui->testpushButton->setIcon(QIcon(":/icon.png"));
    //Qt::WindowCloseButtonHint://显示关闭按钮
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    //设置定时器
    timelinetimer = new QTimer(this);
    timelinetimer->setInterval(100);
    timelinetimer->start();
    connect(timelinetimer,SIGNAL(timeout()),this,SLOT(settimeline()));
    //0.设置退出系统的信号与槽
    connect(ui->ESpushButton,SIGNAL(clicked(bool)),this,SLOT(exitbtnSlot()));
    //1.设置注销用户按钮 信号与槽
    connect(ui->SOpushButton,SIGNAL(clicked(bool)),this,SLOT(returnbtnSlot()));
    //2.设置修改密码窗口 信号与槽
    inventorypassword = new Inventorypassword;
    ui->InventoryStack->addWidget(inventorypassword);
    inventorypassword->hide();
    connect(ui->CPpushButton,SIGNAL(clicked(bool)),this,SLOT(passwordbtnSlot()));
    connect(this,SIGNAL(toInventorynumber(QString)),inventorypassword,SLOT(comeInventoryManage(QString)));
    //3.设置物料查询窗口 material inquiry
    inventoryinquiry = new  Inventoryinquiry;
    ui->InventoryStack->addWidget(inventoryinquiry);
    inventoryinquiry->hide();
    //这句话的意思是想comeIventoryManage发射信号，获取inventorynumber，但是查询按钮并不需要调用，所以请忽略
 //   connect(this,SIGNAL(toInventoryinquiry(QString)),inventoryinquiry,SLOT(comeInventoryManage(QString)));
    connect(ui->MIpushButton,SIGNAL(clicked(bool)),this,SLOT(inquirybtnSlot()));
    //4.设置物资盘点窗口
    inventorylist = new InventoryList;
    ui->InventoryStack->addWidget(inventorylist);
    inventorylist->hide();
    connect(ui->ILpushButton,SIGNAL(clicked(bool)),this,SLOT(inventorylistbtnSlot()));
    connect(this,SIGNAL(toInventoryCheck(QString)),inventorylist,SLOT(comeMaterialManage()));

    //创建各种信号槽连接
    connect(inventoryinquiry,SIGNAL(EmitToInventoryManage()),this,SLOT(setbtnEnableSlot()));
    connect(inventoryinquiry,SIGNAL(EmitToWarehouseManageToModifyStack()),this,SLOT(setbtnEnableSlot()));
    connect(inventorypassword,SIGNAL(EmitToInventoryManage()),this,SLOT(setbtnEnableSlot()));
    connect(inventorylist,SIGNAL(EmitToInventoryManage()),this,SLOT(setbtnEnableSlot()));
}

InventoryManage::~InventoryManage()
{
    delete ui;
}
//在主界面，显示当前登录人员信息
void InventoryManage::comeLoginDialog(QString name, QString number)
{
    inventoryname = name ;
    inventorynumber = number;
    ui->usernamelabel->setText(inventoryname);
}
//在主界面设置系统时间
void InventoryManage::settimeline()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd");
    ui->systemtimelabel->setText(str);
}
//0.设置退出系统信号与槽
void InventoryManage::exitbtnSlot()
{
    if(QMessageBox::question(this,"提示","是否退出系统？",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
       {
           this->close();
           delete this;
       }
}
//1.设置注销用户信号与槽
void InventoryManage::returnbtnSlot()
{
    if(QMessageBox::question(this,"提示","是否退出账户？",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
        emit toLoginDialog();
        delete this;
        }

}
//2.修改密码信号与槽
void InventoryManage::passwordbtnSlot()
{
    inventorypassword->show();
    ui->InventoryStack->setCurrentIndex(2);
    emit toInventorynumber(inventorynumber);
    this->btnsetfalse();
}
//3.物料查询信号与槽
void InventoryManage::inquirybtnSlot()
{
    this->btnsetfalse();
    inventoryinquiry->show();
    ui->InventoryStack->setCurrentIndex(3);
    emit toInventoryinquiry();
}

//4.物资盘点信号与槽
void InventoryManage::inventorylistbtnSlot()
{
    this->btnsetfalse();
    inventorylist->show();
    ui->InventoryStack->setCurrentIndex(4);
    emit toInventoryCheck();
}

void InventoryManage::btnsetfalse()
{
    ui->CPpushButton->setEnabled(false);
    ui->SOpushButton->setEnabled(false);
    ui->ESpushButton->setEnabled(false);
    ui->MIpushButton->setEnabled(false);
    ui->ILpushButton->setEnabled(false);
}
void InventoryManage::btnsettrue()
{
    ui->CPpushButton->setEnabled(true);
    ui->SOpushButton->setEnabled(true);
    ui->ESpushButton->setEnabled(true);
    ui->MIpushButton->setEnabled(true);
    ui->ILpushButton->setEnabled(true);
}
void InventoryManage::setbtnEnableSlot()
{
    this->btnsettrue();

}

