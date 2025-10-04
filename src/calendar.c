#include <stdio.h>
#include <time.h>
#include "calendar.h"
#include "notes.h"

// Named constants for meaningful magic numbers
#define CALENDAR_SIZE 42
#define MONTHS_IN_YEAR 12
#define DAYS_IN_WEEK 7
#define LEAP_YEAR_DIVISOR_4 4
#define LEAP_YEAR_DIVISOR_100 100
#define LEAP_YEAR_DIVISOR_400 400
#define TM_YEAR_OFFSET 1900
#define DAYS_31 31
#define DAYS_30 30
#define DAYS_29 29
#define DAYS_28 28

int calender[CALENDAR_SIZE];

int leap(int year) {
    if ((year % LEAP_YEAR_DIVISOR_4 == 0 && year % LEAP_YEAR_DIVISOR_100 != 0) || (year % LEAP_YEAR_DIVISOR_400 == 0)) {
        return 1; // Leap year
    } else {
        return 0; // Not a leap year
    }
}

int jan_first_day(int year) {
    int day = 1;  // Sunday is 0
    for (int i = 1; i < year; i++) {
        day = (day + leap(i)) % DAYS_IN_WEEK;
    }
    return day;
}

int month_first_day(int year, int month) {
    int day = jan_first_day(year);
    int days_in_months_leapyear[MONTHS_IN_YEAR] = {DAYS_31, DAYS_29, DAYS_31, DAYS_30, DAYS_31, DAYS_30, DAYS_31, DAYS_31, DAYS_30, DAYS_31, DAYS_30, DAYS_31};
    int days_in_months_notleapear[MONTHS_IN_YEAR] = {DAYS_31, DAYS_28, DAYS_31, DAYS_30, DAYS_31, DAYS_30, DAYS_31, DAYS_31, DAYS_30, DAYS_31, DAYS_30, DAYS_31};

    if (leap(year)) {
        for (int i = 0; i < month - 1; i++) {
            day = (day + days_in_months_leapyear[i] % DAYS_IN_WEEK) % DAYS_IN_WEEK;
        }
    } else {
        for (int i = 0; i < month - 1; i++) {
            day = (day + days_in_months_notleapear[i] % DAYS_IN_WEEK) % DAYS_IN_WEEK;
        }
    }
    return day;
}

void calendar_printer(int year, int month) {
    int days_in_months_leapyear[MONTHS_IN_YEAR] = {DAYS_31, DAYS_29, DAYS_31, DAYS_30, DAYS_31, DAYS_30, DAYS_31, DAYS_31, DAYS_30, DAYS_31, DAYS_30, DAYS_31};
    int days_in_months_notleapear[MONTHS_IN_YEAR] = {DAYS_31, DAYS_28, DAYS_31, DAYS_30, DAYS_31, DAYS_30, DAYS_31, DAYS_31, DAYS_30, DAYS_31, DAYS_30, DAYS_31};
    
    // Get current system date
    time_t t = time(NULL);
    struct tm *current_time = localtime(&t);
    int current_day = current_time->tm_mday;
    int current_month = current_time->tm_mon + 1; // tm_mon is 0-11, so add 1
    int current_year = current_time->tm_year + TM_YEAR_OFFSET; // tm_year is years since 1900
    
    printf("Sun\tMon\tTue\tWed\tThu\tFri\tSat\n");

    for (int i = 0; i < month_first_day(year, month); i++) {
        calender[i] = 0;  // Fill the beginning of the calendar with zeros for empty days
    }

    int* days_in_month = leap(year) ? days_in_months_leapyear : days_in_months_notleapear;

    for (int day = 1; day <= days_in_month[month - 1]; day++) {
        calender[month_first_day(year, month) + day - 1] = day;
    }

    // Print the calendar
    for (int i = 0; i < CALENDAR_SIZE; i++) {
        if (calender[i] == 0) {
            printf(" \t");
        } else {
            int isToday = (calender[i] == current_day && month == current_month && year == current_year);
            char noteIndicator = checkNote(calender[i], month,year);
            
            if (isToday) {
                printf("[%2i%c]\t", calender[i], noteIndicator); // Today: [25*] or [25 ]
            } else {
                printf("%3i%c\t", calender[i], noteIndicator); // Regular day: 25* or 25 
            }
        }
        if ((i + 1) % DAYS_IN_WEEK == 0) {
            printf("\n");
        }
    }
}
