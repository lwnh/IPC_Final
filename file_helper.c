/* DIGITAL SIGNATURE(S):
   ====================

   List the student author(s) of this code below:

   Fullname                    Seneca Email Address
   --------------------------- ----------------------------
   1)Yumi Lee                   ylee204@myseneca.ca
   2)Dongwook Hwang             dhwang10@myseneca.ca
   3)Byeongsuk Yoo              bsyoo@myseneca.ca

   +--------------------------------------------------------+
   |                FILE: file_helper.c                     |
   +--------------------------------------------------------+
   |           2  0  2  0  ~  W  I  N  T  E  R              |
   |                 I  P  C  :  B  T  P                    |
   |                 1  4  4  :  1  0  0                    |
   |              FINAL ASSESSMENT PART - 2                 |
   |                                                        |
   |     S  E  N  E  C  A            C  O  L  L  E  G  E    |
   |                                                        |
   |  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  |
   |  !!!      DO NOT ALTER THE CONTENTS BELOW         !!!  |
   |  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  |
   +--------------------------------------------------------+ */

#define _CRT_SECURE_NO_WARNINGS
#include "file_helper.h"
#include "extra_helper.h"

//define the maximum number of records
#define MAXRECORDS 5000

/********************************************************/
/* Read from the opened file the time (HH:MM) parts of  */
/* the record and return the time as decimal hours      */
/********************************************************/
double readTime(FILE* fp)
{
	int hour, min;

	fscanf(fp, "%d%*c", &hour);
	fscanf(fp, "%d", &min);

	return hour + (min / 60.0);
}

/********************************************************/
/* Read all the information on one rider from the valid */
/* (pre-opened) file and store it in the struct.        */
/* Return true when end of file has been reached.       */
/********************************************************/
int readFileRecord(FILE* fp, struct RiderInfo* info)
{
	int result = 1, ch;

	if (!feof(fp))
	{
		result = 0;

		// read from file and assign to data structure
		fscanf(fp, "%[^,]%*c", info->name);
		fscanf(fp, "%d", &info->age);
		fscanf(fp, " %c", &info->raceLength);
		info->startTime = readTime(fp);
		info->mountainTime = readTime(fp);
		info->finishTime = readTime(fp);

		// Last Field (withdrawn: may not be present)
		ch = fgetc(fp);
		info->withdrawn = 0;

		if (ch == ' ')
		{
			ch = fgetc(fp);
			info->withdrawn = ch == 'W';
			ch = fgetc(fp);
		}

		// clear input file buffer until end of line (record):
		while (!feof(fp) && ch != '\n')
		{
			ch = fgetc(fp);
		}
	}

	return result;
}

// raceManagerSystem: to execute the functions in the menu
void raceManagerSystem(void)
{
	struct RiderInfo info[MAXRECORDS] = { {{'\0'}} };
	int flag = 0;

	FILE* fp = fopen("data.txt", "r");
	flag = fileLoad(fp, info, MAXRECORDS);

	while (flag)
	{
		switch (menu())
		{
		case 1:

			printf("\n");
			displayTopriders(info, MAXRECORDS);
			printf("\n");
			pause();
			printf("\n");
			break;

		case 2:

			printf("\n");
			displayAllriders(info, MAXRECORDS);
			printf("\n");
			pause();
			printf("\n");
			break;

		case 3:

			printf("\n");
			displayLastriders(info, MAXRECORDS);
			printf("\n");
			pause();
			printf("\n");
			break;

		case 4:

			printf("\n");
			diplayWinners(info, MAXRECORDS);
			printf("\n");
			pause();
			printf("\n");
			break;

		case 0:

			printf("\n");
			printf("Exit the program? (Y)es/(N)o: ");

			if (yes())
			{
				printf("\n");
				printf("Race Management System: terminated\n");
				flag = 0;
			}
			else
			{
				printf("\n");
			}
			break;
		}
	}
}

int fileLoad(FILE* fp, struct RiderInfo* info, int size)
{
	int flag = 0, i;

	for (i = 0; i < size; i++)
	{
		flag = readFileRecord(fp, &info[i]);
	}

	if (flag == 1)
	{
		printf("Succeeded to load a file\n");
		printf("\n");
		displayWelcome();
	}
	else
	{
		printf("Failed to load a file\n");
		printf("Retry after checking a file\n");
		printf("System will be terminated\n");
		printf("\n");
	}

	return flag;
}

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
