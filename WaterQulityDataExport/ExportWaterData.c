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
#include <stdlib.h>
#include "wiringPi.h"
#include "wiringSerial.h"
#include <unistd.h>
#include <string.h>
// #include <windows.h>


 
int main(void)
{
	int fd;
	char cmd;


	wiringPiSetup();    //调用此函数来进行初始化工作。

	
	fd =serialOpen("/dev/ttyAMA1",115200); //打开串口

	printf("working ... \n");
	serialPrintf(fd,"hello world!!! \n");
	sleep(3);
	printf("sleep 3 second... \n");


	serialClose(fd);

	return 0;
}














