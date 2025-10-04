#ifndef NOTES_H
#define NOTES_H

struct Remainder {
    int dd;
    int mm;
    int yy;
    char note[50];
};

extern struct Remainder R;

char checkNote(int dd, int mm, int yy);
void AddNote();
void showNote(int mm, int yy);
void DeleteNote();

#endif // NOTES_H
