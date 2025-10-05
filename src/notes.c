#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "notes.h"

static void trim_newline(char *s) {
    if (!s) return;
    size_t n = strlen(s);
    if (n && s[n - 1] == '\n') s[n - 1] = '\0';
}

char checkNote(int dd, int mm, int yy) {
    struct Remainder r;
    FILE *fp = fopen("note.dat", "rb");
    if (!fp) return ' ';

    while (fread(&r, sizeof r, 1, fp) == 1) {
        if (r.dd == dd && r.mm == mm && r.yy == yy) {
            fclose(fp);
            return '*';
        }
    }

    fclose(fp);
    return ' ';
}

void AddNote(void) {
    struct Remainder r;
    FILE *fp = fopen("note.dat", "ab+");
    if (!fp) {
        puts("Failed to open notes file.");
        return;
    }

    printf("Enter the date (DD MM YYYY): ");
    if (scanf("%d %d %d", &r.dd, &r.mm, &r.yy) != 3) {
        puts("Invalid date.");
        fclose(fp);
        // clear leftover line
        int c; while ((c = getchar()) != '\n' && c != EOF) {}
        return;
    }

    // consume end of line before reading text
    int c; while ((c = getchar()) != '\n' && c != EOF) {}

    printf("Enter the Note (max %zu chars): ", sizeof r.note - 1);
    if (!fgets(r.note, sizeof r.note, stdin)) {
        puts("Failed to read note.");
        fclose(fp);
        return;
    }
    trim_newline(r.note);

    if (fwrite(&r, sizeof r, 1, fp) == 1) {
        puts("Note saved successfully.");
    } else {
        puts("Failed to save note.");
    }
    fclose(fp);
}

void showNote(int mm, int yy) {
    struct Remainder r;
    FILE *fp = fopen("note.dat", "rb");
    if (!fp) {
        puts("Error opening notes file.");
        return;
    }

    int i = 0, found = 0;
    while (fread(&r, sizeof r, 1, fp) == 1) {
        if (r.mm == mm && r.yy == yy) {
            printf("\nNote %d Day = %d: %s\n", ++i, r.dd, r.note);
            found = 1;
        }
    }
    if (!found) puts("\nThis month contains no note.");

    fclose(fp);
}

void DeleteNote(void) {
    FILE *fp = fopen("note.dat", "rb");
    if (!fp) {
        puts("No notes found.");
        return;
    }

    FILE *ft = fopen("temp.dat", "wb");
    if (!ft) {
        puts("Unable to create temporary file.");
        fclose(fp);
        return;
    }

    int d, m, y, found = 0;
    struct Remainder r;

    printf("Enter date of note to delete (DD MM YYYY): ");
    if (scanf("%d %d %d", &d, &m, &y) != 3) {
        puts("Invalid input.");
        fclose(fp);
        fclose(ft);
        remove("temp.dat");
        // clear leftover line
        int c; while ((c = getchar()) != '\n' && c != EOF) {}
        return;
    }

    while (fread(&r, sizeof r, 1, fp) == 1) {
        if (!found && r.dd == d && r.mm == m && r.yy == y) {
            found = 1;              // skip first match (delete it)
            continue;
        }
        fwrite(&r, sizeof r, 1, ft);
    }

    fclose(fp);
    fclose(ft);

    if (!found) {
        printf("No note found for %02d/%02d/%d.\n", d, m, y);
        remove("temp.dat");
        return;
    }

    if (remove("note.dat") != 0 || rename("temp.dat", "note.dat") != 0) {
        puts("Failed to update notes file.");
        return;
    }

    printf("Note for %02d/%02d/%d deleted successfully.\n", d, m, y);
}
