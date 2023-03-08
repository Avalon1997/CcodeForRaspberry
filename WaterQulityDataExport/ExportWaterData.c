/* --------------------------------------------------------------------------------------------------------- */
/**
 * @file ExportWaterData.c
 * @author Avalon1997 (https://github.com/Avalon1997)
 * @brief 
 *      This file is a code file 
 *      for analog output 
 *      to meet the needs of the Yangzi Petrochemical Project.
 * @version 1.0
 * @date 2023-03-07
 * 
 * @copyright Copyright (c) Avalon1997
 * 
 */
/* --------------------------------------------------------------------------------------------------------- */

/* ---------- Include ---------- */
#include <stdio.h>
// #include <wiringPi.h>
// #include <wiringSerial.h>
#include <unistd.h>
// #include <string.h>
// #include <windows.h>


 
int main(void)
{
	char buf[64] = {'\0'};
	int n_read;
	wiringPiSetup();    //调用此函数来进行初始化工作。
	
	int fd =serialOpen("/dev/ttyAMA1",115200); //打开串口
	
	if(fork() == 0){
		while(1){
			memset(buf,0,sizeof(buf));
			n_read = read(fd,buf,sizeof(buf));
			if(n_read != 0){
				printf("data %dB:%s\n",n_read,buf); //子进程一直等待数据接收
			}	
		}
	}
    else{
			while(1){
				serialPrintf(fd,"hello world!!\n"); //每隔三秒发送一次hello world!!
				sleep(3);
			}
	}
 
 return 0;
}










