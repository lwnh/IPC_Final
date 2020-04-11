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
    char withdrawn;
};

// readTime: convert time HH:MM into decimal hours
double readTime(FILE* fp);

// raceManagerSystem: to execute the functions in the menu
void raceManagerSystem(void);

// determineCategory: to prompt users to choose one of the categories

// checkCategory: to check if the input-word is between s/S, m/M, l/L 

// displayAllriders: to display all riders in the category
void displayAllriders(const struct Contact contacts[], int size);

// displayTopriders: to display top 3 riders in the category

// lookupTopriders: to look up top 3 riders in the category

// displayLastriders: to display last 3 riders in the category

// lookupLastriders: to look up last 3 riders in the category

// diplayWinners: to display winners in all category

// lookupWinners: to display last 3 riders in the category

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
