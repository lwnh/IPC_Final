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

#ifndef EXTRA_HELPER_H
#define EXTRA_HELPER_H

#include <stdio.h>
#include "file_helper.h"

// clearKeyboard: clear input buffer
void clearKeyboard(void);

// pause: to ask users whether to proceed to next step by pushing the enter button
void pause(void);

// getInt: to make sure if users input demical number
int getInt(void);

// getIntInRange: to make sure if users input the number within the range of the menu
int getIntInRange(int min, int max);

// yes : to make sure yes or no
int yes(void);

// displayWelcome: to diplay welcome message
void displayWelcome(void);

// displayHeader for 'all rider' menu
void displayHeaderall(void);

// displayHeader for 'top and last' menu
void displayHeadertoplast(void);

// displayHeader for 'winner' menu
void displayHeaderwinner(void);

// menu: to display default menu list and return the number users choose
int menu(void);

#endif