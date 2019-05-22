#ifndef RFID_H
#define RFID_H
#include "garage.hpp"
#define DEV_PATH   "/dev/ttySAC2"      //设备定义

class rfid
{
public:
    rfid();
    ~rfid();
int getCardid();
 static void beep(int);
private:
    volatile unsigned int cardid ;         //卡片的ID
    void init_tty();
    /*计算校验和*/
    unsigned char CalBCC(unsigned char *buf, int n);
    int PiccRequest();
    /*防碰撞，获取范围内最大ID*/
    int PiccAnticoll();
    struct timeval timeout;          //串口
    int fd;
};

#endif // RFID_H
