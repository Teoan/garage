#ifndef ZIBGEE_H
#define ZIBGEE_H
#include "garage.hpp"


#define BUFSIZE 1024
#define USART1	"/dev/ttySAC1"
class zibgee
{
public:
    zibgee();
    ~zibgee();
    QString getTempstr();

private:
    void init_tty(int);
    char message[32];
    QString tempStr;
    int ser_fd;
};

#endif // ZIBGEE_H
