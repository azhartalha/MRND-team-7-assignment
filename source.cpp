#include "UI.h"
#include "Availability.h"
#include "book.h"
#include "db.h"
#include "MacExtraction.h"
#include<iostream>
#include<thread>
#include<cstdio>
using namespace std;

void DBinitialization()
{
    while(1)
    {
        this_thread::sleep_for(chrono::milliseconds(60000));
        updateDB();
        resetAvailability((time(NULL)/60 + 6)%24);
    }
}
void dataFetching()
{
    int op, tmp;
    while(1){
        op = main_menu(5, "Book a slot", "Rush hours" , "show logs", "Number of connected devices", "exit")+1;
        switch(op)
        {
        case 1:
            system("cls");
            book();
            break;
        case 2:
            print_graph(getData());
            break;
        case 3:
            system("cls");
            showLogs();
            _getch();
            break;
        case 4:
            system("cls");
            tmp = getCount();
            if(tmp>0)
                printf("\nThe current number of people connected are: %d\n", tmp);
            else
                printf("\nNo device is connected.\n");
            _getch();
            break;
        case 5:
            system("cls");
            exit(0);
        }
    }
    return;
}
void multiThreading()
{
    thread clinetSide(dataFetching);
    thread DBside(DBinitialization);
    clinetSide.join();
    DBside.join();
}
int main()
{
    system("netsh interface ip delete arpcache");
    multiThreading();
    return 0;
}
