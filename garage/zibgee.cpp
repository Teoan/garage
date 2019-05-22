#include "zibgee.h"

zibgee::zibgee()
{

}

zibgee::~zibgee()
{

}

void zibgee::init_tty(int fd){
    //保存原先串口配置到变量old_cfg中
    struct termios new_cfg, old_cfg;
    if(tcgetattr(fd, &old_cfg) != 0)
    {
        perror("tcgetattr() failed");
        exit(0);
    }

    bzero(&new_cfg, sizeof(new_cfg));
    new_cfg = old_cfg;

    //将中断设置为原始模式
    cfmakeraw(&new_cfg);

    //分别设置输入波特率和输出波特率，一般情况下设置为相同
    cfsetispeed(&new_cfg, B115200);
    cfsetospeed(&new_cfg, B115200);

    //开启本地连接和本地使能
    new_cfg.c_cflag |= CLOCAL | CREAD;

    //先将数据位清零，再设置数据位为8位
    new_cfg.c_cflag &= ~CSIZE;
    new_cfg.c_cflag |= CS8;

    //设置无奇偶校验位
    new_cfg.c_cflag &= ~PARENB;
    //设置没有停止位
    new_cfg.c_cflag &= ~CSTOPB;
    //设置时间
    // MIN > 0和TIME = 0：read()函数会被阻塞直到MIN个字节数据可被读取。
    new_cfg.c_cc[VTIME] = 0;
    new_cfg.c_cc[VMIN]  = 1;

    //清空缓存区
    tcflush(fd, TCIFLUSH);

    //激活串口
    if(tcsetattr(fd, TCSANOW, &new_cfg) != 0)
    {
        perror("tcsetattr() failed");
        exit(0);
    }
}

QString zibgee::getTempstr(){
    //打开串口1  波特率115200
    ser_fd= open(USART1,O_RDWR);
    if (ser_fd < 0)
    {
        perror("Open GEC6818_serical fail !");
    }
    /*初始化串口*/
       init_tty(ser_fd);
        bzero(message,32);
        read(ser_fd,message,32);
//        printf("%s\n",message);
        tempStr = QString(message);
        tcflush(ser_fd, TCIOFLUSH); //刷新缓冲区
        sleep(2);

    close(ser_fd);
    return tempStr;
}
