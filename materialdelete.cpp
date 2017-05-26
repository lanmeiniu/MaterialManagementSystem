#include "materialdelete.h"
#include "ui_materialdelete.h"

MaterialDelete::MaterialDelete(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MaterialDelete)
{
    ui->setupUi(this);
    connect(ui->deletepushButton,SIGNAL(clicked(bool)),this,SLOT(deletebtnSlot()));
    connect(ui->backpushButton,SIGNAL(clicked(bool)),this,SLOT(returnbtnSlot()));

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    //创建model实现与数据库交互
    model = new QSqlTableModel(this);
    model->setTable("materiallist");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setHeaderData(0,Qt::Horizontal,"商品编号");
    model->setHeaderData(1,Qt::Horizontal,"商品名称");
    model->setHeaderData(2,Qt::Horizontal,"规格");
    model->setHeaderData(3,Qt::Horizontal,"单位");
    model->setHeaderData(4,Qt::Horizontal,"账存数量");
    model->setHeaderData(5,Qt::Horizontal,"入库人员");
    //添加了这句话，在界面显示数据库数据
    model->select();
    ui->tableView->setModel(model);
    model->removeColumns(6,5);
}

MaterialDelete::~MaterialDelete()
{
    delete ui;
}
void MaterialDelete::deletebtnSlot()
{
    if(ui->GoodsIDlineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,tr("Warning"),tr("Can't empty"));
        return;
    }
    model->select();
    int i;
    for(i=0;i<model->rowCount();i++)
    {
        if(model->data(model->index(i,0)).toString()== ui->GoodsIDlineEdit->text())
        {
            if(QMessageBox::question(this,tr("Prompt"),tr("Are you sure this delete?"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
            {
                model->removeRow(i);
                model->submitAll();
                ui->GoodsIDlineEdit->clear();
                return;
            }
            else
                return;
        }
    }
    QMessageBox::information(this,tr("Prompt"),tr("GoodID is not exit,fail to delete!"));
    ui->GoodsIDlineEdit->clear();
}
void MaterialDelete::returnbtnSlot()
{
    ui->GoodsIDlineEdit->clear();
    emit EmitToWarehouseManage();
    this->hide();
}
void MaterialDelete::comeMaterialManage()
{
    model->select();
    if(model->data(model->index(0,0)).toString().isEmpty())
    {
        QMessageBox::information(this,tr("Prompt"),tr("Information is empty,can't delete"),QMessageBox::Yes);
        emit EmitToWarehouseManage();
        this->hide();
        return;
    }
    ui->tableView->setModel(model);
}
