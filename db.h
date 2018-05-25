#pragma once
#include "MacExtraction.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>

using namespace std;

void updateDB()
{
    int hour = (time(NULL)/60 + 6)%24;
    FILE* fp = fopen("count.DB", "r");
    int Data[24]= {0};
    for(int i=0; i<24; i++)
    {
        fscanf(fp,"%d",&Data[i]);
    }
    fclose(fp);
    Data[hour] = (getCount()+Data[hour])/2;
    fp = fopen("count.DB", "w");
    for(int i=0; i<24; i++)
    {
        fprintf(fp, "%d\n", Data[i]);
    }
    fclose(fp);
    return;
}

int* getData()
{
    time_t seconds = time(NULL);
    int hour = (seconds/60 + 6)%24;
    FILE* fp = fopen("count.DB", "r");
    int * Data = (int *)malloc(24*sizeof(int));
    for(int i=0; i<24; i++)
    {
        fscanf(fp,"%d",&Data[i]);
    }
    fclose(fp);

    return Data;
}


char * currentDate() {
    time_t t = time(0);   // get time now
    tm* now = localtime(&t);
    char * buf = (char *)malloc(80*sizeof(char));
    sprintf(buf, "%d:%d:%d", (now->tm_year + 1900), (now->tm_mon + 1), now->tm_mday);
    return buf;
}

void addLog(char *name, int price, int statTime, int endTime)
{
    system("cls");
    string n(name);
    _getch();
    currentDate();
    char *cd = currentDate();
    FILE* fp = fopen("logs.db", "a+");
    time_t seconds = time(NULL);
    fprintf(fp, "%s %d %s %d %d\n", name, price, cd, statTime, endTime); // name, price, date, start time, end time.
    fclose(fp);
}

void showLogs()
{

    FILE* fp = fopen("logs.db", "r");
    char buf[100];
    while(fgets(buf, 100, fp))
    {
        printf("%s\n",buf);
    }
    fclose(fp);
}
