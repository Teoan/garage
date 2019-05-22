#include "mainwidget.h"
#include "ui_mainwidget.h"

//温湿度全局变量
double mainWidget::temp ;
double mainWidget::hum ;
QSqlDatabase mainWidget::database;
int mainWidget::nowCarCount = 0;

mainWidget::mainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainWidget)
{
    //设置背景
    ui->setupUi(this);
    qpalette.setBrush(QPalette::Background,QBrush(QPixmap(":/bg/icon/bg2.jpg")));
    this->setPalette(qpalette);
    movie =new QMovie(":/bg/icon/itas_800_480.gif");

    //设置开机动画
    ui->start_lable->setMovie(movie);
    movie->start();
    start_timer = new QTimer(this);
    connect(start_timer,SIGNAL(timeout()),this,SLOT(finishedPlay()));
    start_timer->start(6000);
    system("madplay mp3/start.mp3 &");

    //创建线程获取温湿度
    tempFuture = QtConcurrent::run(getTemp,Tempzibgee,&isGetTemp);


   // 初始化数据库
    initSqlite();
}

mainWidget::~mainWidget()
{
    delete ui;
}
//打开相机页面
void mainWidget::on_camera_Button_clicked()
{
    cameras = new camera();
    connect(cameras,SIGNAL(sendSignals()),this,SLOT(reShow()));
    cameras->show();
    this->hide();
}

void mainWidget::reShow(){
    this->show();
}
    //停止播放开机动画
void mainWidget::finishedPlay(){

    movie->stop();
    ui->start_lable->close();
   start_timer->stop();
   //创建线程显示时间
    future =QtConcurrent::run(showTime,ui->lcdNumber);
     //打开扫描界面
      scanners = new scanner();
      connect(scanners,SIGNAL(sendSignals()),this,SLOT(reShow()));
      scanners->show();
      this->hide();

}

//关闭程序
void mainWidget::on_shut_down_Button_clicked()
{

    ui->lcdNumber->setEnabled(false);
    future.waitForFinished();
    isGetTemp = false;
    tempFuture.waitForFinished();
    database.close();
    this->close();
}

//显示时间
void mainWidget::showTime(QLCDNumber* timeLCD){
    QDateTime datetime;
    QString nowtime ;
    while(timeLCD->isEnabled()){
        datetime= QDateTime::currentDateTime();
        datetime.setTimeSpec(Qt::LocalTime);
        nowtime = datetime.toString("yyyy-MM-dd hh:mm:ss ");
        timeLCD->setDigitCount(nowtime.size());
        timeLCD->display(nowtime);
    }
}

//打开扫描页面
void mainWidget::on_back_Button_clicked()
{
        scanners = new scanner();
        connect(scanners,SIGNAL(sendSignals()),this,SLOT(reShow()));
         scanners->show();
        this->hide();
}
//获取温湿度
void mainWidget::getTemp(zibgee tempzib, bool *flag){
    while(*flag)
    {
        QString str = tempzib.getTempstr();
        temp = str.left(4).toDouble();
        hum = str.right(4).toDouble();
        //温湿度超出一定阀值时报警
        if(temp>setting::wanningTempValue||hum>setting::wanningHumValue)
        {
            rfid::beep(1);
            camera::Delay_MSec(300);
            rfid::beep(0);
        }
    }
}

//初始化Sqlite
void mainWidget::initSqlite(){
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("garage.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    QSqlQuery sql_query;
    //判断数据库是否存在
    if(!IsTableExist(sql_query,"garage"))
    {
        if(!sql_query.exec("create table garage(id integer primary key autoincrement, plate text, startTime text)"))
        {
            qDebug() << "Error: Fail to create table."<< sql_query.lastError();
        }
    }
    else{
        //计算当前车辆数
        sql_query.exec("select * from garage");
        sql_query.last();
    if(sql_query.at()==-2)
        nowCarCount =0;
    else
        nowCarCount = sql_query.at()+1;
    }



}

bool mainWidget::IsTableExist(QSqlQuery &query,QString table)
{
   QString sql = QString("select * from sqlite_master where name='%1'").arg(table);
   query.exec(sql);
   return query.next();
}

//跳转到计费页面
void mainWidget::on_cost_Button_clicked()
{
    costs = new cost();
    connect(costs,SIGNAL(sendSignals()),this,SLOT(reShow()));
    costs->show();
    this->hide();
}
//跳转到设置页面
void mainWidget::on_setting_Button_clicked()
{
    settings = new setting();
    connect(settings,SIGNAL(sendSignals()),this,SLOT(reShow()));
   settings->show();
   this->hide();
}
