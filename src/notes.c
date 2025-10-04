#include <stdio.h>
#include <stdlib.h>
#include "notes.h"

struct Remainder R;

char checkNote(int dd, int mm, int yy) {
    FILE *fp;
    fp = fopen("note.dat", "rb");
    if (fp == NULL) {
        printf(" ");
    }
    while (fread(&R, sizeof(R), 1, fp) == 1) {
        if (R.dd == dd && R.mm == mm && R.yy == yy) {
            fclose(fp);
            return '*';  // Note exists
        }
    }
    fclose(fp);
    return ' ';  // Note does not exist
}

void AddNote() {
    FILE *fp;
    fp = fopen("note.dat", "ab+");
    printf("Enter the date (DD MM YYYY): ");
    scanf("%d%d%d", &R.dd, &R.mm, &R.yy);
    printf("Enter the Note (50 character max): ");
    fflush(stdin);
    scanf("%[^\n]", R.note);
    if (fwrite(&R, sizeof(R), 1, fp)) {
        puts("Note is saved successfully");
        fclose(fp);
    } else {
        puts("\aFail to save!!");
    }
}

void showNote(int mm, int yy) {
    FILE *fp;
    int i = 0, isFound = 0;
    fp = fopen("note.dat", "rb");
    if (fp == NULL) {
        printf("Error in opening the file");
    }
    while (fread(&R, sizeof(R), 1, fp) == 1) {
        if (R.mm == mm && R.yy == yy) {
            printf("\nNote %d Day = %d: %s\n", i + 1, R.dd, R.note);
            isFound = 1;
            i++;
        }
    }
    if (isFound == 0) {
        printf("\nThis Month contains no note\n");
    }
    fclose(fp);
}

void DeleteNote() {
    FILE *fp, *ft;
    int d, m, y;
    int found = 0;
    struct Remainder temp;

    printf("Enter date of note to delete (DD MM YYYY): ");
    if (scanf("%d %d %d", &d, &m, &y) != 3) {
        printf("Invalid input.\n");
        return;
    }

    fp = fopen("note.dat", "rb");
    if (fp == NULL) {
        printf("No notes found.\n");
        return;
    }

    ft = fopen("temp.dat", "wb");
    if (ft == NULL) {
        printf("Unable to create temporary file.\n");
        fclose(fp);
        return;
    }

    while (fread(&temp, sizeof(temp), 1, fp) == 1) {
        if (temp.dd == d && temp.mm == m && temp.yy == y && !found) {
            /* skip the first matching note (delete it) */
            found = 1;
            continue;
        }
        fwrite(&temp, sizeof(temp), 1, ft);
    }

    fclose(fp);
    fclose(ft);

    if (!found) {
        printf("No note found for %02d/%02d/%d.\n", d, m, y);
        remove("temp.dat");
        return;
    }

    /* replace original file with temp file */
    if (remove("note.dat") != 0) {
        printf("Failed to remove original file.\n");
        return;
    }
    if (rename("temp.dat", "note.dat") != 0) {
        printf("Failed to update notes file.\n");
        return;
    }

    printf("Note for %02d/%02d/%d deleted successfully.\n", d, m, y);
}
