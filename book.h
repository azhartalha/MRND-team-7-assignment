#pragma once
#include "Availability.h"
#include "db.h"
#include "UI.h"
#include<iostream>
#include<fstream>
#include<time.h>

using namespace std;

void book();

int *price() {
    return getData();
}

int validateDebitCard(char* debitCard, char* name)
{
    _getch();
	if (strlen(debitCard) == 16)
	{
		for (int iter = 0; iter < strlen(debitCard); iter++)
		{
			if (!(debitCard[iter] >= '0'  && debitCard[iter] <= '9'))
				return 0;
		}
		return 1;
	}

	return 0;
}

int isFreeSlot(int st,int et)
{
    int i;
    if(st<=et)
    {
        for(i=st;i<et;i++)
            if (getAvailability(i))
            {
                break;
            }
    }
    else
    {
        int flag=1;
        for(i=st;i<24;i++)
            if (getAvailability(i))
            {
                flag=0;
                break;
            }
        for(i=0;flag&&i<et;i++)
        {
            if (getAvailability(i))
            {
                break;
            }
        }
    }
    return i==et;

}

void book()
{

	//priceFactor - factor to be multiplied with count to get price
	int PRICE_FACTOR = 10;


	print_free_slot(getAvailableSlots());

	int st, et;
	cout << endl << "Enter ur time slot in 24 hour format:\n";
	cout << "Enter Starting Time:\n";
	cin >> st;
	cout << "Enter Ending Time:\n";
	cin >> et;
	int i;
	if (isFreeSlot(st,et))
	{
	    int total_price = 0;
		int *priceArr;// = (int *)malloc(sizeof(int) * 24);
	    priceArr = price();
	    if(st<=et)
		for (i = st; i < et; i++) {
            total_price += priceArr[i];
		}
		else
        {
            for(i=st;i<24;i++)
            total_price += priceArr[i];
            for(i=0;i<et;i++)
            total_price += priceArr[i];
        }
        int price = total_price*PRICE_FACTOR;
        if(price < 30)
            price = 30;
		cout << "Cost for your requested slot is " <<price<< "\n";




		char** debitInfo = payment_page(price);

		int status = validateDebitCard(debitInfo[1], debitInfo[0]);
		payment_status(status);
		if (status)
		{
			addLog(debitInfo[0], total_price*PRICE_FACTOR, st, et);
			/*for (i = st; i < et; i++)
                setAvailability(i, 1);*/

            if(st<=et)
		    for (i = st; i < et; i++) {
                setAvailability(i, 1);
            }
            else
            {
                for(i=st;i<24;i++)
                    setAvailability(i, 1);
                for(i=0;i<et;i++)
                    setAvailability(i, 1);
            }

			cout << "The requested slot is successfully booked\n";
		}
	}
	else
	{
		cout << "The requested slot is already booked\n\n";
        _getch();
	}
}



