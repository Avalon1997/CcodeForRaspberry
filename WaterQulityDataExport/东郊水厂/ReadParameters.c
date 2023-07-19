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
#include "main.h"
#include "wiringPi.h"
#include "wiringSerial.h"
// #include <windows.h>

/* ---------- Define ---------- */
#define max_line 1024


/* ---------- Variable ---------- */
char AnalogOutput01[] = {0x01,0x06,0x00,0x00,0x01,0x90,0xD9,0xF6};
char AnalogOutput02[] = {0x01,0x06,0x00,0x01,0x01,0x90,0xD9,0xF6};
char AnalogOutput03[] = {0x01,0x06,0x00,0x02,0x01,0x90,0xD9,0xF6};
char AnalogOutput04[] = {0x01,0x06,0x00,0x03,0x01,0x90,0xD9,0xF6};
char data[max_line] ;
char buffer[10] ; 
double DataFloat;
int DataInt,i;
unsigned short int CRC16 = 0;

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



/**
 * @brief 
 * 
 */
void DecToHex(int dec, unsigned char *hex, int length) 
{ 
    
	for(int i=length-1; i>=0; i--) 
	{ 
		hex[i] = (dec%256)&0xFF; 
		dec /= 256; 
	} 
	
	// return 0; 
} 

/**
 * @brief 
 * 
 * @param aa 
 */
void inttohex(int aa)
{
    static int i = 0;
    if (aa < 16)            //递归结束条件 
    {
        if (aa < 10)        //当前数转换成字符放入字符串 
            buffer[i] = aa + '0';
        else
            buffer[i] = aa - 10 + 'A';
        buffer[i+1] = '\0'; //字符串结束标志 
    }
    else
    {
        inttohex(aa / 16);  //递归调用 
        i++;                //字符串索引+1 
        aa %= 16;           //计算当前值
        if (aa < 10)        //当前数转换成字符放入字符串 
            buffer[i] = aa + '0';
        else
            buffer[i] = aa - 10 + 'A';
    }
}


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
            else if (strncmp(databuffer,name,2) == NULL )
            {
                memv(data,databuffer,1,4,len - 4);
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
	// fd =serialOpen("/dev/ttyAMA1",115200); //打开串口
	fd =serialOpen("/dev/ttyAMA1",9600); //打开串口
    sleep(1);
    printf("串口初始化完成...\n");

    sleep(1);
    printf("发送 %s 水质参数...\n",name);
    sleep(1);

    /*---------- Send the Data ----------*/
	// serialPrintf(fd,"%s \n\r",data);


    // ---------- COD transform ----------
    if(memcmp(name,COD,sizeof(COD)) == 0)
    {
        printf("进行进制转换，并发送485模块指令：...\r\n");
        DataFloat = atof(data);

        if (DataFloat < 1600)
        {
            DataInt = (int)DataFloat+400;
        }
        else if (DataFloat > 1600)
        {
            DataInt = 1600;
        }

        printf("数值转换中... 双精度为：%f... 整数为：%d\r\n",DataFloat,DataInt);
        DecToHex(DataInt,buffer,2);
        memv(AnalogOutput01,buffer,5,1,2);

        CRC16 = ModBus_CRC16(AnalogOutput01,6);
        AnalogOutput01[6] = (unsigned char)CRC16&0xFF;
        AnalogOutput01[7] = (unsigned char)(CRC16>>8)&0xFF;
        sleep(1);

        for (i=0;i<sizeof(AnalogOutput01);i++)  
        {
            serialPutchar(fd,AnalogOutput01[i]);
        }
        memset(data,0,sizeof(data));
    }

   // ---------- BOD transform ----------
    else if (memcmp(name,BOD,sizeof(BOD)) == 0)
    {
        printf("进行进制转换，并发送485模块指令：...\r\n");
        DataFloat = atof(data);
        if (DataFloat < 1600)
        {
            DataInt = (int)DataFloat+400;
        }
        else if (DataFloat > 1600)
        {
            DataInt = 1600;
        }

        printf("数值转换中... 双精度为：%f... 整数为：%d\r\n",DataFloat,DataInt);
        DecToHex(DataInt,buffer,2);
        memv(AnalogOutput02,buffer,5,1,2);

        CRC16 = ModBus_CRC16(AnalogOutput02,6);
        AnalogOutput02[6] = (unsigned char)CRC16&0xFF;
        AnalogOutput02[7] = (unsigned char)(CRC16>>8)&0xFF;
        sleep(1);

        for (i=0;i<sizeof(AnalogOutput02);i++)  
        {
            serialPutchar(fd,AnalogOutput02[i]);
        }
        memset(data,0,sizeof(data));
    }

   // ---------- TP transform ----------
    else if (memcmp(name,TP,sizeof(TP)) == 0)
    {
        printf("进行进制转换，并发送485模块指令：...\r\n");
        DataFloat = atof(data);
        if (DataFloat < 16)
        {
            DataInt = (int)(DataFloat * 100)+400;
        }
        else if (DataFloat > 16)
        {
            DataInt = 1600;
        }

        printf("数值转换中... 双精度为：%f... 乘100后+400为：%d\r\n",DataFloat,DataInt);
        DecToHex(DataInt,buffer,2);
        memv(AnalogOutput03,buffer,5,1,2);

        CRC16 = ModBus_CRC16(AnalogOutput03,6);
        AnalogOutput03[6] = (unsigned char)CRC16&0xFF;
        AnalogOutput03[7] = (unsigned char)(CRC16>>8)&0xFF;
        sleep(1);

        for (i=0;i<sizeof(AnalogOutput03);i++)  
        {
            serialPutchar(fd,AnalogOutput03[i]);
        }
        memset(data,0,sizeof(data));
    }

   // ---------- TN transform ----------
    else if (memcmp(name,TN,sizeof(TN)) == 0)
    {
        printf("进行进制转换，并发送485模块指令：...\r\n");
        DataFloat = atof(data);
        if (DataFloat < 160)
        {
            DataInt = (int)(DataFloat * 10)+400;
        }
        else if (DataFloat > 160)
        {
            DataInt = 1600;
        }

        printf("数值转换中... 双精度为：%f... 乘100后+400为：%d\r\n",DataFloat,DataInt);
        DecToHex(DataInt,buffer,2);
        memv(AnalogOutput04,buffer,5,1,2);
        
        CRC16 = ModBus_CRC16(AnalogOutput04,6);
        AnalogOutput04[6] = (unsigned char)CRC16&0xFF;
        AnalogOutput04[7] = (unsigned char)(CRC16>>8)&0xFF;
        sleep(1);

        for (i=0;i<sizeof(AnalogOutput04);i++)  
        {
            serialPutchar(fd,AnalogOutput04[i]);
        }
        memset(data,0,sizeof(data));
    }




    sleep(1);
    printf("发送完成...\n");


	serialClose(fd);
}




















