#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include"garage.hpp"

namespace Ui {
class setting;
}

class setting : public QWidget
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = 0);
    ~setting();
    static double wanningTempValue;
    static double wanningHumValue;
    static int garage_count;
    static int garage_cost;
signals:
    void sendSignals();

private slots:
    void on_pushButton_clicked();

    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_temp_horizontalSlider_valueChanged(int value);

    void on_temp_doubleSpinBox_valueChanged(double arg1);

    void on_hum_horizontalSlider_valueChanged(int value);

    void on_hum_spinBox_valueChanged(int arg1);

    void on_garage_horizontalSlider_valueChanged(int value);

    void on_garage_spinBox_valueChanged(int arg1);

    void on_cost_horizontalSlider_valueChanged(int value);

    void on_cost_spinBox_valueChanged(int arg1);

private:
    Ui::setting *ui;
     QPalette qpalette;
};

#endif // SETTING_H
