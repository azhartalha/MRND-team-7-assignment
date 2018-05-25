#pragma once
#include<stdio.h>
#include<stdlib.h>

int getAvailability(int time)
{
	if (time < 0 || time > 23)
		return -1;

	FILE* fp = fopen("availability.db", "r");

	int tp;
	int avail;
	while (!feof(fp))
	{
		fscanf(fp, "%d %d\n", &tp, &avail);
		if (tp == time)
		{
			return avail;
		}
	}
	fclose(fp);
}

void setAvailability(int time, int available)
{
	if (time < 0 || time > 23)
	{
		printf("Invalid Time");

	}
	FILE* fp = fopen("availability.db", "r+");

	fpos_t pos;
	int tp;
	int avail;
	while (!feof(fp))
	{
		fgetpos(fp,&pos);
		fscanf(fp, "%d %d\n", &tp, &avail);
		if (tp == time)
		{
			fsetpos(fp, &pos);
			fprintf(fp, "%d %d\n", tp, available);
			fclose(fp);
			return;
		}
	}

}

void resetAvailability(int time)
{
	setAvailability(time, 0);
}

int* getAvailableSlots()
{
    printf("Debug\n");

	FILE* fp = fopen("availability.db", "r");

	int* data = (int*)malloc(sizeof(int) * 24);

	int val;
	int i = 0;
	while (!feof(fp))
	{
		fscanf(fp,"%*d %d\n", &val);
		data[i++] = val;
	}
	fclose(fp);
    return data;
}
