#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include  "serialport.h"
#include "charge.h"
#include "card_id.h"
#include <QMainWindow>
#include "EventBus.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_SerialPort_clicked();

    void on_chareg_clicked();

    void on_chareg_2_clicked();

private:
    Ui::MainWindow *ui;
    SerialPort* serial = new SerialPort;
    Charge* charge_view = new Charge;
    card_id* card_manage=new card_id;
    EventBus *eventBus;
};


#endif // MAINWINDOW_H
