#include "inventorylist.h"
#include "ui_inventorylist.h"


InventoryList::InventoryList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InventoryList)
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
       model->setHeaderData(5,Qt::Horizontal,"实存数量");
       model->setHeaderData(6,Qt::Horizontal,"出库人员");


       ui->tableView->setItemDelegateForColumn(0,new ReadOnlyDelegate);
       ui->tableView->setItemDelegateForColumn(1,new ReadOnlyDelegate);
       ui->tableView->setItemDelegateForColumn(2,new ReadOnlyDelegate);
       ui->tableView->setItemDelegateForColumn(3,new ReadOnlyDelegate);
       ui->tableView->setItemDelegateForColumn(4,new ReadOnlyDelegate);

       model->select();
       model->removeColumns(5,4);

       //搜索以后的模式
       _model = new QSqlTableModel(this);
       _model->setTable("materiallist");
       _model->setEditStrategy(QSqlTableModel::OnManualSubmit);
       _model->setHeaderData(0,Qt::Horizontal,"商品编号");
       _model->setHeaderData(1,Qt::Horizontal,"商品名称");
       _model->setHeaderData(2,Qt::Horizontal,"规格");
       _model->setHeaderData(3,Qt::Horizontal,"单位");
       _model->setHeaderData(4,Qt::Horizontal,"账存数量");
       _model->setHeaderData(5,Qt::Horizontal,"实存数量");
       _model->setHeaderData(6,Qt::Horizontal,"出库人员");
       _model->select();
       _model->removeColumns(5,4);


       buttongroup = new QButtonGroup(this);
       buttongroup->addButton(ui->GoodIDradioButton,0);
       buttongroup->addButton(ui->GoodsNameradioButton,1);

       connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(inputeditSlot(QString)));
       connect(buttongroup,SIGNAL(buttonClicked(int)),this,SLOT(buttongroupSlot(int)));


}
InventoryList::~InventoryList()
{
    delete ui;
}
void InventoryList::comeMaterialManage()
{
    model->select();
       if(model->data(model->index(0,0)).toString().isEmpty())
       {
           QMessageBox::information(this,tr("Prompt"),tr("information is empty, please add information"),QMessageBox::Yes);
           emit EmitToInventoryToListManage();
           this->hide();
           return;
       }
       ui->tableView->setModel(model);
}
void InventoryList::searchbtnSlot()
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
void InventoryList::returnbtnSlot()
{
    if(judge==1)
        {
            emit EmitToInventoryManage();
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
            emit EmitToInventoryManage();
            this->hide();
            judge=1;
            return ;
        }
        else
        {
            emit EmitToInventoryManage();
            judge=1;
            this->hide();
        }
}

void InventoryList::inputeditSlot(QString)
{
    if(ui->lineEdit->text().isEmpty())
    {
        ui->tableView->setModel(model);
    }
}
void InventoryList::buttongroupSlot(int)
{
    ui->tableView->setModel(model);
    ui->lineEdit->clear();
}
ReadOnlyDelegate::ReadOnlyDelegate(QObject *parent)
{

}
ReadOnlyDelegate::~ReadOnlyDelegate()
{

}
QWidget *ReadOnlyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return NULL;
}
void InventoryList::submitSlot()
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
