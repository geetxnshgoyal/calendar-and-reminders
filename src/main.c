#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calendar.h"
#include "notes.h"

/* Some repos don't declare this in calendar.h; declare defensively. */
void calendar_printer(int year, int month);

/* ---------- simple safe input helpers ---------- */

static int read_line(char *buf, size_t n) {
    if (!fgets(buf, (int)n, stdin)) return 0;
    size_t len = strlen(buf);
    if (len && buf[len - 1] == '\n') buf[len - 1] = '\0';
    return 1;
}

static int read_int(const char *prompt, int min, int max, int *out) {
    char line[64];
    for (;;) {
        if (prompt && *prompt) printf("%s", prompt);
        if (!read_line(line, sizeof line)) return 0;  /* EOF */
        char *end;
        long v = strtol(line, &end, 10);
        if (end == line || *end != '\0') {
            puts("Please enter a valid integer.");
            continue;
        }
        if ((min != 0 || max != 0) && (v < min || v > max)) {
            printf("Please enter a value between %d and %d.\n", min, max);
            continue;
        }
        *out = (int)v;
        return 1;
    }
}

/* ---------- actions ---------- */

static void action_show_calendar(void) {
    int year, month;
    if (!read_int("Enter year (e.g., 2025): ", 1, 9999, &year)) return;
    if (!read_int("Enter month (1-12): ", 1, 12, &month)) return;

    puts("\n Sun\tMon\tTue\tWed\tThu\tFri\tSat");
    calendar_printer(year, month);
    puts("");
}

static void action_add_note(void) {
    AddNote();
}

static void action_view_monthly_reminders(void) {
    int year, month;
    if (!read_int("Enter year (e.g., 2025): ", 1, 9999, &year)) return;
    if (!read_int("Enter month (1-12): ", 1, 12, &month)) return;

    /* showNote prints all notes for given month/year */
    showNote(month, year);
}

static void action_delete_note(void) {
    DeleteNote();
}

/* ---------- menu loop ---------- */

static void print_menu(void) {
    puts("==== Calendar & Reminders ====");
    puts("1) Show calendar for a month");
    puts("2) Add a note");
    puts("3) View reminders for a specific month");
    puts("4) Delete a note");
    puts("0) Exit");
}

int main(void) {
    for (;;) {
        print_menu();
        int choice;
        if (!read_int("Select an option: ", 0, 4, &choice)) break;

        switch (choice) {
            case 1: action_show_calendar(); break;
            case 2: action_add_note(); break;
            case 3: action_view_monthly_reminders(); break;
            case 4: action_delete_note(); break;
            case 0: puts("Goodbye!"); return 0;
            default: puts("Invalid option."); break;
        }

        puts(""); /* spacer */
    }
    return 0;
}
