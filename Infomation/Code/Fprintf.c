/* ---------- Include ---------- */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
// #include <windows.h>
#include "GetInfo.h"


void main(void)
{
    FILE *fp;

    fp = fopen("/home/tsimen/Infomation/Message/text.txt","w");

    fprintf(fp,"aaaaaa\r\n0798676");
    fclose(fp);
}