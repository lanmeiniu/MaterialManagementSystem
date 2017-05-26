#include "WarehouseManage.h"
#include "ui_WarehouseManage.h"

WarehouseManage::WarehouseManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WarehouseManage)
{
    ui->setupUi(this);
    //this->showNormal();
    QPalette p;
    p.setBrush(QPalette::Background,QBrush(QPixmap(":/loginbg.png").scaled(this->size())));
    this->setPalette(p);
    this->setWindowIcon(QIcon(":/cangchu.png"));
    //显示关闭按钮
    this->setWindowFlags(Qt::WindowCloseButtonHint);

    this->setWindowTitle("仓储管理 ");
    ui->MIpushButton->setIcon(QIcon(":/search.png"));
    ui->MMpushButton->setIcon(QIcon(":/modify.png"));
    ui->MSpushButton->setIcon(QIcon(":/storage.png"));
    ui->MOpushButton->setIcon(QIcon(":/outbound.png"));
    ui->MDpushButton->setIcon(QIcon(":/delete.png"));
    ui->IOpushButton->setIcon(QIcon(":/outboundsearch.png"));
    ui->CPpushButton->setIcon(QIcon(":/cpassword.png"));
    ui->SOpushButton->setIcon(QIcon(":/signout.png"));
    ui->ESpushButton->setIcon(QIcon(":/exit2.png"));
    ui->testpushButton->setIcon(QIcon(":/icon.png"));


    //设置定时器
    timelinetimer = new QTimer(this);
    timelinetimer->setInterval(100);
    timelinetimer->start();
    connect(timelinetimer,SIGNAL(timeout()),this,SLOT(settimeline()));

    //0.设置退出系统的信号与槽
    connect(ui->ESpushButton,SIGNAL(clicked(bool)),this,SLOT(exitbtnSlot()));
   //1.设置注销用户按钮信号与槽
    connect(ui->SOpushButton,SIGNAL(clicked(bool)),this,SLOT(returnbtnSlot()));
    //2.设置修改密码窗口
    warehousepassword = new Warehousepassword;
    ui->warehousestack->addWidget(warehousepassword);
    warehousepassword->hide();
    connect(ui->CPpushButton,SIGNAL(clicked(bool)),this,SLOT(passwordbtnSlot()));
    connect(this,SIGNAL(towarehousepassword(QString)),warehousepassword,SLOT(comeWarehouseManage(QString)));
    //3.创建仓管员查询物料信息窗口MaterialInquiry
    materialinquiry = new MaterialInquiry;
    ui->warehousestack->addWidget(materialinquiry);
    connect(ui->MIpushButton,SIGNAL(clicked(bool)),this,SLOT(inquirybtnSlot()));
    //4.创建仓管员修改物料窗口MaterialModify
    materialmodify = new MaterialModify;
    ui->warehousestack->addWidget(materialmodify);
    connect(this,SIGNAL(tomaterialmodify()),materialmodify,SLOT(comeWarehouseManage(QString)));
    connect(ui->MMpushButton,SIGNAL(clicked(bool)),this,SLOT(modifybtnSlot()));
    //5.创建管理员增加物料窗口MaterialStorage
    materialstorage = new MaterialStorage;
    ui->warehousestack->addWidget(materialstorage);
    connect(ui->MSpushButton,SIGNAL(clicked(bool)),this,SLOT(storagebtnSlot()));
    //6.创建仓管员出库物料窗口MaterialOutbound
    materialoutbound = new MaterialOutbound;
    ui->warehousestack->addWidget(materialoutbound);
    connect(this,SIGNAL(tomaterialoutbound()),materialoutbound,SLOT(comeWarehouseManage(QString)));
    connect(ui->MOpushButton,SIGNAL(clicked(bool)),this,SLOT(outboundSlot()));
    //7.创建仓管员删除物料窗口MaterialDelete
    materialdelete = new MaterialDelete;
    ui->warehousestack->addWidget(materialdelete);
    connect(this,SIGNAL(tomaterialdelete()),materialdelete,SLOT(comeWarehouseManage(QString)));
    connect(ui->MDpushButton,SIGNAL(clicked(bool)),this,SLOT(deletebtnSlot()));
    //8.创建物料出库信息查询窗口
    inquirymaterialoutbound = new InquiryMaterialOutbound;
    ui->warehousestack->addWidget(inquirymaterialoutbound);
    connect(this,SIGNAL(toinquirymaterialoutbound()),inquirymaterialoutbound,SLOT(comeWarehouseManage(QString)));
    connect(ui->IOpushButton,SIGNAL(clicked(bool)),this,SLOT(inquiryoutboundbtnSlot()));
    //各个功能与仓管员管理窗口信号槽连接，用于设置button属性

    connect(materialinquiry,SIGNAL(EmitToWarehouseManage()),this,SLOT(setbtnEnableSlot()));
    connect(materialmodify,SIGNAL(EmitToWarehouseManage()),this,SLOT(setbtnEnableSlot()));
    connect(materialstorage,SIGNAL(EmitToWarehouseManage()),this,SLOT(setbtnEnableSlot()));
    connect(materialdelete,SIGNAL(EmitToWarehouseManage()),this,SLOT(setbtnEnableSlot()));
    connect(materialoutbound,SIGNAL(EmitToWarehouseManage()),this,SLOT(setbtnEnableSlot()));
    connect(warehousepassword,SIGNAL(EmitToWarehouseManage()),this,SLOT(setbtnEnableSlot()));
    connect(inquirymaterialoutbound,SIGNAL(EmitToWarehouseManage()),this,SLOT(setbtnEnableSlot()));
    connect(materialinquiry,SIGNAL(EmitToWarehouseManageToModifyStack()),this,SLOT(setbtnEnableSlot()));
    connect(materialmodify,SIGNAL(EmitToWarehouseManageToModifyStack()),this,SLOT(setbtnEnableSlot()));
    connect(inquirymaterialoutbound,SIGNAL(EmitToWarehouseManageToinquiryStack()),this,SLOT(setbtnEnableSlot()));
}
WarehouseManage::~WarehouseManage()
{
    delete ui;
}

//在主界面显示当前登录人员信息
void WarehouseManage::comeLoginDialog(QString name, QString number)
{
    warehousename = name ;
    warehousenumber = number;
    ui->usernamelabel->setText(warehousename);
}

//在管理界面设置系统时间
void WarehouseManage::settimeline()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd");
    ui->systemtimelabel->setText(str);
}
//0.退出函数的槽函数
void WarehouseManage::exitbtnSlot()
{
    if(QMessageBox::question(this,tr("Prompt"),tr("Does it exit the system?"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
        this->close();
        delete this;
    }
}
//1.注销函数的槽函数
void WarehouseManage::returnbtnSlot()
{
    if(QMessageBox::question(this,tr("Prompt"),tr("Do you log out the user?"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
        //连接到登录界面
        emit toLoginDialog();
        delete this;
    }
}
//2.密码槽
void WarehouseManage::passwordbtnSlot()
{
    this->setbtnfalse();
    warehousepassword->show();
    ui->warehousestack->setCurrentIndex(2);
    emit towarehousepassword(warehousenumber);

}
//3.查询槽
void WarehouseManage::inquirybtnSlot()
{
    this->setbtnfalse();
    materialinquiry->show();
    ui->warehousestack->setCurrentIndex(3);
    emit tomaterialinquiry();
}
//4.修改槽,emit调用tomaterialmodify信号对应的槽函数
void WarehouseManage::modifybtnSlot()
{
    this->setbtnfalse();
    materialmodify->show();
    ui->warehousestack->setCurrentIndex(4);
    emit tomaterialmodify();
}
//5.入库存货槽
void WarehouseManage::storagebtnSlot()
{
    this->setbtnfalse();
    materialstorage->show();
    ui->warehousestack->setCurrentIndex(5);
    emit tomaterialstorage();
}
//6.出库槽
void WarehouseManage::outboundSlot()
{
    this->setbtnfalse();
    materialoutbound->show();
    ui->warehousestack->setCurrentIndex(6);
    emit tomaterialoutbound();
}
//7.删除存货信息槽
void WarehouseManage::deletebtnSlot()
{
    this->setbtnfalse();
    materialdelete->show();
    ui->warehousestack->setCurrentIndex(7);
    emit tomaterialdelete();
}
//8.显示出库物料出库信息
void WarehouseManage::inquiryoutboundbtnSlot()
{
    this->setbtnfalse();
    inquirymaterialoutbound->show();
    ui->warehousestack->setCurrentIndex(8);
    emit toinquirymaterialoutbound();
}

void WarehouseManage::setbtnfalse()
{
    ui->MIpushButton->setEnabled(false);
    ui->MMpushButton->setEnabled(false);
    ui->MSpushButton->setEnabled(false);
    ui->MOpushButton->setEnabled(false);
    ui->MDpushButton->setEnabled(false);
    ui->CPpushButton->setEnabled(false);
    ui->SOpushButton->setEnabled(false);
    ui->ESpushButton->setEnabled(false);
    ui->IOpushButton->setEnabled(false);
}
//
void WarehouseManage::setbtntrue()
{
    ui->MIpushButton->setEnabled(true);
    ui->MMpushButton->setEnabled(true);
    ui->MSpushButton->setEnabled(true);
    ui->MOpushButton->setEnabled(true);
    ui->MDpushButton->setEnabled(true);
    ui->CPpushButton->setEnabled(true);
    ui->SOpushButton->setEnabled(true);
    ui->ESpushButton->setEnabled(true);
    ui->IOpushButton->setEnabled(true);
}
//
void WarehouseManage::setbtnEnableSlot()
{
    this->setbtntrue();
}
//
void WarehouseManage::tosetStack()
{
    materialstorage->show();
    ui->warehousestack->setCurrentIndex(5);
}
