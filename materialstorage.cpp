#include "materialstorage.h"
#include "ui_materialstorage.h"

MaterialStorage::MaterialStorage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MaterialStorage)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this);
    model->setTable("materiallist"); 
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

//    //设置lineedit提示字段
//    ui->GoodsIDlineEdit->setPlaceholderText("商品名称");
//    ui->goodsnamelineEdit->setPlaceholderText("商品名称");
//    ui->specificationlineEdit->setPlaceholderText("规格");
//    ui->unitlineEdit->setPlaceholderText("单位");
//    ui->accountnumberlineEdit->setPlaceholderText("账存数量");
//    ui->operaterlineEdit->setPlaceholderText("In_Operater");

    //按钮连接的信号与槽
    connect(ui->submitpushButton,SIGNAL(clicked()),this,SLOT(confirmbtnSlot()));
    connect(ui->backpushButton,SIGNAL(clicked()),this,SLOT(returnbtnSlot()));
}

MaterialStorage::~MaterialStorage()
{
    delete ui;
}

void MaterialStorage::clearAll()
{
    ui->GoodsIDlineEdit->clear();
    ui->goodsnamelineEdit->clear();
    ui->specificationlineEdit->clear();
    ui->unitlineEdit->clear();
    ui->accountnumberlineEdit->clear();
    ui->operaterlineEdit->clear();
}
bool MaterialStorage::judgeEmpty()
{
    if(ui->GoodsIDlineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,tr("warning"),tr("GoodID can't be empty"),QMessageBox::Yes);
        return false;
    }
    else if(ui->goodsnamelineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,tr("warning"),tr("GoodName can't be empty"),QMessageBox::Yes);
        return false;
    }
    else if(ui->specificationlineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,tr("warning"),tr("specificaition can't be empty"),QMessageBox::Yes);
        return false;
    }
    else if(ui->unitlineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,tr("warning"),tr("Unit can't be empty"),QMessageBox::Yes);
        return false;
    }
    else if(ui->accountnumberlineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,tr("warning"),tr("Account_number can't be empty"),QMessageBox::Yes);
        return false;
    }
    else if(ui->operaterlineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,tr("warning"),tr("operater can't be empty"),QMessageBox::Yes);
        return false;
    }
    else
        return true;
}
void MaterialStorage::returnbtnSlot()
{
    if(ui->GoodsIDlineEdit->text().isEmpty()&&ui->goodsnamelineEdit->text().isEmpty()&&ui->specificationlineEdit->text().isEmpty()
            &&ui->unitlineEdit->text().isEmpty()&&ui->accountnumberlineEdit->text().isEmpty()&&ui->operaterlineEdit->text().isEmpty())
    {
        emit EmitToWarehouseManage();
        //this是这个窗口类的引用，用show方法，就是显示改窗体，反之hide（）就是隐藏
        this->hide();
        return;
    }
    if(QMessageBox::question(this,tr("Prompt"),tr("Not yet saved, whether to exit"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
        emit EmitToWarehouseManage();
        this->clearAll();
        this->hide();
    }
}
void MaterialStorage::confirmbtnSlot()
{
    if(!this->judgeEmpty())
        return;
    model->select();
    int i;
    for(i=0;i<model->rowCount();i++)
    {
        if(model->data(model->index(i,0)).toString()==ui->GoodsIDlineEdit->text())
            {
             break;
            }
    }
    //若是提早跳出循环，则说明lineEdit中与数据库的i行0列数据相符
    if(i!=model->rowCount())
        {
            QMessageBox::information(this,tr("Prompt"),tr("GoodID already exist,Please re-try"),QMessageBox::Yes);
            this->clearAll();
            return;
        }
    //

    QSqlRecord record=model->record();
    record.setValue("GoodsID",ui->GoodsIDlineEdit->text());
    record.setValue("GoodsName",ui->goodsnamelineEdit->text());
    record.setValue("Specification",ui->specificationlineEdit->text());
    record.setValue("Unit",ui->unitlineEdit->text());
    record.setValue("Account_Number",ui->accountnumberlineEdit->text().toFloat());
    record.setValue("入库人员",ui->operaterlineEdit->text());
    model->insertRecord(-1,record);

    if(model->submitAll())
    {
        QMessageBox::information(this,tr("Prompt"),tr("Information added successfully"),QMessageBox::Yes);
        this->clearAll();
    }
}

