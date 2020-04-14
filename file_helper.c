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
	int flag = fileLoad(info, MAXRECORDS);

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

int fileLoad(struct RiderInfo* info, int size)
{
	int flag = 0, i;
	FILE* fp = fopen("data.txt", "r");

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
char determineCategory(void)
{
	char category = '\0';

	printf("Which category (S, M, L): ");
	switch (checkCategory())
	{
	case 0:
		category = 'S';
		break;
	case 1:
		category = 'M';
		break;
	case 2:
		category = 'L';
		break;
	}
	printf("\n");

	return category;
}

// checkCategory: to check if the input-word is between s/S, m/M, l/L 
int checkCategory(void)
{
	char input, inputNL;
	int flag = 1, category;

	while (flag)
	{
		scanf("%c%c", &input, &inputNL);


		if (inputNL != '\n')
		{
			clearKeyboard();
			printf("*** INVALID ENTRY *** <Only S, M, L are acceptable>: ");
		}
		else if (input != 's' && input != 'S' && input != 'm' && input != 'M' && input != 'l' && input != 'L')
		{
			printf("*** INVALID ENTRY *** <Only S, M, L are acceptable>: ");
		}
		else
		{
			flag = 0;
			if (input == 's' || input == 'S')
			{
				category = 0;
			}
			else if (input == 'm' || input == 'M')
			{
				category = 1;
			}
			else
			{
				category = 2;
			}
		}
	}

	return category;
}

// determineAgeGroup
char* determineAgeGroup(int age)
{
	char* group;

	if (age >= 16 && age <= 20)
	{
		group = "Junior";
	}
	else if (age >= 21 && age <= 34)
	{
		group = "Adult";
	}
	else
	{
		group = "Senior";
	}

	return group;
}

// timeCal: to convert time read from file into full length
double timeCal(double start, double finish)
{
	return (finish - start) + 0.005;
}

// convertTime: to convert time readability
void convertTime(double time, int* hour, int* minute)
{
	*hour = (int)time;
	*minute = (int)((time - *hour) * 60);
}

// getRaceTime : to store calculated race time
double getRaceTime(struct RiderInfo* info)
{
	info->raceTime = timeCal(info->startTime, info->finishTime);
	return info->raceTime;
}

char* checkWithdraw(int withdraw)
{
	char* result;

	if (withdraw == 1)
	{
		result = "Yes";
	}
	else
	{
		result = "No";
	}

	return result;
}

// displayAllriders: to display all riders in the category
void displayAllriders(struct RiderInfo* info, int size)
{
	char category;
	int i, hour = 0, minute = 0;

	category = determineCategory();
	displayHeaderall();

	for (i = 0; i < size; i++)
	{
		if (info[i].raceLength == category)
		{
			printf("%-21s", info[i].name);
			printf("%9s", determineAgeGroup(info[i].age));
			if (info[i].withdrawn)
			{
				printf("    N/A");
			}
			else
			{
				convertTime(getRaceTime(&info[i]), &hour, &minute);
				printf("%4d:%02d", hour, minute);
			}
			printf("%11s\n", checkWithdraw(info[i].withdrawn));
		}
	}
}

// displayTopriders: to display top 3 riders in the category
void displayTopriders(struct RiderInfo* info, int size) {

}

// lookupTopriders: to look up top 3 riders in the category
void lookupTopriders(struct RiderInfo* info, int size) {

}

// displayLastriders: to display last 3 riders in the category
void displayLastriders(struct RiderInfo* info, int size) {

}

// lookupLastriders: to look up last 3 riders in the category
void lookupLastriders(struct RiderInfo* info, int size) {

}

// diplayWinners: to display winners in all category
void diplayWinners(struct RiderInfo* info, int size) {

}

// lookupWinners: to display last 3 riders in the category
void lookupWinners(struct RiderInfo* info, int size) {

}
