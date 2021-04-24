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

/* Main function started */

int main() {
    FILE *fp, *ft; // file pointers
    char another, choice;

    /* structure that represent a employee */

    struct student {
        char name[40]; // name of employee
        int age; // age of employee
        int id; // basic salary of employee
        float score; // score out of 100
    };

    struct student s; // structure variable creation

    char studentname[40]; // string to store name of the employee

    long int recsize; // size of each record of employee

    int studentid;

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
        gotoxy(30, 10); // move the cursor to position 30, 10 from top-left corner
        printf("1. Add Record"); // option for add record
        gotoxy(30, 12);
        printf("2. List Records"); // option for showing existing record
        gotoxy(30, 14);
        printf("3. Modify Records"); // option for editing record
        gotoxy(30, 16);
        printf("4. Delete Records"); // option for deleting record
        gotoxy(30, 18);
        printf("5. Exit"); // exit from the program
        gotoxy(30, 20);
        printf("Your Choice: "); // enter the choice 1, 2, 3, 4, 5
        fflush(stdin); // flush the input buffer
        choice = getche(); // get the input from keyboard
        switch (choice) {
        case '1': // if user press 1
            system("cls");
            fseek(fp, 0, SEEK_END); // search the file and move cursor to end of the file
            // here 0 indicates moving 0 distance from the end of the file

            another = 'y';
            while (another == 'y') { // if user want to add another record
                printf("\nEnter name: ");
                scanf("%[^\n]", &s.name);

                printf("\nEnter age: ");
                scanf("%d", &s.age);

                printf("\nEnter ID: ");
                scanf("%d", &s.id);

                printf("\nEnter score: ");
                scanf("%f", &s.score);

                fwrite(&s, recsize, 1, fp); // write the record in the file

                printf("\nAdd another record(y/n) ");
                fflush(stdin);
                another = getche();
            }
            break;
        case '2': // press '2' to show all data list
            system("cls");
            rewind(fp); // this moves file cursor to start of the file
            printf("_");
            int i;
            for (i=1; i<=105; i++)
                printf("_");
            printf("\n|%21s%21s%21s%21s%21s\n", "|", "|", "|", "|", "|");
            printf("|%12s%9s%12s%9s%12s%9s%12s%9s%12s%9s\n|", "Name", "|", "Age", "|", "ID", "|", "Score", "|", "Grade", "|"); // table creation
            for (i=1; i<=105; i++)
                if (!(i % 21))
                    printf("|");
                else
                    printf("_");
            printf("\n");
            while (fread(&s, recsize, 1, fp) == 1) { // read the file and fetch the record one record per fetch
                printf("|%-20.20s|%-20d|%-20d|%-20.2f|", s.name, s.age, s.id, s.score); // print a data list for each row
                if (s.score >= 0 && s.score < 50) // calculator for grading
                    printf("%-20s|\n", "F");
                else if (s.score <= 60)
                    printf("%-20s|\n", "D");
                else if (s.score <= 70)
                    printf("%-20s|\n", "C");
                else if (s.score <= 80)
                    printf("%-20s|\n", "B");
                else if (s.score <= 100)
                    printf("%-20s|\n", "A");
                else
                    printf("%-20s|\n", "Error");
            }
            getch();
            break;
        case '3': // if user press 3 then do editing existing record
            system("cls");
            another = 'y';
            while (another == 'y') {
                printf("\nEnter the student id to modify: ");
                scanf("%d", &studentid);
                rewind(fp);
                while (fread(&s, recsize, 1, fp) == 1) { // fetch all record from file
                	status = 1;
                    if (s.id == studentid) { // if entered name matches with that in file
                    	status = 0;
                        printf("\nEnter new name,age, ID and score: ");
                        scanf("%s%d%d%f", s.name, &s.age, &s.id, &s.score);
                        fseek(fp, -recsize, SEEK_CUR); // move the cursor 1 step back from current position
                        fwrite(&s, recsize, 1, fp); // override the record
                        break;
                    } 
                }
                if(status){
                	printf("\nID not found");
				}
                printf("\nModify another record(y/n)");
                fflush(stdin);
                another = getche();
            }
            break;
        case '4': // press '4' to delete data by studentID
            system("cls");
            another = 'y';
            while (another == 'y') {
                printf("\nEnter StudentID to delete: ");
                scanf("%d", &studentid);
                ft = fopen("Temp.dat", "wb"); // create a intermediate file for temporary storage
                rewind(fp); // move record to starting of file
                while (fread(&s, recsize, 1, fp) == 1) { // read all records from file
                    if (s.id == studentid)
                        status = 0;
                    if (s.id != studentid) // if the entered record match
                        fwrite(&s, recsize, 1, ft); // move all records except the one that is to be deleted to temp file
                }
                if (status == 1)
                    printf("ID not found\n");
                fclose(fp);
                fclose(ft);
                remove("EMP.DAT"); // remove the orginal file
                rename("Temp.dat", "EMP.DAT"); // rename the temp file to original file name
                fp = fopen("EMP.DAT", "rb+");
                printf("\nDelete another record(y/n)");
                fflush(stdin);
                another = getche();
                status = 1;
            }
            break;
        case '5': // exit from app
            fclose(fp); // close the file
            exit(0); // exit from the program
        }
    }
    return 0;
}
