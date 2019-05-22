#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>
#include "v4l2.h"
#include "picture.h"
#include "mainwidget.h"
#include "garage.hpp"

namespace Ui {
class camera;
}

class camera : public QWidget
{
    Q_OBJECT

public:
    explicit camera(QWidget *parent = 0);
    static void Delay_MSec(unsigned int );
    static void savePicture(const char*,unsigned char*);
    ~camera();

private slots:
    void on_back_Button_clicked();
    void showBuff();

    void on_take_image_Button_clicked();

    void on_gallery_Button_clicked();

    void reShow();

signals:
    void sendSignals();
private:
    Ui::camera *ui;
    QPalette qpalette;
    pass_data pd;
    QTimer *timer;
     QPixmap m_qpixmap;
     class picture *pictureview;
     camera *camer;
     void open_Camera();
};

#endif // CAMERA_H
