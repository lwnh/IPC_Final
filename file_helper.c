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
				printf("Race Management System: terminated");
				flag = 0;
			}
			printf("\n");
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
		printf("Succeeded to load a file\n\n");
		setRaceTime(info, MAXRECORDS);
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

// getCategory: to prompt users to choose one of the categories
char getCategory(void)
{
	printf("Which category (S, M, L): ");
	return checkCategory();
}

// checkCategory: to check if the input-word is between s/S, m/M, l/L 
char checkCategory(void)
{
	char input, inputNL, category = '\0';
	int flag = 1;

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
			category = toupper(input);
		}
	}
	printf("\n");
	return category;
}

// getAgeGroup
char* getAgeGroup(int age)
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

// convertTime: to convert time human-readable
void convertTime(double time, int* hour, int* minute)
{
	*hour = (int)time;
	*minute = (int)((time - *hour) * 60);
}

// setRaceTime : to store calculated race time
void setRaceTime(struct RiderInfo* info, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		info[i].raceTime = (info[i].finishTime - info[i].startTime) + 0.005;
	}
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

	category = getCategory();
	displayHeaderall();
	sortRiders(info, size);

	for (i = 0; i < size; i++)
	{
		if (info[i].raceLength == category)
		{
			printf("%-21s", info[i].name);
			printf("%9s", getAgeGroup(info[i].age));
			if (info[i].withdrawn)
			{
				printf("    N/A");
			}
			else
			{
				convertTime(info[i].raceTime, &hour, &minute);
				printf("%4d:%02d", hour, minute);
			}
			printf("%11s\n", checkWithdraw(info[i].withdrawn));
		}
	}
}

// displayTopriders: to display top 3 riders in the category
void displayTopriders(struct RiderInfo* info, int size)
{
	char category;
	int i, hour = 0, minute = 0, count = 0;

	category = getCategory();
	displayHeadertoplast();
	sortRiders(info, size);

	for (i = 0; i < size; i++)
	{
		if (info[i].raceLength == category && count < 3 && info[i].withdrawn == 0)
		{
			printf("%-21s", info[i].name);
			printf("%9s", getAgeGroup(info[i].age));
			convertTime(info[i].raceTime, &hour, &minute);
			printf("%4d:%02d\n", hour, minute);
			count++;
		}
	}
}

// sortRiders
void sortRiders(struct RiderInfo* info, int size)
{
	int i, j;
	struct RiderInfo temp;

	for (i = 0; i < size - 1; i++)
	{
		for (j = i + 1; j < size; j++)
		{
			if (info[i].raceTime > info[j].raceTime)
			{
				temp = info[i];
				info[i] = info[j];
				info[j] = temp;
			}
		}
	}
}

// displayLastriders: to display last 3 riders in the category
void displayLastriders(struct RiderInfo* info, int size)
{
	char category;
	int i, hour = 0, minute = 0, count = 0;

	category = getCategory();
	displayHeadertoplast();
	RsortRiders(info, size);

	for (i = 0; i < size; i++)
	{
		if (info[i].raceLength == category && count < 3 && info[i].withdrawn == 0)
		{
			printf("%-21s", info[i].name);
			printf("%9s", getAgeGroup(info[i].age));
			convertTime(info[i].raceTime, &hour, &minute);
			printf("%4d:%02d\n", hour, minute);
			count++;
		}
	}
}

void RsortRiders(struct RiderInfo* info, int size)
{
	int i, j;
	struct RiderInfo temp;

	for (i = 0; i < size - 1; i++)
	{
		for (j = i + 1; j < size; j++)
		{
			if (info[i].raceTime < info[j].raceTime)
			{
				temp = info[j];
				info[j] = info[i];
				info[i] = temp;
			}
		}
	}
}

// to display the winner in the S length
void displaySwinner(struct RiderInfo* info, int size)
{
	int i, winner = 0, hour, minute, flag = 0;

	for (i = 0; i < size; i++)
	{
		if (info[i].raceLength == 'S' && info[i].withdrawn == 0)
		{
			if (flag == 0)
			{
				winner = i;
				flag = 1;
			}
			else
			{
				if (info[i].raceTime < info[winner].raceTime)
				{
					winner = i;
				}
			}
		}
	}

	//printf("Rider                Age Group   Category   Time\n");
	printf("%-21s", info[winner].name);
	printf("%9s", getAgeGroup(info[winner].age));
	printf("      50 km");
	convertTime(info[winner].raceTime, &hour, &minute);
	printf("%4d:%02d\n", hour, minute);
}

// to display the winner in the M length
void displayMwinner(struct RiderInfo* info, int size)
{
	int i, winner = 0, hour, minute, flag = 0;

	for (i = 0; i < size; i++)
	{
		if (info[i].raceLength == 'M' && info[i].withdrawn == 0)
		{
			if (flag == 0)
			{
				winner = i;
				flag = 1;
			}
			else
			{
				if (info[i].raceTime < info[winner].raceTime)
				{
					winner = i;
				}
			}
		}
	}

	//printf("Rider                Age Group   Category   Time\n");
	printf("%-21s", info[winner].name);
	printf("%9s", getAgeGroup(info[winner].age));
	printf("      75 km");
	convertTime(info[winner].raceTime, &hour, &minute);
	printf("%4d:%02d\n", hour, minute);
}

// to display the winner in the L length
void displayLwinner(struct RiderInfo* info, int size)
{
	int i, winner = 0, hour, minute, flag = 0;

	for (i = 0; i < size; i++)
	{
		if (info[i].raceLength == 'L' && info[i].withdrawn == 0)
		{
			if (flag == 0)
			{
				winner = i;
				flag = 1;
			}
			else
			{

				if (info[i].raceTime < info[winner].raceTime)
				{
					winner = i;
				}
			}
		}
	}

	//printf("Rider                Age Group   Category   Time\n");
	printf("%-21s", info[winner].name);
	printf("%9s", getAgeGroup(info[winner].age));
	printf("     100 km");
	convertTime(info[winner].raceTime, &hour, &minute);
	printf("%4d:%02d\n", hour, minute);
}

// to display winners in all category
void diplayWinners(struct RiderInfo* info, int size)
{
	displayHeaderwinner();
	displaySwinner(info, size);
	displayMwinner(info, size);
	displayLwinner(info, size);
}
