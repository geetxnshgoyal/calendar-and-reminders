#ifndef CALENDAR_H
#define CALENDAR_H

int is_leap_year(int year);
int days_in_month(int month, int year);

/* New: month grid without globals (42 = 6 weeks x 7 days) */
void generate_month_grid(int month, int year, int grid[42]);
void print_month(const int grid[42]);
void showMonth(int month, int year);   /* convenience wrapper */

#endif
