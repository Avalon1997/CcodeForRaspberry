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
#include <unistd.h>
#include <string.h>
// #include <windows.h>

int ReadParameter(char *name)
{
    FILE *fp;
    int size = 0;
    char databuffer[200];


    fp = fopen("WaterData.txt","r");
    
    fread(databuffer,18,1,fp);
    printf("这是txt中内容：%s",databuffer);

    fclose(fp);

    return 0;




}








