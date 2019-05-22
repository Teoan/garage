#include "cost.h"
#include "ui_cost.h"

cost::cost(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cost)
{
    ui->setupUi(this);
    qpalette.setBrush(QPalette::Background,QBrush(QPixmap(":/bg/icon/bg2.jpg")));
    this->setPalette(qpalette);
    //禁止编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    initTableview();
}

cost::~cost()
{
    delete ui;
}

//初始化列表
void cost::initTableview(){
    int i=0;
    model = new QStandardItemModel();
    ui->tableView->setModel(model);
//    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    //设置行宽
    model->setColumnCount(4);
    ui->tableView->setColumnWidth(0,180);
    ui->tableView->setColumnWidth(1,247);
    ui->tableView->setColumnWidth(2,110);
    ui->tableView->setColumnWidth(3,120);

    model->setHeaderData(0,Qt::Horizontal,"车牌");
    model->setHeaderData(1,Qt::Horizontal,"进库时间");
    model->setHeaderData(2,Qt::Horizontal,"停留时间");
    model->setHeaderData(3,Qt::Horizontal,"应收费用");

    QSqlQuery sql_query;

    //查找表
    sql_query.exec("select * from garage");
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            int stayHour;
            QString plate = sql_query.value(1).toString();
            QString startTimeStr= sql_query.value(2).toString();
            stayHour = getStayHour(startTimeStr);
            model->setItem(i,0,new QStandardItem(plate));
            //设置表格字体居中
            model->item(i,0)->setTextAlignment(Qt::AlignCenter);
            model->setItem(i,1,new QStandardItem(startTimeStr));
            model->item(i,1)->setTextAlignment(Qt::AlignCenter);
            model->setItem(i,2,new QStandardItem(QString::number(stayHour)));
            model->item(i,2)->setTextAlignment(Qt::AlignCenter);
            model->setItem(i,3,new QStandardItem(QString::number(stayHour*setting::garage_cost)));
            model->item(i,3)->setTextAlignment(Qt::AlignCenter);
            i++;
        }
    }
}
//返回上一个页面
void cost::on_pushButton_clicked()
{
    emit sendSignals();
    this->close();
}

//获取停留时间
int cost::getStayHour(QString startTimeStr){
    int stayHour=0;
    QDateTime startTime = QDateTime::fromString(startTimeStr, "yyyy-MM-dd hh:mm:ss");
    qint64 secToNow = startTime.secsTo(QDateTime::currentDateTime());
    if(secToNow%3600)
        stayHour = secToNow/3600+1;
    else
        stayHour = secToNow/3600;
   return stayHour;
}
//删除按钮槽函数
void cost::on_deletc_pushButton_clicked()
{
        QSqlQuery sql_query;
        sql_query.exec("delete from garage");
        mainWidget::nowCarCount =0;
        initTableview();
}
