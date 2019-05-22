#ifndef COST_H
#define COST_H

#include <QWidget>
#include "setting.h"
#include "garage.hpp"
#include "mainwidget.h"

namespace Ui {
class cost;
}

class cost : public QWidget
{
    Q_OBJECT

public:
    explicit cost(QWidget *parent = 0);
    ~cost();
    static  int getStayHour(QString);

signals:
    void sendSignals();

private slots:
    void on_pushButton_clicked();

    void on_deletc_pushButton_clicked();

private:
    Ui::cost *ui;
    QPalette qpalette;
    QStandardItemModel *model;
    void initTableview();

};

#endif // COST_H
