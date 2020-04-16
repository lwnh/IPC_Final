/* DIGITAL SIGNATURE(S):
   ====================

   List the student author(s) of this code below:

   Fullname                    Seneca Email Address
   --------------------------- ----------------------------
   1)Yumi Lee                   ylee204@myseneca.ca
   2)Dongwook Hwang             dhwang10@myseneca.ca
   3)Byeongsuk Yoo              bsyoo@myseneca.ca

   +--------------------------------------------------------+
   |                FILE: file_helper.h                     |
   +--------------------------------------------------------+
   |           2  0  2  0  ~  W  I  N  T  E  R              |
   |                 I  P  C  :  B  T  P                    |
   |                 1  4  4  :  1  0  0                    |
   |              FINAL ASSESSMENT PART - 2                 |
   |                                                        |
   |     S  E  N  E  C  A            C  O  L  L  E  G  E    |
   +--------------------------------------------------------+ */

#ifndef FILE_HELPER_H
#define FILE_HELPER_H

#include <stdio.h>
#include <string.h>

/********************************************************/
/* Define the missing members for the RiderInfo data    */
/* used to store Rider information read from a file     */
/********************************************************/
struct RiderInfo
{
    char name[21];
    int age;
    char raceLength;
    double startTime;
    double mountainTime;
    double finishTime;
    double raceTime; // finishTime -startTime (calculated by getRaceTime function)
    int withdrawn;
};

// readTime: convert time HH:MM into decimal hours
double readTime(FILE* fp);

// raceManagerSystem: to execute the functions in the menu
void raceManagerSystem(void);

// fileLoad
int fileLoad(struct RiderInfo* info, int size);

// determineCategory: to prompt users to choose one of the categories
char determineCategory(void);

// checkCategory: to check if the input-word is between s/S, m/M, l/L 
int checkCategory(void);

// determineAgeGroup
char* determineAgeGroup(int age);

// convertTime: to convert time readability
void convertTime(double time, int* hour, int* minute);

// getRaceTime : to store calculated race time
void getRaceTime(struct RiderInfo* info, int size);

// checkWithdraw: to check out whether or not athletes withdrew
char* checkWithdraw(int withdraw);

// displayAllriders: to display all riders in the category
void displayAllriders(struct RiderInfo* info, int size);

// displayTopriders: to display top 3 riders in the category
void displayTopriders(struct RiderInfo* info, int size);

// displayLastriders: to display last 3 riders in the category
void displayLastriders(struct RiderInfo* info, int size);

// sortRiders
void sortRiders(struct RiderInfo* info, int size);

void RsortRiders(struct RiderInfo* info, int size);

// to display the winner in the S length
void displaySwinner(struct RiderInfo* info, int size);

// to display the winner in the M length
void displayMwinner(struct RiderInfo* info, int size);

// to display the winner in the L length
void displayLwinner(struct RiderInfo* info, int size);

// to display winners in all category
void diplayWinners(struct RiderInfo* info, int size);

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*!!!        DO NOT ALTER THE CONTENTS BELOW       !!!*/
/*!!!             ( function prototype )           !!!*/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

/********************************************************/
/* Read all the information on one rider from the       */
/* file and store it in the struct. Return true         */
/* when end of file has been reached.                   */
/********************************************************/
int readFileRecord(FILE* fp, struct RiderInfo* info);

#endif
