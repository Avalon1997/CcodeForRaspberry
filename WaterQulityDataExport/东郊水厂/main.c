/* --------------------------------------------------------------------------------------------------------- */
/**
 * @file main.c
 * @author Avalon1997 (https://github.com/Avalon1997)
 * @brief Program Entry
 * @version 1.0
 * @date 2023-03-22
 * 
 * @copyright Copyright (c) Avalon1997
 * 
 */
/* --------------------------------------------------------------------------------------------------------- */


/* ---------- Include ---------- */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "main.h"
#include "wiringPi.h"
#include "wiringSerial.h"
#include "ReadParameters.h"
// #include <windows.h>

/* ---------- Variable ---------- */
// char AnalogOutput01[] = {0x01,0x06,0x00,0x00,0x01,0x90,0xD9,0xF6};
// char AnalogOutput02[] = {0x01,0x06,0x00,0x01,0x01,0x90,0xD9,0xF6};
// char AnalogOutput03[] = {0x01,0x06,0x00,0x02,0x01,0x90,0xD9,0xF6};
// char AnalogOutput04[] = {0x01,0x06,0x00,0x03,0x01,0x90,0xD9,0xF6};





int main (void)
{
    printf("软件初始化...\r\n");

    sleep(1);
    printf("读取 COD 水质参数值...\r\n");
    ReadParameter(COD);
    printf("传输 COD 水质参数值...\r\n");
    sleep(1);
    Exportwater(COD);

    printf("--------------------");

    sleep(1);
    printf("读取 BOD 水质参数值...\r\n");
    ReadParameter(BOD);
    sleep(1);
    printf("传输 BOD 水质参数值...\r\n");
    Exportwater(BOD);

    sleep(1);
    printf("读取 TP 水质参数值...\r\n");
    ReadParameter(TP);
    sleep(1);
    printf("传输 TP 水质参数值...\r\n");
    Exportwater(TP);

    sleep(1);
    printf("读取 TN 水质参数值...\r\n");
    ReadParameter(TN);
    sleep(1);
    printf("传输 TN 水质参数值...\r\n");
    Exportwater(TN);


    

    return 0;
}


























































