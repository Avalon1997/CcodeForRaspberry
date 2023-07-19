/* --------------------------------------------------------------------------------------------------------- */
/**
 * @file Yangtse_main.c
 * @author Avalon1997 (https://github.com/Avalon1997)
 * @brief Yangtse EVA analog output code
 * @version 1.0
 * @date 2023-03-23
 * 
 * @copyright Copyright (c) Avalon1997
 * 
 */
/* --------------------------------------------------------------------------------------------------------- */


/* ---------- Include ---------- */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include "wiringPi.h"
#include "wiringSerial.h"

/* ---------- Define ---------- */
#define max_line 1024

/* ---------- Variable ---------- */
char data[max_line] ;
char Waterdata_COD[] = {0x01,0x06,0x00,0x01,0x01,0x90,0xD9,0xF6};
char analog_config[] = {0x01,0x06,0x00,0x04,0x00,0x01,0x09,0xCB};
char Waterdata_CODtest[] = {0x01,0x06,0x00,0x01,0x03,0xE8,0xD8,0xB4};
double x;
int y,i = 0;
char transbuf[] = {0x00,0x00};
char transbuf1[] = {0x00,0x00};
unsigned short int CRC16 = 0;

/**
 * @brief 
 * 
 */
int IntToHex(int a,unsigned char *hex)
{   i = 0;
    while (a)
    {
        if (a % 16 >= 10)
            hex[i] = a % 16 + 55;
        else
            hex[i] = a % 16 + 48;
        i++;
        a = a / 16;
    }
}

/**
 * @brief 
 * 
 */
int DecToHex(int dec, unsigned char *hex, int length) 
{ 
    
	for(int i=length-1; i>=0; i--) 
	{ 
		hex[i] = (dec%256)&0xFF; 
		dec /= 256; 
	} 
	
	return 0; 
} 


/* ---------------------------------------------------------------------- Tool Function -------------------------------------------------------------------------- */
/**
 * @brief CRC16 check code. The function is used for data verification when communicating with PC.
 *  
 * @param pdata 
 * @param len 
 * @return uint16_t 
 */
unsigned short int ModBus_CRC16( unsigned char *pdata, int len)     //polynomial: 8005
{
    int CRC_i=0,CRC_j=0;
    unsigned short int crc = 0xFFFF;

    for ( CRC_j=0; CRC_j<len;CRC_j++)
    {
    // printf("%d",crc);
    // HAL_Delay(20);
    crc=crc^pdata[CRC_j];
    for ( CRC_i=0; CRC_i<8; CRC_i++)
    {
        if( ( crc&0x0001) >0)
        {
        crc=crc>>1;
        crc=crc^ 0xA001;                            //We take 8005 in reverse.
        }
    else
    crc=crc>>1;
    }
    }
    return crc;
}


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
	// serialPrintf(fd,"%s \n",data);
    x = atof(data);
    y = (int)x+400;
    // serialPrintf(fd,"%.6f \n",x);
    // serialPuts(fd,Waterdata_COD);
    // serialPrintf(fd,"%s",Waterdata_COD);
    printf("转换数值格式... 双精度数值为:%f... 整数数值为:%d\n",x,y);

    

    // IntToHex(y,transbuf);

    // serialPutchar(fd,transbuf[0]);
    // serialPutchar(fd,transbuf[1]);

    // memv(Waterdata_COD,transbuf,5,1,2);

    // CRC16 = ModBus_CRC16(Waterdata_COD,6);
    // Waterdata_COD[6]=(unsigned char)CRC16&0xFF;
    // Waterdata_COD[7]=(unsigned char)(CRC16>>8)&0xFF;

    // sleep(1);

    // printf("初始化模拟量模块...\n");
    // for (i=0;i<sizeof(analog_config);i++)
    // {
    //     serialPutchar(fd,analog_config[i]);
    // }



    // sleep(1);

    // printf("发送数值...\n");
    // for (i=0;i<sizeof(Waterdata_COD);i++)
    // {
    //     serialPutchar(fd,Waterdata_COD[i]);
    // }

    //---------------------------------
    printf("另一种方式...");
    DecToHex(y,transbuf1,2);
    serialPutchar(fd,transbuf1[0]);
    serialPutchar(fd,transbuf1[1]);
    memv(Waterdata_COD,transbuf1,5,1,2);

    CRC16 = ModBus_CRC16(Waterdata_COD,6);
    Waterdata_COD[6]=(unsigned char)CRC16&0xFF;
    Waterdata_COD[7]=(unsigned char)(CRC16>>8)&0xFF;
    sleep(1);

    printf("初始化模拟量模块...\n");
    for (i=0;i<sizeof(analog_config);i++)
    {
        serialPutchar(fd,analog_config[i]);
    }



    sleep(1);

    printf("发送数值...\n");
    for (i=0;i<sizeof(Waterdata_COD);i++)
    {
        serialPutchar(fd,Waterdata_COD[i]);
    }
    
    //--------------------------------------
    sleep(1);
    printf("发送完成...\n");


	serialClose(fd);
}
/* --------------------------------------------------------------------------------------------------------- */

int main (void)
{
    ReadParameter("COD");

    printf("参数读取成功...\n");
    sleep(1);

    Exportwater("COD");
    printf("Done...\n");


    

    return 0;
}











