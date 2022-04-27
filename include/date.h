#pragma once
#include <stdbool.h>
#include <time.h>

typedef struct date{
	unsigned int day, month, year;
} Date;

/**
 * @brief Creates a date instance
 *
 * @param day day
 * @param month month
 * @param year year
 * @return Date created date
 */
Date dateCreate(int day, int month, int year);

/**
 * @brief Changes string to date
 *
 * @param date date string
 * @return Date date created by string
 */
Date toDate(char *str);

/**
 * @brief changes date to string
 *
 * @param date date
 * @return char* string date
 */
char* toString(Date *date);
long int toNumber(Date *date);

/**
 * @brief Prints date information in dd/mm/yyy
 *
 * @param date date
 */
void datePrint(Date *date);

/**
 * @brief Verify if date is empty
 *
 * @param date date
 * @return true true if empty
 * @return false false if not empty
 */
bool dateIsEmpty(Date *date);

/**
 * @brief Verify if date information generates fails
 *
 * @param day day
 * @param month month
 * @param year year
 * @return true true if generates fail
 * @return false false if do not generates fail
 */
bool verifyDateFail(int day, int month, int year);
/**
 * @brief Converts a date structure into a time_t instance.
 *
 * @param date The inputted date.
 *
 * @return time_t instance.
 */
time_t dateToTime(Date *date);
/**
 * @brief Calculates the difference in days between two date instances.
 *
 * @param oldDate Oldest date to be calculate in difference to the recentDate.
 * @param recentDate Most recent date to be calculate in difference to the oldDate.
 *
 * @return Difference in days between the two dates.
 */
int dayDifference(Date *oldDate, Date *recentDate);

/**
 * @brief Compares two dates
 * 
 * @param d1 
 * @param d2 
 * @return true if the two dates are equal
 * @return false if the two dates are not equal
 */
bool dateCompare(Date d1, Date d2);

/**
 * @brief Get the day before a date
 * 
 * @param date 
 * @return day before
 */
Date theDayBefore(Date *date);
