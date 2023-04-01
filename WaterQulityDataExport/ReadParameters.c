/* --------------------------------------------------------------------------------------------------------- */
/**
 * @file ReadParameters.c
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
#include <unistd.h>
#include <string.h>
#include "wiringPi.h"
#include "wiringSerial.h"
// #include <windows.h>

/* ---------- Define ---------- */
#define max_line 1024


/* ---------- Variable ---------- */
char data[max_line] ;



/* --------------------------------------------------------------------------------------------------------- */
/**
 * @brief Cut a specific length from the A array to the B array.
 * 
 * @param pdata target array
 * @param ppdata truncated array
 * @param st1 start bit of the destination array
 * @param st2 start bit of truncated array
 * @param length The length of the truncated array
 */
void memv(unsigned char *pdata,unsigned char *ppdata,int st1,int st2,int length)
{
    int memv_i = 0;
    for (memv_i=0;memv_i<length;memv_i++)
    {
    pdata[memv_i+st1-1] = ppdata[memv_i+st2-1];
    }
}
/* --------------------------------------------------------------------------------------------------------- */



/* --------------------------------------------------------------------------------------------------------- */
/**
 * @brief Read the water parameter
 * 
 * @param name Need to input the parameter name
 * @return int 
 */
int ReadParameter(char *name)
{
    FILE *fp;                   //文件指针
    int len,i;                    //行字符个数
    char databuffer[max_line];  // 缓冲区

    if ( (fp = fopen("WaterData.txt","r")) == NULL)
    {
        perror("Fail to read:");
        exit(1);
    }

    // for (i=0;i<11;i++)
    // {
    //     if (fgets(databuffer,max_line,fp) != NULL)
    //     {
    //         len = strlen(databuffer);
    //         databuffer[len - 1] = '\0';
    //         printf("这一行内容是：%s\n",databuffer);
    //         printf("整行长度：%d \n",(len - 1));
    //         if (strncmp(databuffer,name,sizeof(name)) == NULL )
    //         {
    //             memv(data,databuffer,1,5,5);
    //             fclose(fp);
    //             return 1;
    //         } 
    //     }
    // }

    

        while(fgets(databuffer,max_line,fp) != NULL)
        {
            len = strlen(databuffer);
            databuffer[len - 1] = '\0';
            printf("这一行内容是：%s\n",databuffer);
            printf("整行长度：%d \n",(len - 1));
            if (strncmp(databuffer,name,3) == NULL )
            {
                memv(data,databuffer,1,5,len - 5);
                printf("data 中数据为：%s \n",data);
                fclose(fp);
                return 1;
            } 
        }


    fclose(fp);
    return 0;
}
/* --------------------------------------------------------------------------------------------------------- */

void Exportwater(char *name)
{
	int fd;
    printf("串口初始化...\n");
	wiringPiSetup();    //调用此函数来进行初始化工作。
	fd =serialOpen("/dev/ttyAMA1",115200); //打开串口
    sleep(1);
    printf("串口初始化完成...\n");

    sleep(1);
    printf("发送 %s 水质参数...\n",name);
    sleep(1);

    /*---------- Send the Data ----------*/
	serialPrintf(fd,"%s \n",data);

    sleep(1);
    printf("发送完成...\n");


	serialClose(fd);
}


















