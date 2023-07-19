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
#include "wiringPi.h"
#include "wiringSerial.h"
#include "ReadParameters.h"
// #include <windows.h>

/* ---------- Define ---------- */
#define COD "COD"
#define BOD "BOD"
#define TOC "TOC"
#define TUR "TUR"
#define NH3 "NH3-N"
#define NO2 "NO2"
#define NO3 "NO3"
#define TP "TP"
#define TN "TN"
#define MACH "MACHs"
#define PHNEOL "PHNEOL"

/* ---------- Variable ---------- */
char AnalogOutput01[] = {0x01,0x06,     0x00,0x00,      0x01,0x90,0xD9,0xF6};
char AnalogOutput02[] = {0x01,0x06,     0x00,0x01,      0x01,0x90,0xD9,0xF6};
char AnalogOutput03[] = {0x01,0x06,     0x00,0x02,      0x01,0x90,0xD9,0xF6};
char AnalogOutput02[] = {0x01,0x06,     0x00,0x03,      0x01,0x90,0xD9,0xF6};







int main (void)
{

    ReadParameter(COD);

    printf("参数读取成功...\n");
    sleep(1);

    Exportwater(COD);
    printf("Done...\n");


    

    return 0;
}


























































