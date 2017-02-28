#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <allocators>


void printMenu();
void writeData();
void readData();
void findRecord(int recordNumber);

struct result
{
	int ID;
	char surname[20];
	char firstname[20];
	char english, maths, french, philosophy;
	struct result *next;
};
struct result *first;


void  main(void)
{
	int id;

	writeData();
	readData();
	printf("To exit enter 0\n");
	do
	{
		printf("Enter which ID you want: ");
		scanf("%d", &id);
		findRecord(id);
	} while (id != 0);

}


void writeData()
{
	FILE *fp;
	int i = 0, j;
	struct result results[] = { { 137,"Elsie","Barton", 'A','A','B','A' },{ 108,"Hazel","Bender",'A','B','A','A' },{ 102,"Paige","Chen",'D','D','A','D' },{ 101,"Kristina","Chung",'D','B','B','A' } };
	fp = fopen("C:\\Users\\sndri\\Documents\\results.dat", "wb+");
	for (j = 0; j < 4; j++)
	{
		fwrite(&results[j], sizeof(result), 1, fp);
	}
	fclose(fp);
}

void readData()
{
	FILE *ptr;
	struct result *last = NULL;
	struct result *current = NULL;

	ptr = fopen("C:\\Users\\sndri\\Documents\\results.dat", "r");

	while (!feof(ptr))
	{
		if (first == NULL)
		{
			first = (struct result*)malloc(sizeof(result));
			first->next = NULL;
			current = first;
		}
		else
		{
			last = (struct result*)malloc(sizeof(result));
			current->next = last;
			current = last;
			last->next = NULL;
		}
		fread(current, sizeof(result), 1, ptr);
	}
	fclose(ptr);
}

void findRecord(int id)
{
	struct result *current;
	current = first;

	while (current != NULL)
	{
		if (current->ID == id)
		{
			printf("\n%d: %s %s: English<%c> Maths<%c> French<%c> Philosophy<%c>\n",
				current->ID,
				current->firstname,
				current->surname,
				current->english,
				current->maths,
				current->french,
				current->philosophy);
			return;
		}
		current = current->next;
	}
}