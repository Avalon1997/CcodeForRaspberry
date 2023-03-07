/* --------------------------------------------------------------------------------------------------------- */
/**
 * @file GetInfo.c
 * @author Avalon1997 (https://github.com/Avalon1997)
 * @brief In order to record some necessary information, this program is written for use by field engineers.
 * @version 1.0
 * @date 2022-07-29
 * 
 * @copyright Copyright (c) Avalon1997
 * 
 */
/* --------------------------------------------------------------------------------------------------------- */

/* ---------- Include ---------- */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
// #include <windows.h>
#include "GetInfo.h"

/* ---------- Variable Define ---------- */
FILE *fp;
char filename[200];
char str[200];
char path[] ="/home/tsimen/Infomation/Message/";
char timestr[9] = {0};
char buff[8] = {0};
int i, j;
time_t  current_time;

/* ---------- Main Function ---------- */
void main(void) 
{
    system("clear");    // Clear the screen
    Get_Time();     // Get the current date
    Get_Path(timestr,8);    // Write the path of message.txt

    // printf("                      ██████ ▓█████ ▓█████ ▓█████▄  \r\n");
    // printf("                    ▒██    ▒ ▓█   ▀ ▓█   ▀ ▒██▀ ██▌ \r\n");
    // printf("                    ░ ▓██▄   ▒███   ▒███   ░██   █▌ \r\n");
    // printf("                      ▒   ██▒▒▓█  ▄ ▒▓█  ▄ ░██▄   ▌ \r\n");
    // printf("                    ▒██████▒▒░▒████▒░▒████▒░█████▓  \r\n");
    // printf("                    ▒ ▒▓▒ ▒ ░░░ ▒░ ░░░ ▒░ ░ ▒▒▓  ▒  \r\n");
    // printf("                    ░ ░▒  ░ ░ ░ ░  ░ ░ ░  ░ ░ ▒  ▒  \r\n");
    // printf("                    ░  ░  ░     ░      ░    ░ ░  ░  \r\n");
    // printf("                          ░     ░  ░   ░  ░   ░     \r\n");
    // printf("                                            ░       \r\n");
    printf("***************************************************************************\r\n\r\n");
    printf("                 ______     ________    ________    _______    \r\n");
    printf("                /      \\   /          |/          |/       \\   \r\n");
    printf("               /$$$$$$  |  $$$$$$$$/   $$$$$$$$/   $$$$$$$  |  \r\n");
    printf("               $$ \\__$$/   $$ |__      $$ |__      $$ |  $$ |  \r\n");
    printf("               $$      \\   $$    |     $$    |     $$ |  $$ |  \r\n");
    printf("                $$$$$$  |  $$$$$/      $$$$$/      $$ |  $$ |  \r\n");
    printf("               /  \\__$$   |$$ |_____   $$ |_____   $$ |__$$ |  \r\n");
    printf("               $$    $$/   $$       |  $$       |  $$    $$/   \r\n");
    printf("                $$$$$$/    $$$$$$$$/   $$$$$$$$/   $$$$$$$/    \r\n\r\n");
    printf("                                                        计蒙操作信息记录\r\n");
    printf("****************************************************************************\r\n\r\n");
    sleep(1);
    printf("                            请输入如下罗列信息\r\n\r\n");
    sleep(1);


    // ----- Write the message in the txt ----- //
    fprintf(fp,"***********************************************************************\r\n\r\n");
    fprintf(fp,"             ______     ________    ________    _______    \r\n");
    fprintf(fp,"            /      \\   /          |/          |/       \\   \r\n");
    fprintf(fp,"           /$$$$$$  |  $$$$$$$$/   $$$$$$$$/   $$$$$$$  |  \r\n");
    fprintf(fp,"           $$ \\__$$/   $$ |__      $$ |__      $$ |  $$ |  \r\n");
    fprintf(fp,"           $$      \\   $$    |     $$    |     $$ |  $$ |  \r\n");
    fprintf(fp,"            $$$$$$  |  $$$$$/      $$$$$/      $$ |  $$ |  \r\n");
    fprintf(fp,"           /  \\__$$   |$$ |_____   $$ |_____   $$ |__$$ |  \r\n");
    fprintf(fp,"           $$    $$/   $$       |  $$       |  $$    $$/   \r\n");
    fprintf(fp,"            $$$$$$/    $$$$$$$$/   $$$$$$$$/   $$$$$$$/    \r\n\r\n");
    fprintf(fp,"                                                    计蒙操作信息记录\r\n");
    fprintf(fp,"************************************************************************\r\n");
    
    // ----- write name ----- //
	fprintf(fp,"安装人姓名：");
	printf("请输入您的姓名：");
    fgets(str,sizeof(str),stdin);
    for(j=0;str[j]!='\n';j++){
        fputc(str[j],fp);
    }
    fputc('\n',fp);

    // ----- write phone ----- //
	fprintf(fp,"安装人联系方式：");
	printf("请输入您的联系方式（手机号）：");
    fgets(str,sizeof(str),stdin);
    for(j=0;str[j]!='\n';j++){
        fputc(str[j],fp);
    }
    fputc('\n',fp);

    // ----- write place ----- //
	fprintf(fp,"安装地点：");
	printf("请输入您安装的地点：");
    fgets(str,sizeof(str),stdin);
    for(j=0;str[j]!='\n';j++){
        fputc(str[j],fp);
    }
    fputc('\n',fp);

    // ----- write time ----- //
	fprintf(fp,"安装时间：");
	printf("请输入安装时间（格式：xxxx-xx-xx）：");
    fgets(str,sizeof(str),stdin);
    for(j=0;str[j]!='\n';j++){
        fputc(str[j],fp);
    }
    fputc('\n',fp);

    // ----- write ID ----- //
	fprintf(fp,"设备ID号：");
	printf("请输入计蒙设备ID号：");
    fgets(str,sizeof(str),stdin);
    for(j=0;str[j]!='\n';j++){
        fputc(str[j],fp);
    }
    fputc('\n',fp);

    // ----- write status ----- //
	fprintf(fp,"传感器设备情况：");
	printf("请输入传感器设备情况(稳定/不稳定)：");
    fgets(str,sizeof(str),stdin);
    for(j=0;str[j]!='\n';j++){
        fputc(str[j],fp);
    }
    fputc('\n',fp);
    fprintf(fp," -稳定 -不稳定\r\n");

    // // ----- write ID ----- //
	// fprintf(fp,"传感器设备情况：");
	// printf("请输入传感器设备情况：");
    // fgets(str,sizeof(str),stdin);
    // for(j=0;str[j]!='\n';j++){
    //     fputc(str[j],fp);
    // }
    // fputc('\n',fp);
    // fprintf(fp," -稳定 -不稳定\r\n");



    fclose(fp);                
    printf("你输入的信息成功保存，感谢使用！！！\r\n");
    sleep(1);
    printf("程序将在5秒中后自动关闭...\r\n");
    for (i=5;i>0;i--)
    {
        printf("%d...\r\n",i);
        sleep(1);
    }


}

/**
 * @brief Get the message.txt path
 * 
 * @param p 
 * @param a 
 * @return int 
 */
int Get_Path(char *p,int a)
{
    // memcpy(buff,timestr,8);
    // strcat(path,buff);
    strcat(path,"Message.txt");

    fp = fopen(path,"w");

}

/**
 * @brief Get the current date
 * 
 */
void Get_Time(void)
{
    current_time = time(NULL);
    // printf("current_time = %d\r\n",current_time);

    strftime(timestr,sizeof(timestr),"%Y%m%d",localtime(&current_time));
    // printf("now the real time is : %s\r\n",timestr);

    // for (i=0;i<sizeof(timestr);i++)
    // {
    //     printf("%c \r\n",timestr[i]);
    // }

}
