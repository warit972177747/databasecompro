#include <stdio.h> // for input output functions like printf, scanf
#include <stdlib.h>
#include <conio.h>
#include <windows.h> // for windows related functions (not important)
#include <string.h> // string operations

/* List of Global Variable */
COORD coord = {0, 0}; // top-left corner of window

/*  function : gotoxy
    @param input: x and y coordinates
    @param output: moves the cursor in specified position of console */

void gotoxy(int x, int y) {
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void title() {
    gotoxy(35, 3);
    printf("OOO    OOO  OOOOO  OOO    OOOO   OOO   OOOO OOOOO");
    gotoxy(35, 4);
    printf("O  OO O   O   O   O   O   O   O O   O O     O    ");
    gotoxy(35, 5);
    printf("O  OO O   O   O   O   O   OOOO  O   O OOOOO OOOO ");
    gotoxy(35, 6);
    printf("O  OO OOOOO   O   OOOOO   O   O OOOOO     O O    ");
    gotoxy(35, 7);
    printf("OOO   O   O   O   O   O   OOOO  O   O OOOO  OOOOO");
}

void animation(int round) {
    for (int i=0; i<round; i++) {
        system("cls");
        gotoxy(55, 15);
        printf("LOADING");
        gotoxy(57, 16);
        printf(".");
        Sleep(150);
        gotoxy(58, 16);
        printf(".");
        Sleep(150);
        gotoxy(59, 16);
        printf(".");
        Sleep(150);
    }
    system("COLOR 9F");
}

/* Main function started */

int main() {
    system("COLOR 9F");
    FILE *fp, *ft; // file pointers
    char another, choice;

    /* structure that represent a employee */

    struct student {
        char name[40]; // name of employee
        int age; // age of employee
        char id[11]; // basic salary of employee
        float score; // score out of 100
    };

    struct student s; // structure variable creation

    char studentname[40]; // string to store name of the employee

    long int recsize; // size of each record of employee

    char studentid[11];

    int status = 1;

    /*  open the file in binary read and write mode
        if the file EMP.DAT already exists then it open that file in read write mode
        if the file doesn't exit it simply create a new copy */

    fp = fopen("EMP.DAT", "rb+");
    if (fp == NULL) {
        fp = fopen("EMP.DAT", "wb+");
        if (fp == NULL) {
            printf("Connot open file");
            exit(1);
        }
    }

    // sizeo of each record i.e. size of structure variable e
    recsize = sizeof(s);
    // infinite loop continues untile the break statement encounter
    while (1) {
        system("cls"); // clear the console window
        title();
        gotoxy(45, 12); // move the cursor to position 30, 10 from top-left corner
        printf("Press [1] to Add Data Record"); // option for add record
        gotoxy(45, 14);
        printf("Press [2] to Show Data List"); // option for showing existing record
        gotoxy(45, 16);
        printf("Press [3] Modify Data Records"); // option for editing record
        gotoxy(45, 18);
        printf("Press [4] Delete Data Records"); // option for deleting record
        gotoxy(45, 20);
        printf("Press [5] to Exit The Program"); // exit from the program
        gotoxy(59, 10);
        printf(" <<");
        gotoxy(55, 10);
        printf(">> "); // enter the choice 1, 2, 3, 4, 5
        fflush(stdin); // flush the input buffer
        choice = getche(); // get the input from keyboard
        switch (choice) {
        case '1': // if user press 1
            system("cls");
            animation(2);
            fseek(fp, 0, SEEK_END); // search the file and move cursor to end of the file
            // here 0 indicates moving 0 distance from the end of the file

            another = 'y';
            while (another == 'y') { // if user want to add another record
                system("cls");
                gotoxy(40, 10);
                printf("Enter student name: ");
                scanf("%[^\n]s", s.name);

                gotoxy(40, 12);
                printf("Enter student age: ");
                scanf("%d", &s.age);

                gotoxy(40, 14);
                printf("Enter studentID: ");
                scanf("%s", s.id);

                gotoxy(40, 16);
                printf("Enter total score: ");
                scanf("%f", &s.score);

                fwrite(&s, recsize, 1, fp); // write the record in the file

                gotoxy(40, 18);
                printf("[Y] Add More\t[M] Menu");
                fflush(stdin);
                another = getche();
            }
            animation(1);
            break;
        case '2': // press '2' to show all data list
            animation(2);
            system("cls");
            rewind(fp); // this moves file cursor to start of the file
            printf("_");
            for (int i=1; i<=105; i++)
                printf("_");
            printf("\n|%21s%21s%21s%21s%21s\n", "|", "|", "|", "|", "|");
            printf("|%12s%9s%12s%9s%12s%9s%12s%9s%12s%9s\n|", "Name", "|", "Age", "|", "ID", "|", "Score", "|", "Grade", "|"); // table creation
            for (int i=1; i<=105; i++)
                if (!(i % 21))
                    printf("|");
                else
                    printf("_");
            printf("\n");
            while (fread(&s, recsize, 1, fp) == 1) { // read the file and fetch the record one record per fetch
                printf("|%-20.20s|%-20d|%-20s|%-20.2f|", s.name, s.age, s.id, s.score); // print a data list for each row
                if (s.score < 0 || s.score > 100){
                    printf("%-20s|\n", "Error");}
                else if (s.score >= 0 && s.score < 50){ // calculator for grading
                    printf("%-20s|\n", "F");}
                else if (s.score < 55){
                    printf("%-20s|\n", "D");}
                else if (s.score < 60){
                    printf("%-20s|\n", "D+");}
                else if (s.score < 65){
                    printf("%-20s|\n", "C");}
                else if (s.score < 70){
                    printf("%-20s|\n", "C+");}
                else if (s.score < 75){
                    printf("%-20s|\n", "B");}
                else if (s.score < 80){
                    printf("%-20s|\n", "B+");}
                else if (s.score <= 100){
                    printf("%-20s|\n", "A");}
            }
            printf("\n[M] Menu");
            getch();
            animation(1);
            break;
        case '3': // if user press 3 then do editing existing record
            animation(2);
            system("cls");
            another = 'y';
            while (another == 'y') {
                system("cls");
                gotoxy(40, 10);
                printf("Enter the studentID to modify: ");
                scanf("%s", studentid);
                rewind(fp);
                while (fread(&s, recsize, 1, fp) == 1) { // fetch all record from file
                    status = 1;
                    if (strcmp(s.id,studentid) == 0 ) { // if entered name matches with that in file
                        status = 0;
                        gotoxy(40, 12);
                        printf("Enter new name: ");
                        scanf("%s", s.name);

                        gotoxy(40, 14);
                        printf("Enter new age: ");
                        scanf("%d", &s.age);

                        gotoxy(40, 16);
                        printf("Enter new ID: ");
                        scanf("%s", s.id);

                        gotoxy(40, 18);
                        printf("Enter new score: ");
                        scanf("%f", &s.score);

                        fseek(fp, -recsize, SEEK_CUR); // move the cursor 1 step back from current position
                        fwrite(&s, recsize, 1, fp); // override the record
                        // animation(1);
                        break;
                    }
                }
                if (status) {
                    gotoxy(40, 12);
                    printf("Sorry, studentID \"%s\" not found", studentid);

                    gotoxy(40, 14);
                    printf("[Y] Try Again [M] Menu");
                    fflush(stdin);
                    another = getche();
                    animation(1);
                }
                else{
                    gotoxy(40, 20);
                    printf("[Y] Modify More\t[M] Menu");
                    fflush(stdin);
                    another = getche();
                    animation(1);

                }
            }
            break;
        case '4': // press '4' to delete data by studentID
            animation(2);
            system("cls");
            another = 'y';
            while (another == 'y') {
                system("cls");
                gotoxy(40, 12);
                printf("Enter StudentID to delete: ");
                scanf("%s", studentid);
                ft = fopen("Temp.dat", "wb"); // create a intermediate file for temporary storage
                rewind(fp); // move record to starting of file
                while (fread(&s, recsize, 1, fp) == 1) { // read all records from file
                    if (strcmp(s.id,studentid) == 0 ){
                        status = 0;}
                    if (strcmp(s.id,studentid) != 0 ){// if the entered record match
                        fwrite(&s, recsize, 1, ft);} // move all records except the one that is to be deleted to temp file
                }
                if (status == 1) {
                    gotoxy(40, 14);
                    printf("StudentID \"%s\" not found", studentid);
                }
                else{
                    gotoxy(40,14);
                    printf("StudentID \"%s\" have deleted", studentid);
                }
                fclose(fp);
                fclose(ft);
                remove("EMP.DAT"); // remove the orginal file
                rename("Temp.dat", "EMP.DAT"); // rename the temp file to original file name
                fp = fopen("EMP.DAT", "rb+");
                gotoxy(40, 16);
                printf("[Y] Try Again\t[M] Menu");
                fflush(stdin);
                another = getche();
                status = 1;
            }
            animation(1);
            break;
        case '5': // exit from app
            fclose(fp); // close the file
            exit(0); // exit from the program
        }
    }
    return 0;
}
