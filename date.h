////////////////////////////////////////
//                                    //
// LibManage                          //
// Library Management Sytem           //
//                                    //
// Copyright (c) 2007 Kartik Singhal. //
// kartiksinghal@gmail.com            //
// All rights reserved.               //
//                                    //
////////////////////////////////////////


#include <ctime>
#include <iostream>
#include <string>

using namespace std;

//////////////////////////////////////
//          The Date Class          //
//////////////////////////////////////
class Date                  //28 bytes
{
private:                       
	int day, month, year;
	char nameOfMonth[15];
	void giveNameOfMonth();
public:                        
	Date(void);
	Date(int);
	void printDate(void);
	void extendDate(int);
	int diff(Date);
	int returnDay(void)
	{
		return day;
	}
	int returnMonth(void)
	{
		return month;
	}
	int returnYear(void)
	{
		return year;
	}
}; //Date class ends

// Constructor to initialize date to current system time
Date::Date(void)
{   
	///////////////////////////////////////////////////////////////////////////
	struct tm *ptr;                       //                                 //
	time_t sec;                           //                                 //
	time(&sec);                           //Thanks to http://java2s.com for  //
	ptr = localtime(&sec);                //                                 //
	                                      //particularly this piece of code  //
	month = (int) ptr->tm_mon + 1;        //                                 //
	day   = (int) ptr->tm_mday;           //to generate current system time. //
	year  = (int) ptr->tm_year + 1900;    //                                 //
	///////////////////////////////////////////////////////////////////////////

	giveNameOfMonth();
} //End Date(void)

// Constructor to initialize date to zeroes
Date::Date(int d)
{
	day = month = year = 0;
} //End Date(int)

// Function to assign name of the month for particular month
void Date::giveNameOfMonth()
{
	switch (month)
	{
	case 1:
		strcpy(nameOfMonth,"January");
		break;
	case 2:
		strcpy(nameOfMonth,"February");
		break;
	case 3:
		strcpy(nameOfMonth,"March");
		break;
	case 4:
		strcpy(nameOfMonth,"April");
		break;
	case 5:
		strcpy(nameOfMonth,"May");
		break;
	case 6:
		strcpy(nameOfMonth,"June");
		break;
	case 7:
		strcpy(nameOfMonth,"July");
		break;
	case 8:
		strcpy(nameOfMonth,"August");
		break;
	case 9:
		strcpy(nameOfMonth,"September");
		break;
	case 10:
		strcpy(nameOfMonth,"October");
		break;
	case 11:
		strcpy(nameOfMonth,"November");
		break;
	case 12:
		strcpy(nameOfMonth,"December");
		break;
	}
} //End giveNameOfMonth()

// To print date in a specialized manner
void Date::printDate(void)
{
	cout << nameOfMonth << " " << day << ", " <<year;
} //End printDate()

// To extend current date by given no. of days
void Date::extendDate(int days)
{
	static int monthNum[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	for(int i=1; i<=days; i++)
	{
		day++;
		if( (day > monthNum[month-1]) || (year%4 != 0 && month==2 && day>28) )
		{
			day = 1;
			month++;
		}
		if(month > 12)
		{
			month = 1;
			year++;
		}
	}

	giveNameOfMonth();

} //End extendDate()

// Returns the no. of days between the provided date and current date
int Date::diff(Date ret)
{
	int d = ret.returnDay(), m = ret.returnMonth(), y = ret.returnYear();
	int days=0;
	if( (year < y) || (year==y && month<m) 
		|| (year==y && month==m && day<d) )
		return days;
	static int month_days[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	while( d != (int)day || m != (int)month || y != (int)year )
	{
		days++;
		d++;
		if( (d > month_days[m-1]) 
			|| (y%4 != 0 && m==2 && d>28) )
		{
			d = 1;
			m++;
		}
		if(m > 12)
		{
			m = 1;
			y++;
		}
	}
	return days;
} //End diff()

//////////////////////////////////////////
//                                      //
//   THE END                            //
//                                      //
//////////////////////////////////////////
