/******************************************************
Program name:	database.c
Author:			Raymond Vo; Palomar ID: 010478907
Date submitted:	June 25, 2017
Class:			CSCI 112
Instructor:		Richard Stegman
Compiler:		CLion 2017.1.2
OS:				Windows 10
Description:    Program retrieves and manipulates company's payroll database.
Input files:	payfile.txt
Output files:	csis.txt
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define SIZE 14

FILE *fp, *fpOut;

typedef struct {
    char first[8], initial[2], last[10], street[17], city[12], state[3], zip[6];
    int age;
    char sex[2];
    int tenure;
    double salary;
} Database;

void strsub(char buf[], char sub[], int start, int end);
void createStructs(Database workers[]);
void outputData(Database workers[]);
void outputMen(Database workers[]);
void outputHighestWoman(Database workers[]);
void outputLowestMan(Database workers[]);
void outputAvgSalary(Database workers[]);
void outputWomanBelow(Database workers[]);
void outputRatio(Database workers[]);
void outputTenured(Database workers[]);
void outputNewSalary(Database workers[]);



int main() {
    int i;
    char buf;
    Database workers[MAX];


    if (!(fp = fopen("payfile.txt", "r"))) {

        exit (1);
    }
    if (!(fpOut = fopen("csis.txt", "w"))) {
        printf("csis.txt could not be opened for output.");
        exit (1);
    }

    createStructs(workers);
    outputData(workers);
    outputMen(workers);
    outputHighestWoman(workers);
    outputLowestMan(workers);
    outputAvgSalary(workers);
    outputWomanBelow(workers);
    outputRatio(workers);

    outputTenured(workers);

    outputNewSalary(workers);
    fclose(fp);
    fclose(fpOut);
    return 0;
}

void strsub(char buf[], char sub[], int start, int end) {
    int i, j;

    for (j = 0, i = start; i <= end; i++, j++) {
        sub[j] = buf[i];
    }
    sub[j] = '\0';

}


void createStructs(Database workers[]) {

    int i = 0;
    char buf[MAX];
    char temp[SIZE];

    if (!(fp = fopen("payfile.txt", "r"))) {
        printf("payfile.txt could not be opened for input.");
        exit(1);
    }

    while (!feof(fp)) {
        fgets(buf, MAX, fp);
        strsub(buf, workers[i].first, 0, 6);
        strsub(buf, workers[i].initial, 8, 8);
        strsub(buf, workers[i].last, 10, 18);
        strsub(buf, workers[i].street, 20, 35);
        strsub(buf, workers[i].city, 37, 47);
        strsub(buf, workers[i].state, 49, 50);
        strsub(buf, workers[i].zip, 52, 56);
        strsub(buf, temp, 58, 59);
        workers[i].age = atoi(temp);
        strsub(buf, workers[i].sex, 61, 61);
        strsub(buf, temp, 63, 63);
        workers[i].tenure = atoi(temp);
        strsub(buf, temp, 65, 70);
        workers[i].salary = atof(temp);
        i++;
    }
}

void outputData(Database workers[]) {

    printf("%5s %8s %3s \t %5s \t %5s\t %10s %5s %6s %5s %5s %5s\n", "First", "Initial", "Last", "Street", "City", "State", "Zip", "Age", "Sex", "Tenure", "Salary");
    fprintf(fpOut, "%5s %8s %3s \t %5s \t %5s\t %10s %5s %6s %5s %5s %5s\n", "First", "Initial", "Last", "Street", "City", "State", "Zip", "Age", "Sex", "Tenure", "Salary");
    printf("--------------------------------------------------------------------------------------------\n");
    fprintf(fpOut, "--------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < SIZE; i++) {

        printf("%5s %5s %10s %5s %5s %5s %6s %5d %5s %5d %7.2lf\n", workers[i].first, workers[i].initial, workers[i].last,
               workers[i].street, workers[i].city, workers[i].state, workers[i].zip,
               workers[i].age, workers[i].sex, workers[i].tenure,  workers[i].salary);
        fprintf(fpOut,"%5s %5s %10s %5s %5s %5s %6s %5d %5s %5d %7.2lf\n", workers[i].first, workers[i].initial, workers[i].last,
                workers[i].street, workers[i].city, workers[i].state, workers[i].zip,
                workers[i].age, workers[i].sex, workers[i].tenure,  workers[i].salary);
    }
}
void outputMen(Database workers[]) {

    printf("\nMen on payroll:\n");
    fprintf(fpOut, "\nMen on payroll:\n");



    for (int i = 0; i < SIZE; i++) {
        if (strcmp(workers[i].sex, "M") == 0) {

            printf("%2s %2s\n", workers[i].first, workers[i].last);
            fprintf(fpOut,"%2s %2s\n", workers[i].first, workers[i].last);


        }
    }
}

void outputHighestWoman(Database workers[]) {
    int i = 0;
    double max = 0;

    max = workers[1].salary;

    printf("\nHighest paid woman:\n");
    fprintf(fpOut,"\nHighest paid woman:\n");

    Database *p;

    for (i = 1; i < SIZE; i++) {

        if (strcmp(workers[i].sex, "F") == 0 && workers[i].salary > max) {
            max = workers[i].salary;
            p = &workers[i];


        }

    }
    printf("%2s %2s\n", p->first, p->last);
    fprintf(fpOut,"%2s %2s\n", p->first, p->last);
}


void outputLowestMan(Database workers[]) {
    int i = 0;
    double min;

    printf("\nLowest paid man:\n");
    fprintf(fpOut, "\nLowest paid man:\n");
    min = workers[1].salary;

    Database *p;

    for (i = 1; i < SIZE; i++) {

        if (strcmp(workers[i].sex, "M") == 0 && workers[i].salary < min) {
            min = workers[i].salary;
            p = &workers[i];


        }

    }
    printf("%2s %2s\n", p->first, p->last);
    fprintf(fpOut,"%2s %2s\n", p->first, p->last);

}

void outputAvgSalary(Database workers[]) {
    int i;
    double sum = 0, avg;
    double *average;
    printf("\nAverage salary\n");
    fprintf(fpOut, "\nAverage salary:\n");

    for (i = 0; i < SIZE; i++) {
        sum += workers[i].salary;
    }
    avg = sum / SIZE;
    average = &avg;
    printf("$%.2lf\n", *average);
    fprintf(fpOut, "$%.2lf\n", *average);

}

void outputWomanBelow(Database workers[]) {
    int i;
    double sum = 0, avg, min;

    printf("\nWomen earning less than average salary:\n");
    fprintf(fpOut, "\nWomen earning less than average salary:\n");
    for (i = 0; i < SIZE; i++) {
        sum += workers[i].salary;
    }
    avg = sum / SIZE;
    for (i = 0; i < SIZE; i++) {

        if (strcmp(workers[i].sex, "F") == 0 && workers[i].salary < avg) {
            printf("%2s %2s\n", workers[i].first, workers[i].last);
            fprintf(fpOut, "%2s %2s\n", workers[i].first, workers[i].last);
        }
    }
}

void outputRatio(Database workers[]) {
    int i, below = 0, above = 0;
    double sum = 0, avg, min, ratio;

    printf("\nRatio of men above average salary to men below average salary:\n");
    fprintf(fpOut, "\nRatio of men above average salary to men below average salary:\n");

    for (i = 0; i < SIZE; i++) {
        sum += workers[i].salary;
    }
    avg = sum / SIZE;
    for (i = 0; i < SIZE; i++) {
        if (strcmp(workers[i].sex, "M") == 0 && workers[i].salary < avg) {
            ++below;
        }
        if (strcmp(workers[i].sex, "M") == 0 && workers[i].salary > avg) {
            ++above;
        }
    }
    ratio = (double) above / below;
    printf("%.3lf\n", ratio);
    fprintf(fpOut,"%.3lf\n", ratio);
}

void outputTenured(Database workers[]) {
    int i;

    printf("\nEmployees w/ salary over $35,000/year, tenured for 5+ years, and over 30 years old:\n");
    fprintf(fpOut, "\nEmployees w/ salary over $35,000/year, tenured for 5+ years, and over 30 years old:\n");


    for (i = 0; i < SIZE; i++) {
        if ((workers[i].salary * 52 > 35000) && (workers[i].tenure >= 5) && (workers[i].age > 30) ) {
            printf("%s %s\n", workers[i].first, workers[i].last);
            fprintf(fpOut, "%s %s\n", workers[i].first, workers[i].last);

        }
    }

}

void outputNewSalary(Database workers[]) {
int i;
    printf("\nEmployees who make less than $350.00 per week and new salary if given 10%% raise:\n");
    fprintf(fpOut, "\nEmployees who make less than $350.00 per week and new salary if given 10%% raise:\n");

    for (i = 0; i < SIZE; i++) {
        if (workers[i].salary < 350) {
            workers[i].salary *= 1.1;
            printf("%s %s New salary: $%.2f\n", workers[i].first, workers[i].last, workers[i].salary);
            fprintf(fpOut, "%s %s New salary: $%.2f\n", workers[i].first, workers[i].last, workers[i].salary);

        }
    }

}

