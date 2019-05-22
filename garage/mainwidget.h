#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "scanner.h"
#include "setting.h"
#include "cost.h"
#include "zibgee.h"
#include "garage.hpp"

namespace Ui {
class mainWidget;
}

class mainWidget : public QWidget
{
    Q_OBJECT


public:
    explicit mainWidget(QWidget *parent = 0);
    ~mainWidget();
    static double temp ;
    static  double hum ;
    static  QSqlDatabase database;
    static  int nowCarCount;


private slots:
    void on_camera_Button_clicked();
    void reShow();
    void finishedPlay();
    void on_shut_down_Button_clicked();
   void on_back_Button_clicked();
   void on_cost_Button_clicked();
   void on_setting_Button_clicked();
signals:
    void sendSignals();
private:
    Ui::mainWidget *ui;
    QPalette qpalette;
    class camera *cameras;
    class scanner *scanners;
    class setting *settings;
    class cost *costs;
    QTimer *start_timer;
    QMovie *movie ;
    QFuture<void> future,tempFuture ;
    zibgee Tempzibgee;
    bool isGetTemp =true;
    static void getTemp(zibgee,bool *);
    void initSqlite();
    bool IsTableExist(QSqlQuery &,QString);
    static void showTime(QLCDNumber *);
};

#endif // MAINWIDGET_H
