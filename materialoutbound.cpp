#include "materialoutbound.h"
#include "ui_materialoutbound.h"

MaterialOutbound::MaterialOutbound(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MaterialOutbound)
{
    ui->setupUi(this);
    judge =1;

    //两个按钮建立信号与槽
    connect(ui->searchpushButton,SIGNAL(clicked(bool)),this,SLOT(searchbtnSlot()));
    connect(ui->backpushButton,SIGNAL(clicked(bool)),this,SLOT(returnbtnSlot()));
    connect(ui->submitpushButton,SIGNAL(clicked(bool)),this,SLOT(submitSlot()));
    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


    model = new QSqlTableModel(this);
    model->setTable("materiallist");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setHeaderData(0,Qt::Horizontal,"商品编号");
    model->setHeaderData(1,Qt::Horizontal,"商品名称");
    model->setHeaderData(2,Qt::Horizontal,"规格");
    model->setHeaderData(3,Qt::Horizontal,"单位");
    model->setHeaderData(4,Qt::Horizontal,"账存数量");
    ui->tableView->setItemDelegateForColumn(0,new ReadOnly);
    ui->tableView->setItemDelegateForColumn(1,new ReadOnly);
    ui->tableView->setItemDelegateForColumn(2,new ReadOnly);
    ui->tableView->setItemDelegateForColumn(3,new ReadOnly);
    ui->tableView->setItemDelegateForColumn(4,new ReadOnly);
    ui->tableView->setItemDelegateForColumn(5,new ReadOnly);

    model->select();
    model->removeColumns(9,2);

    //搜索以后的模式
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

MaterialOutbound::~MaterialOutbound()
{
    delete ui;
}
void MaterialOutbound::searchbtnSlot()
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
                QMessageBox::warning(this,tr("warning"),tr("GoodsID does not exit"));
                ui->tableView->setModel(model);
                ui->lineEdit->clear();
                return ;
            }

            ui->tableView->setModel(_model);

        }
        else if (buttongroup->checkedId() == 1)
        {
            _model->setFilter("GoodsName='"+ui->lineEdit->text()+"'");
            _model->select();
            if(_model->data(model->index(0,0)).toString().isEmpty())
            {
                QMessageBox::warning(this,tr("Warning"),tr("GoodsName does not exit"));
                ui->tableView->setModel(model);
                ui->lineEdit->clear();
                return;
            }
            ui->tableView->setModel(_model);
        }
        else
            {
                QMessageBox::warning(this,tr("warning"),tr("please select inquiry model"));
            }
}
void MaterialOutbound::comeMaterialManage()
{

    model->select();
    if(model->data(model->index(0,0)).toString().isEmpty())
    {
        QMessageBox::information(this,tr("Prompt"),tr("information is null,please insert"),QMessageBox::Yes);
        emit EmitToWarehouseManage();
        this->hide();
        return;
     }
        ui->tableView->setModel(model);
}
void MaterialOutbound::returnbtnSlot()
{
    ui->lineEdit->clear();
    emit EmitToWarehouseManage();
    this->hide();

}
void MaterialOutbound::inputeditSlot(QString)
{
    if(ui->lineEdit->text().isEmpty())
    {
        ui->tableView->setModel(model);

    }
}
void MaterialOutbound::buttongroupSlot(int)
{
    ui->tableView->setModel(model);
    ui->lineEdit->clear();
}
ReadOnly::ReadOnly(QObject *parent)
{

}
ReadOnly::~ReadOnly()
{

}
QWidget *ReadOnly::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return NULL;
}
void MaterialOutbound::submitSlot()
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
