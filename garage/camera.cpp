#include "camera.h"
#include "ui_camera.h"


camera::camera(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::camera)
{
    ui->setupUi(this);
    qpalette.setBrush(QPalette::Background,QBrush(QPixmap(":/bg/icon/bg2.jpg")));
    this->setPalette(qpalette);

    //设置计时器 用于刷新显示lable
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer,SIGNAL(timeout()),this,SLOT(showBuff()));
     pd.dev_name="/dev/video7";
    open_Camera();

}

camera::~camera()
{
    if (timer->isActive()) {
           timer->stop();
       }
    stop_dev (&pd);
    delete ui;
}

   // 显示摄像头
void camera::showBuff(){

    read_frame(&pd);
    ui->image_label->setText("");
    m_qpixmap.loadFromData((unsigned char*)pd.buffers[pd.buf.index].start,IHEIGHT*IWIDTH*3);
    ui->image_label->setPixmap(m_qpixmap);
    return_data(&pd);
}
//打开摄像头
void camera::open_Camera(){
    int flag = init_dev(&pd);
       if (flag == -1) {
           QMessageBox::information(this,tr("Tip"),tr("没有找到设备"));
           exit(1);
       }
       else if (flag == -2) {
           QMessageBox::information(this,tr("Tip"),tr("设备错误"));
           exit(2);
       }
       else if (flag == -3) {
           QMessageBox::information(this,tr("Tip"),tr("无法打开设备"));
           exit(3);
       }
       timer->start();
       ui->image_label->setText("正在打开摄像头...");
}

//返回上一个页面
void camera::on_back_Button_clicked()
{
    if (timer->isActive()) {
           timer->stop();
       }
    stop_dev (&pd);
    emit sendSignals();
    this->close();
}

 //保存按钮到槽函数 以时间命名保存一张图片
void camera::on_take_image_Button_clicked()
{
     static clock_t t =0;
    QString timestr = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ");
    savePicture(timestr.toLatin1().data(),(unsigned char*)pd.buffers[pd.buf.index].start);
    ui->text_label->setText("已拍摄一张图片");
    Delay_MSec(1000);
    ui->text_label->setText("");
}
//保存一张图片
void camera::savePicture(const char* fileName,unsigned char* data){
    QPixmap savePix;

    QString filePath = QString("./picture/%1.jpg").arg(fileName);
    savePix.loadFromData(data,IHEIGHT*IWIDTH*3);
    savePix.save(filePath);
}
//延时函数
void camera:: Delay_MSec(unsigned int msec)
{
    QTime _Timer = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < _Timer )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
 //跳转到图片页面
void camera::on_gallery_Button_clicked()
{
    pictureview = new picture();
    connect(pictureview,SIGNAL(sendSignals()),this,SLOT(reShow()));
    pictureview->show();
    if (timer->isActive()) {
           timer->stop();
       }
    stop_dev (&pd);
    this->hide();
}
//重新打开页面
void camera::reShow(){
    open_Camera();
    this->show();
}


