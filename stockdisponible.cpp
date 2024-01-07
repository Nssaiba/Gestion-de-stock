#include "stockdisponible.h"
#include "ui_stockdisponible.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>

StockDisponible::StockDisponible(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StockDisponible)
{
    ui->setupUi(this);
}

StockDisponible::~StockDisponible()
{
    delete ui;
}

void StockDisponible::on_btnStockDispo_clicked()
{
    QString NomP = ui->txtNomPDispo->text();


    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("c:/Users/Dell/gestion_stock.db");

    if (!db.open())
    {
        qDebug() << "Database connection error: " << db.lastError().text();
        return;
    }

    QSqlQuery query(db);

    // Use a parameterized query to prevent SQL injection
    query.prepare("select Id, Name,Quantity from Produit where Name like '%"+NomP+"%'");
    query.exec();
    qDebug() << query.lastError().text() << query.lastQuery();
    if(model == NULL){

        model=new QSqlQueryModel();
    }


    model->setQuery(query);
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0,150);
    ui->tableView->setColumnWidth(1,200);
    ui->tableView->setColumnWidth(2,200);
    qDebug() << "rows are : " << model->rowCount();
    ui->tableView->show();
}
