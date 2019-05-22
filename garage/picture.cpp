#include "picture.h"
#include "ui_picture.h"

picture::picture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::picture)
{
    ui->setupUi(this);
    count =0;
    ImageFileNameList = getDirAllFileName("./picture");
    if(ImageFileNameList.isEmpty())
    {
        ui->label->setText("无图片");
    }
    else{
        ui->label->setPixmap(QPixmap("./picture/"+ImageFileNameList[count]));
        ui->Image_name_label->setText(ImageFileNameList[count]);
        qDebug()<<"./picture/"+ImageFileNameList[count]<<endl;
        ui->label->setText("");
    }
}

picture::~picture()
{
    delete ui;
}

void picture::on_close_Button_clicked()
{
    emit sendSignals();
    this->close();
}

//获取所有jpg文件命字
QStringList picture::getDirAllFileName(QString dirPath){
    QDir dir(dirPath);
    if(!dir.exists()){
        return QStringList("");
    }
    dir.setFilter(QDir::NoSymLinks|QDir::Files);
    QStringList filters;
    filters<<"*.jpg";
    dir.setNameFilters(filters);
    QStringList allImageFlieList = dir.entryList();
    if(allImageFlieList.count()<=0){
        return QStringList("");
    }
    return allImageFlieList;
}

//上一张
void picture::on_back_Button_clicked()
{
    count--;
    QString fileName =ImageFileNameList[abs(count)%(ImageFileNameList.size())];
    ui->Image_name_label->setText(fileName);
    ui->label->setPixmap(QPixmap("./picture/"+fileName));
}
//下一张
void picture::on_next_Button_clicked()
{
    count++;
    QString fileName =ImageFileNameList[abs(count)%(ImageFileNameList.size())];
    ui->Image_name_label->setText(fileName);
    ui->label->setPixmap(QPixmap("./picture/"+fileName));
}
