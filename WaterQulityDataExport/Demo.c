#include "wiringPi.h"
#include "wiringSerial.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
        int fd;
        wiringPiSetup();  						//初始化树莓派引脚
        char cmd;
        char *str;
        str=(char*)malloc(1024);
        fd=serialOpen("/dev/ttyAMA1",115200);       //打开并初始串口

        while(1){
//              serialPutchar(fd,'c');
//              serialPuts(fd,"aaaaaaaaa\r\n");
                while(serialDataAvail(fd)<=0);		//获取串口缓存中可用的字节数

                cmd = serialGetchar(fd);			//从串口读取一个字节数据返回
//              memset(str,0,1024);
//              sprintf(str,"get cmd:%c\r\n",cmd);
//              serialPuts(fd,str);					//发送一个字符串到串口
                printf("get data:cmd=%c\n",cmd);
                serialPrintf (fd, "get cmd:%c\r\n", cmd);	//发送数据到串口
                if(cmd=='q'){
                        serialPuts(fd,"quit\r\n");
                        printf("quit\n");
                        break;
                }
//              delayMicroseconds(1000000);
        }
        free(str);
        serialClose(fd);							//关闭fd关联的串口
        return 0;
}


