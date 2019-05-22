#ifndef SCANNER_H
#define SCANNER_H

#include <QWidget>

#include "v4l2.h"
#include "garage.hpp"
#include "rfid.h"
#include "camera.h"
#include "zibgee.h"
#include "mainwidget.h"

namespace Ui {
class scanner;
}

class scanner : public QWidget
{
    Q_OBJECT

public:
    explicit scanner(QWidget *parent = 0);
    ~scanner();

private slots:
    void on_gallery_Button_clicked();
     void scannRfid();

     void on_lock_Button_clicked();

signals:
    void sendSignals();

private:
    Ui::scanner *ui;
    QPalette qpalette;
    QTimer *timer;
    pass_data pd;
     QPixmap m_qpixmap;
     QFuture<void> gallery_future,flashCamer_future,temp_future;
     rfid rfids;
     zibgee zibgees;
     bool isStart = true;
     bool isShowTemp = true;
     void open_Camera();
    static void gallery(unsigned char*,int,int,QLabel *,QLCDNumber *);
    static void flashCameraDate(bool*,pass_data);
    static void showTempHum(QLabel *,QLabel *,bool *);
    void back_main();
    static bool isHaveSame(const char*);
};

#endif // SCANNER_H
