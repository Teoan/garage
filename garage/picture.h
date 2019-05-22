#ifndef PICTURE_H
#define PICTURE_H

#include <QWidget>
#include "camera.h"
#include "math.h"

namespace Ui {
class picture;
}

class picture : public QWidget
{
    Q_OBJECT

public:
    explicit picture(QWidget *parent = 0);
    ~picture();

private:
    Ui::picture *ui;
    QStringList getDirAllFileName(QString);
    QStringList ImageFileNameList;
    int count;
signals:
    void sendSignals();
private slots:
    void on_close_Button_clicked();
    void on_back_Button_clicked();
    void on_next_Button_clicked();
};

#endif // PICTURE_H
