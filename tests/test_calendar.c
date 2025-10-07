/* date_validate.h */
#ifndef DATE_VALIDATE_H
#define DATE_VALIDATE_H

#include <stdbool.h>

static inline bool is_leap(int yy) {
    return (yy % 400 == 0) || (yy % 4 == 0 && yy % 100 != 0);
}

static inline int days_in_month(int mm, int yy) {
    if (mm < 1 || mm > 12) return 0;
    static const int d[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (mm == 2) return is_leap(yy) ? 29 : 28;
    return d[mm-1];
}

static inline bool is_valid_date(int dd, int mm, int yy) {
    if (yy < 1900 || yy > 2100) return false;   /* tweak bounds */
    int dim = days_in_month(mm, yy);
    return dim != 0 && dd >= 1 && dd <= dim;
}
#endif
