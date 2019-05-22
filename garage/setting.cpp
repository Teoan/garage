#include "setting.h"
#include "ui_setting.h"
//设置默认值
double setting::wanningHumValue = 90.0;
double setting::wanningTempValue = 38.0;
int setting::garage_count = 300;
int setting::garage_cost = 10;

setting::setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);
    qpalette.setBrush(QPalette::Background,QBrush(QPixmap(":/bg/icon/bg2.jpg")));
    this->setPalette(qpalette);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());

    //初始化控件
    ui->temp_doubleSpinBox->setValue(wanningTempValue);
    ui->hum_spinBox->setValue(wanningHumValue);
    ui->garage_spinBox->setValue(garage_count);
    ui->cost_spinBox->setValue(garage_cost);
}

setting::~setting()
{
    delete ui;
}

void setting::on_pushButton_clicked()
{
    emit sendSignals();
    this->hide();
}

//dateTimeEdit控件槽函数，更改时间
void setting::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    QString timeStr = "date -s ";
     timeStr = timeStr +"\""+dateTime.toString("yyyy-MM-dd  hh:mm:ss")+"\"";
    system(timeStr.toLatin1().data());
    system("hwclock --systohc");
}

//控件数值相互变化
void setting::on_temp_horizontalSlider_valueChanged(int value)
{
    double dvalue = (double)value/10;
    ui->temp_doubleSpinBox->setValue(dvalue);
    wanningTempValue = dvalue;
}

void setting::on_temp_doubleSpinBox_valueChanged(double arg1)
{
    int value = arg1*10;
    ui->temp_horizontalSlider->setValue(value);
}

void setting::on_hum_horizontalSlider_valueChanged(int value)
{
    wanningHumValue = value;
    ui->hum_spinBox->setValue(value);
}

void setting::on_hum_spinBox_valueChanged(int arg1)
{
    ui->hum_horizontalSlider->setValue(arg1);
}

void setting::on_garage_horizontalSlider_valueChanged(int value)
{
    ui->garage_spinBox->setValue(value);
    garage_count = value;
}

void setting::on_garage_spinBox_valueChanged(int arg1)
{
    ui->garage_horizontalSlider->setValue(arg1);
}

void setting::on_cost_horizontalSlider_valueChanged(int value)
{
    garage_cost = value;
    ui->cost_spinBox->setValue(value);
}

void setting::on_cost_spinBox_valueChanged(int arg1)
{
    ui->cost_horizontalSlider->setValue(arg1);
}
