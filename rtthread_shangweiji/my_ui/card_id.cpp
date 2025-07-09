#include "card_id.h"
#include "ui_card_id.h"
#include <QTime>
#include <QTimer>
#include "QSqlDatabase"
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQueryModel>

QString cardnum;
extern QSqlDatabase db ;
card_id::card_id(QWidget *parent)
        : QWidget(parent)
        , ui(new Ui::card_id)
{
    ui->setupUi(this);
    //db=QSqlDatabase::addDatabase("QSQLITE");
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("card_num.db");
    if(!db.open())
    {
        qDebug()<<" 11ERRO";
    }
    if(db.open())
    {
        qDebug()<<" oppen";
    }
//    QTimer* Timer_ = new QTimer();
//    Timer_->setInterval(1000);
//    connect(Timer_, &QTimer::timeout, this, [=]()
//    {
//        if(QString::localeAwareCompare(cardnum, "0000"))
//        {
//            ui->card_num->setText(cardnum);
//        }
//    });
//    Timer_->start();
}

card_id::~card_id()
{
    delete ui;
}

void card_id::on_add_clicked()
{
    QString num  = ui->card_num->text();
    if(!db.open())
    {
        qDebug()<<" 11ERRO";
    }
    if(db.open())
    {
        qDebug()<<" oppen";
    }
    QSqlQuery sql_query;

    QString cardNum = ui->card_num->text();
    QString rank = ui->rank->text();
    QString phone = ui->phone_number->text();
    QString pay = ui->rank_2->text();
    qDebug() << "cardNum"<<pay;

    sql_query.exec(QString("SELECT id FROM card WHERE id = '%1'").arg(cardNum));
    if (sql_query.next())
    {
        sql_query.prepare("UPDATE card SET rank = :newRank, phone = :newPhone, pay_m = :newPay WHERE id = :id");
        sql_query.bindValue(":newRank", rank);      // 使用外部传入的 rank 新值
        sql_query.bindValue(":newPhone", phone);    // 使用外部传入的 phone 新值
        sql_query.bindValue(":newPay", pay);        // 使用外部传入的 pay 新值
        sql_query.bindValue(":id", cardNum);        // WHERE 子句的条件
        if (!sql_query.exec())
        {
            qDebug() << "Insert card error:" << sql_query.lastError();
        }
    }
    else if (!sql_query.next())
    {
        sql_query.prepare("INSERT INTO card (id, rank, phone,pay_m) VALUES (:id, :rank, :phone,:pay_m)");
        sql_query.bindValue(":id", cardNum);
        sql_query.bindValue(":rank", rank);
        sql_query.bindValue(":phone", phone);
        sql_query.bindValue(":pay_m", pay);
        if (!sql_query.exec())
        {
            qDebug() << "Insert card error:" << sql_query.lastError();
        }

    }
    model = new QSqlQueryModel(this);

    model->setQuery("select * from card");

    model->setHeaderData(0, Qt::Horizontal, tr( "卡号"   ));
    model->setHeaderData(1, Qt::Horizontal, tr( "等级"   ));
    model->setHeaderData(2, Qt::Horizontal, tr( "手机号"  ));
    model->setHeaderData(3, Qt::Horizontal, tr( "余额"  ));

    db.close();

    ui->tableView->setModel(model);

}


void card_id::on_search_clicked()
{

    if(!db.open())
    {
        qDebug()<<" 11ERRO";
    }
    model = new QSqlQueryModel(this);

    model->setQuery("select * from card");

    model->setHeaderData(0, Qt::Horizontal, tr( "卡号"   ));
    model->setHeaderData(1, Qt::Horizontal, tr( "等级"   ));
    model->setHeaderData(2, Qt::Horizontal, tr( "手机号"  ));
    model->setHeaderData(3, Qt::Horizontal, tr( "余额"  ));




    db.close();

    ui->tableView->setModel(model);

}


void card_id::on_delet_clicked()
{
    QSqlQuery sql_query;
    if(!db.open())
    {
        qDebug()<<" 11ERRO";
    }
    QString cardNum = ui->card_num->text();
    qDebug() << cardNum;
    sql_query.exec(QString("SELECT id FROM card WHERE id = '%1'").arg(cardNum));
    if (!sql_query.next())
    {
        qDebug() << "The book no exists.";
    } else
    {
        QString sql = QString("delete from card where id = '%1'").arg(cardNum);
        QSqlQuery query;
        query.exec(sql);
    }
}
