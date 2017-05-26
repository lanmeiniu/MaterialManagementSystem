#include "materialmodify.h"
#include "ui_materialmodify.h"

MaterialModify::MaterialModify(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MaterialModify)
{
    ui->setupUi(this);

    judge=1;

    connect(ui->submitpushButton,SIGNAL(clicked()),this,SLOT(confirmbtnSlot()));
    connect(ui->backpushButton,SIGNAL(clicked()),this,SLOT(returnbtnSlot()));
    //创建model实现与数据库交互
    model=new QSqlTableModel(this);
    model->setTable("materiallist");
    //在modify界面中显示数据列，add by myself
    ui->modifyView->setModel(model);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setHeaderData(0,Qt::Horizontal,"商品编号");
    model->setHeaderData(1,Qt::Horizontal,"商品名称");
    model->setHeaderData(2,Qt::Horizontal,"规格");
    model->setHeaderData(3,Qt::Horizontal,"单位");
    model->setHeaderData(4,Qt::Horizontal,"账存数量");
    //添加了这句话，在界面显示数据库数据
    model->select();

    model->removeColumns(6,5);
    //两个按钮信号和槽函数连接

    connect(model,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(judgeSlot(QModelIndex,QModelIndex)));
}

MaterialModify::~MaterialModify()
{
    delete ui;
}
void MaterialModify::comeWarehouseManage()
{
    model->select();
    if(model->data(model->index(0,0)).toString().isEmpty())
    {
        QMessageBox::information(this,tr("Prompt"),tr("Information is empty, please add information"),QMessageBox::Yes);
        emit EmitToWarehouseManageToModifyStack();
        this->hide();
        return;
    }
    ui->modifyView->setModel(model);
}
void MaterialModify::confirmbtnSlot()
{
    if(model->submitAll())
        QMessageBox::information(this,tr("Prompt"),tr("Congratulation,Successfully modified"),QMessageBox::Yes);
    else
    {
        QMessageBox::information(this,tr("Prompt"),tr("Fail to edit"),QMessageBox::Yes);
        model->revertAll();
    }
    judge=1;
}
void MaterialModify::returnbtnSlot()
{

    if(judge==1)
    {
        emit EmitToWarehouseManage();
        this->hide();
        return;
    }
    if(QMessageBox::question(this,tr("Prompt"),tr("Not yet saved"),QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes)
    {
        if(model->submitAll())
            QMessageBox::information(this,tr("Prompt"),tr("Successfully modified"),QMessageBox::Yes);
        else
        {
            QMessageBox::information(this,tr("Prompt"),tr("Fail to edit"),QMessageBox::Yes);
            model->revertAll();
        }
        emit EmitToWarehouseManage();
        this->hide();
        judge=1;
        return ;
    }
    else
    {
        emit EmitToWarehouseManage();
        judge=1;
        this->hide();
    }
}
void MaterialModify::judgeSlot(QModelIndex, QModelIndex)
{
    judge=0;
}
