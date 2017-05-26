#include "inquirymaterialoutbound.h"
#include "ui_inquirymaterialoutbound.h"
#include <QVBoxLayout>

InquiryMaterialOutbound::InquiryMaterialOutbound(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InquiryMaterialOutbound)
{
    //设置ui
    ui->setupUi(this);

    connect(ui->backpushButton,SIGNAL(clicked(bool)),this,SLOT(returnbtnSlot()));
    connect(ui->searchpushButton,SIGNAL(clicked(bool)),this,SLOT(searchbtnSlot()));

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    model = new QSqlTableModel(this);
    model->setTable("materiallist");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setHeaderData(0,Qt::Horizontal,"商品编号");
    model->setHeaderData(1,Qt::Horizontal,"商品名称");
    model->setHeaderData(2,Qt::Horizontal,"规格");
    model->setHeaderData(3,Qt::Horizontal,"单位");
    model->setHeaderData(4,Qt::Horizontal,"账存数量");
    //添加了这句话，在界面显示数据库数据
    model->select();
    model->removeColumns(9,2);

    //创建_model实现数据查询
    _model = new QSqlTableModel(this);
    _model->setTable("materiallist");
    _model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    _model->setHeaderData(0,Qt::Horizontal,"商品编号");
    _model->setHeaderData(1,Qt::Horizontal,"商品名称");
    _model->setHeaderData(2,Qt::Horizontal,"规格");
    _model->setHeaderData(3,Qt::Horizontal,"单位");
    _model->setHeaderData(4,Qt::Horizontal,"账存数量");
    _model->select();
    _model->removeColumns(9,2);

    buttongroup = new QButtonGroup(this);
    buttongroup->addButton(ui->GoodIDradioButton,0);
    buttongroup->addButton(ui->GoodsNameradioButton,1);

    connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(inputeditSlot(QString)));
    connect(buttongroup,SIGNAL(buttonClicked(int)),this,SLOT(buttongroupSlot(int)));

}

InquiryMaterialOutbound::~InquiryMaterialOutbound()
{
    delete ui;
}
void InquiryMaterialOutbound::searchbtnSlot()
{

    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,tr("Warning"),tr("lineEdit does not empty!"));
        return;
    }
    if(buttongroup->checkedId()==0)
    {
        //筛选按照字符串filter对数据库进行筛选，相当于SQL中的where的语句
        _model->setFilter("GoodsID='"+ui->lineEdit->text()+"'");
        //显示结果
        _model->select();

        if(_model->data(model->index(0,0)).toString().isEmpty())
        {
            QMessageBox::warning(this,tr("Warning"),tr("GoodsID does not exit"));
            ui->tableView->setModel(model);
            ui->lineEdit->clear();
            return ;
        }

        ui->tableView->setModel(_model);

    }
    else if (buttongroup->checkedId() == 1)
    {
        _model->setFilter("出库人员='"+ui->lineEdit->text()+"'");
        _model->select();
        if(_model->data(model->index(0,0)).toString().isEmpty())
        {
            QMessageBox::warning(this,tr("Warning"),tr("Operater does not exit"));
            ui->tableView->setModel(model);
            ui->lineEdit->clear();
            return;
        }
        ui->tableView->setModel(_model);
    }
    else
    {
        QMessageBox::warning(this,tr("Warning"),tr("please select inquiry model"));
    }
}
void InquiryMaterialOutbound::comeMaterialManage()
{

       model->select();

       if(model->data(model->index(0,0)).toString().isEmpty())
       {
           QMessageBox::information(this,tr("Prompt"),tr("information is null,please insert"),QMessageBox::Yes);
           emit EmitToWarehouseManageToinquiryStack();
           this->hide();
           return;
       }
       ui->tableView->setModel(model);
}
void InquiryMaterialOutbound::returnbtnSlot()
{
    ui->lineEdit->clear();
    emit EmitToWarehouseManage();
    this->hide();
}
void InquiryMaterialOutbound::inputeditSlot(QString)
{
    if(ui->lineEdit->text().isEmpty())
    {
        ui->tableView->setModel(model);
    }
}
void InquiryMaterialOutbound::buttongroupSlot(int)
{
    ui->tableView->setModel(model);
    ui->lineEdit->clear();
}

