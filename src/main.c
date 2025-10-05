#include <stdio.h>
#include "calendar.h"
#include "notes.h"

/* Read an integer with a prompt; re-ask until the user enters a valid int.
   Also clears the rest of the input line each time. */
static int read_int(const char *prompt) {
    int x;
    int ch;
    for (;;) {
        if (prompt && *prompt) {
            printf("%s", prompt);
        }
        if (scanf("%d", &x) == 1) {
            /* clear trailing characters on the line */
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            return x;
        }
        /* invalid token: clear line and re-prompt */
        printf("Invalid input! Try again.\n");
        while ((ch = getchar()) != '\n' && ch != EOF) {}
    }
}

int main(void) {
    for (;;) {
        printf("\n=== Calendar & Reminders ===\n");
        printf("1. Show calendar\n");
        printf("2. Add note\n");
        printf("3. Show notes for a month\n");
        printf("4. Delete a note by date\n");
        printf("5. Exit\n");

        int choice = read_int("Enter your choice: ");

        switch (choice) {
            case 1: {
                int year  = read_int("Enter year  (e.g., 2025): ");
                int month = read_int("Enter month (1-12): ");
                calendar_printer(year, month);
                break;
            }
            case 2:
                AddNote();
                break;

            case 3: {
                int mm = read_int("Enter month (1-12): ");
                int yy = read_int("Enter year  (e.g., 2025): ");
                showNote(mm, yy);
                break;
            }

            case 4:
                DeleteNote();
                break;

            case 5:
                printf("Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice! Please select 1-5.\n");
                break;
        }
    }
}
