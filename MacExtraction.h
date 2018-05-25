#pragma once
#include<stdio.h>
#include<stdlib.h>



//this function returns the current count of users connected to a router
//this function also clears the arp cache so the next time a fresh count is created (not containing previous )
int getCount()
{
	system("arp -a > in.txt");

	//count - used to keep track of "Interface" string in the arp result file
	//linecount - counts the number of mac addresses under "Interface" 3
	int count = 0, linecount = 0;


	char* buff = (char*)malloc(sizeof(char) * 100);

	FILE* fp = fopen("in.txt", "r");


	while (fgets(buff, 100, fp) != 0)
	{
	    if (buff[0] == 'I')
			count++;

		if (count >= 2)
		{
		    printf("debug\n\n");
			linecount++;
		}
	}

	system("netsh interface ip delete arpcache");

	if (linecount <= 2)
    {
        return 0;
    }
	return linecount - 2;
}


