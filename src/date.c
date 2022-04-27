#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/date.h"
#include "../include/utils.h"

Date dateCreate(int day, int month, int year)
{
	Date date;
	if (verifyDateFail(day, month, year))
	{
		date.day = 0;
		date.month = 0;
		date.year = 0;
	}
	else
	{
		date.day = day;
		date.month = month;
		date.year = year;
	}
	return date;
}

Date toDate(char *str)
{
	Date date;
	if (str != NULL && strlen(str) > 0)
	{
		char *aux = (char *)calloc(11, sizeof(char));
		strcpy(aux, str);
		char **tokens = split(aux, 3, "/");
		date = dateCreate(atoi(tokens[0]), atoi(tokens[1]), atoi(tokens[2]));
		free(aux);
		free(tokens);
	}
	else
	{
		date = dateCreate(0, 0, 0);
	}

	return date;
}

char *toString(Date *date)
{
	char *string = (char *)calloc(11, sizeof(char));
	sprintf(string, "%02d/%02d/%02d", date->day, date->month, date->year);
	return string;
}

long int toNumber(Date *date)
{
	char *string = (char *)calloc(11, sizeof(char));
	sprintf(string, "%02d%02d%02d", date->year, date->month, date->day);
	long int number = atol(string);
	free(string);
	return number;
}

void datePrint(Date *date)
{
	printf("%02d/%02d/%02d", date->day, date->month, date->year);
}

bool dateIsEmpty(Date *date)
{
	if (date == NULL)
	{
		Date auxDate = dateCreate(0, 0, 0);
		return true;
	}
	return false;
}

bool verifyDateFail(int day, int month, int year)
{
	if (day <= 0 || day > 31 || month <= 0 || month > 12 || year <= 0)
	{
		return true;
	}
	return false;
}

time_t dateToTime(Date *date)
{
	struct tm timeStruct = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	if (date != NULL)
	{
		timeStruct.tm_year = date->year - 1900;
		timeStruct.tm_mon = date->month - 1;
		timeStruct.tm_mday = date->day;
	}
	time_t time = mktime(&timeStruct);
	return time;
}

int dayDifference(Date *oldDate, Date *recentDate)
{
	time_t time1 = dateToTime(recentDate);
	time_t time2 = dateToTime(oldDate);
	return ((int)(difftime(time1, time2) / (24 * 3600)));
}

bool dateCompare(Date d1, Date d2)
{
	if (!dateIsEmpty(&d1) && !dateIsEmpty(&d2))
	{
		if (d1.day == d2.day && d1.month == d2.month && d1.year == d2.year)
		{
			return true;
		}
		return false;
	}
	return false;
}

Date theDayBefore(Date *date)
{
	Date before = dateCreate(0, 0, 0);
	if (date != NULL)
	{
		time_t time1 = dateToTime(date);
		time1 -= (24 * 3600);
		struct tm *newTime = localtime(&time1);
		before.year = newTime->tm_year + 1900;
		before.month = newTime->tm_mon + 1;
		before.day = newTime->tm_mday;
	}
	return before;
}
