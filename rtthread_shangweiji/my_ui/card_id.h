#ifndef CARD_ID_H
#define CARD_ID_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>
namespace Ui {
    class card_id;
}

class card_id : public QWidget
{
Q_OBJECT
    friend class Charge;
public:
    explicit card_id(QWidget *parent = nullptr);
    ~card_id();
    //QSqlDatabase db ;
    QSqlQueryModel *model;

private slots:
    void on_add_clicked();

    void on_search_clicked();

    void on_delet_clicked();

private:
    Ui::card_id *ui;
};


#endif // CARD_ID_H
