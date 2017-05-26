#include "login.h"
#include <QApplication>
#include <QIcon>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    QTranslator translator;
    translator.load(":/qm/mms.qm");
    a.installTranslator(&translator);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("123456");
    db.setDatabaseName("material");
    if(db.open())
    {
        Login w;
        w.show();
        return a.exec();
    }
    else
    {
        QMessageBox::information(NULL,"ERROR","Can't run,Please Retry!",QMessageBox::Yes);
    }


   return 0;
}
