#include "scanner.h"
#include "ui_scanner.h"

scanner::scanner(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::scanner)
{
    ui->setupUi(this);
    qpalette.setBrush(QPalette::Background,QBrush(QPixmap(":/bg/icon/bg2.jpg")));
    this->setPalette(qpalette);
    timer = new QTimer(this);
    timer->setInterval(1000);
    pd.dev_name="/dev/video7";
    ui->scanner_label->hide();
    open_Camera();
    connect(timer,SIGNAL(timeout()),this,SLOT(scannRfid()));
    //创建线程显示温湿度
     temp_future = QtConcurrent::run(showTempHum,ui->temp_label,ui->hum_label,&isShowTemp);
     ui->lcdNumber->display(QString::number(setting::garage_count-mainWidget::nowCarCount));
}

scanner::~scanner()
{
    gallery_future.waitForFinished();
    if (timer->isActive()) {
           timer->stop();
       }
    stop_dev (&pd);
    delete ui;
}

void scanner::on_gallery_Button_clicked()
{
//    gallery_future.waitForFinished();
    system("madplay mp3/wite.mp3 &");
    ui->plate_label->setText("车牌:正在识别...");
    //创建线程识别车牌
    gallery_future =QtConcurrent::run(gallery,(unsigned char*)pd.buffers[pd.buf.index].start,600,800,ui->plate_label,ui->lcdNumber);

}


void scanner::gallery(unsigned char* srcbuf,int hight,int width,QLabel  *result_lable ,QLCDNumber* garageLCD){
    using namespace easypr;
    using namespace cv;
    CvMat mCvmat = cvMat(width,hight,CV_8UC2,srcbuf);
    IplImage* IpImg = cvDecodeImage(&mCvmat, 1);
    Mat image = cvarrToMat(IpImg);
     CPlateRecognize pr;
      pr.setResultShow(false);
      pr.setDetectType(PR_DETECT_SOBEL);
      pr.setLifemode(true);
      vector<CPlate> plateVec;
      int result =pr.plateRecognize(image, plateVec);
      if(result==0&&!plateVec.empty())
      {
           CPlate cp =plateVec.at(0);
           String ret = cp.getPlateStr();
            if(ret.size()==16){
                result_lable->setText("车牌:");
                cout<<ret<<endl;
//                cout<<ret.size()<<endl;
                QSqlQuery sql_query;
                if(isHaveSame(ret.c_str())){
                    QString sql= QString("select startTime from garage where plate = '%1'").arg(ret.c_str());
                    sql_query.exec(sql);
                    sql_query.next();
                    QString startTime = sql_query.value(0).toString();
                    int hour = cost::getStayHour(startTime);
                    result_lable->setText("已停留"+QString::number(hour)+"小时,应收费用"+QString::number(hour*setting::garage_cost)+"元。");
                    sql = QString("delete from garage where plate = '%1'").arg(ret.c_str());
                    sql_query.exec(sql);
                    system("madplay mp3/rad.mp3 &");
                    mainWidget::nowCarCount -=1;
                    garageLCD->display(QString::number(setting::garage_count-mainWidget::nowCarCount));
                }
                else{
                    result_lable->setText(result_lable->text()+ret.c_str());
                    system("madplay mp3/welcome.mp3 &");
                    QString insertSql = QString("INSERT INTO garage VALUES(null,'%1','%2')").arg(ret.c_str()).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                    if(!sql_query.exec(insertSql))
                    {
                        qDebug() << sql_query.lastError();
                    }
                    mainWidget::nowCarCount +=1;
                    garageLCD->display(QString::number(setting::garage_count-mainWidget::nowCarCount));
                    QString timestr = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ");
                    camera::savePicture(timestr.toLatin1().data(),srcbuf);
                }
//                cout<<insertSql.toStdString()<<endl;
            }
            else
                  result_lable->setText("车牌:识别失败");
       }
       else
      {
          qDebug()<<"result error"<<endl;
           result_lable->setText("车牌:识别失败");
      }

      cvReleaseImage(&IpImg);
}
void scanner::open_Camera(){
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
       //刷新摄像头数据
       flashCamer_future = QtConcurrent::run(flashCameraDate,&isStart,pd);
}

//扫描rfid，进行身份认证
void scanner::scannRfid(){
    int cardID = rfids.getCardid();
    if(cardID!=-1&&cardID==0x8ed7fb79)
    {
            ui->scanner_label->setText("认证成功!");
            system("madplay mp3/success.mp3 &");
            back_main();
    }
    else
    {
        ui->scanner_label->setText("认证失败!");
        system("madplay mp3/fail.mp3 &");
         camera::Delay_MSec(300);
        ui->scanner_label->hide();
        timer->stop();
    }
}
//显示温湿度
void scanner::showTempHum(QLabel *tempLable,QLabel* humLable,bool *flag){
    while(*flag)
    {
        tempLable->setText("温度:"+QString::number(mainWidget::temp,'f',1)+"℃");
        humLable->setText("湿度:"+QString::number(mainWidget::hum,'f',1)+"%");
    }
}
//返回主界面
void scanner::back_main()
{
    isStart =false;
    isShowTemp = false;
    if (timer->isActive()) {
           timer->stop();
       }
    temp_future.waitForFinished();
   flashCamer_future.waitForFinished();
   gallery_future.waitForFinished();
   stop_dev (&pd);
   camera::Delay_MSec(1000);
    emit sendSignals();
    this->close();
}

void scanner::flashCameraDate(bool *isStart, pass_data pd){
    while(*isStart){
        read_frame(&pd);
        return_data(&pd);
    }
}
//检测数据库中是否存在相同到车牌数据
bool scanner::isHaveSame(const char* plate){
    QSqlQuery sql_query;
    QString selectSql = QString("select * from garage where plate = '%1'").arg(plate);
    sql_query.exec(selectSql);
    return sql_query.next();
}


void scanner::on_lock_Button_clicked()
{
    ui->scanner_label->show();
    ui->scanner_label->setText("请稍后...");
    system("madplay mp3/wite.mp3 &");
     timer->start();
}
