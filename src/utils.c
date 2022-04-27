#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ADT/ADTMap/keyString.h"
#include "../include/commandHandler.h"
#include "../include/date.h"
#include "../include/patient.h"
#include "../include/region.h"
#include "../include/utils.h"

char **split(char *string, int nFields, const char *delim)
{
	char **tokens = (char **)malloc(sizeof(char *) * nFields);
	int index = 0, len = strlen(string);
	tokens[index++] = &string[0];
	for (int i = 0; i < len; i++)
	{
		if (string[i] == delim[0])
		{
			string[i] = '\0';
			if (i < len - 1)
			{
				tokens[index++] = &string[i] + 1;
			}
		}
	}
	return tokens;
}

char *searchAndReplace(char *string, char current, char new)
{
	for (int i = 0; i < strlen(string); i++)
	{
		if (string[i] == current && new == '\0')
		{
			for (int j = i; j < strlen(string); j++)
			{
				string[j] = string[j + 1];
			}
		}
		else if (string[i] == current)
		{
			string[i] = new;
		}
	}
	return string;
}

int importPatientsFromFile(char *filename, PtList *listPatients)
{
	FILE *f = NULL;

	f = fopen(filename, "r");

	if (f == NULL)
	{
		printf("File not found %s ...\n", filename);
		return ADT_INVALID;
	}

	char nextline[1024];

	int countPatients = 0;
	bool firstLine = true;

	*listPatients = listCreate(10);

	while (fgets(nextline, sizeof(nextline), f))
	{
		if (strlen(nextline) < 1)
		{
			continue;
		}

		if (firstLine)
		{
			firstLine = false;
			continue;
		}

		char **tokens = split(nextline, 11, ";");

		Patient patient = patientCreate(atol(tokens[0]), tokens[1], atoi(tokens[2]), tokens[3], tokens[4], tokens[5],
				atol(tokens[6]), tokens[7], tokens[8], tokens[9], tokens[10]);

		free(tokens);

		int error_code = listAdd(*listPatients, countPatients, patient);

		if (error_code == LIST_FULL || error_code == LIST_INVALID_RANK || error_code == LIST_NO_MEMORY ||
				error_code == LIST_NULL)
		{
			printf("An error ocurred... Please try again... \n");
			return ADT_INVALID;
		}
		countPatients++;
	}

	printf("%d Patients were read!\n", countPatients);
	fclose(f);
	return ADT_FULL;
}

int importRegionsFromFile(char *filename, PtMap *mapRegions)
{
	FILE *f = NULL;

	f = fopen(filename, "r");

	if (f == NULL)
	{
		printf("An error ocurred... It was not possible to open the file %s ...\n", filename);
		return ADT_INVALID;
	}

	char nextline[1024];

	int countRegions = 0;
	bool firstLine = true;

	*mapRegions = mapCreate(10);

	while (fgets(nextline, sizeof(nextline), f))
	{
		if (strlen(nextline) < 1)
		{
			continue;
		}

		if (firstLine)
		{
			firstLine = false;
			continue;
		}

		char **tokens = split(nextline, 4, ";");

		Region region = regionCreate(tokens[0], tokens[1], atoi(searchAndReplace(tokens[3], ',', '\0')),
				(float)atof(searchAndReplace(tokens[2], ',', '.')));

		KeyString ks = keyStringCreate(tokens[0]);
		int error_code = mapPut(*mapRegions, ks, region);

		if (error_code == MAP_NULL || error_code == MAP_NO_MEMORY || error_code == MAP_UNKNOWN_KEY ||
				error_code == MAP_FULL)
		{
			printf("An error ocurred... Please try again... \n");
			return ADT_INVALID;
		}
		countRegions++;
		free(tokens);
	}

	printf("%d Regions were read!\n", countRegions);
	fclose(f);
	return ADT_FULL;
}

int patientIdExists(PtList *list, long int id)
{
	int size = 0;
	ListElem elem;
	listSize(*list, &size);
	for (int i = 0; i < size; i++)
	{
		listGet(*list, i, &elem);
		if (elem.id == id)
		{
			return i;
		}
	}
	return INVALID_FIELD;
}

int mostRecentConfirmedPatientRank(PtList *list)
{
	int rank = INVALID_FIELD;
	if (list != NULL)
	{
		ListElem elem;
		int size = 0;
		long int date = -1;
		listSize(*list, &size);
		for (int i = 0; i < size; i++)
		{
			listGet(*list, i, &elem);
			if (toNumber(&elem.confirmedDate) >= date)
			{
				date = toNumber(&elem.confirmedDate);
				rank = i;
			}
		}
	}
	return rank;
}

char *intToString(int value)
{
	char *string = (char *)calloc(80, sizeof(char));
	if (value > -1)
	{
		sprintf(string, "%d", value);
	}
	else
	{
		strcpy(string, "Unknown");
	}
	return string;
}

int *ageGapArray(PtList *list, int minAge, int maxAge)
{
	int *fields = (int *)calloc(3, sizeof(int));
	fields[0] = 0;
	fields[1] = 0;
	fields[2] = 0;
	if (list != NULL)
	{
		ListElem elem;
		int size = 0;
		listSize(*list, &size);
		for (int i = 0; i < size; i++)
		{
			listGet(*list, i, &elem);
			if (patientAge(elem) >= minAge && maxAge == INVALID_FIELD)
			{
				if (strcmp(elem.status, "isolated") == 0)
				{
					fields[0]++;
				}
				else if (strcmp(elem.status, "deceased") == 0)
				{
					fields[1]++;
				}
				else if (strcmp(elem.status, "released") == 0)
				{
					fields[2]++;
				}
			}
			else if (minAge != INVALID_FIELD && maxAge != INVALID_FIELD && patientAge(elem) != INVALID_FIELD &&
					patientAge(elem) >= minAge && patientAge(elem) <= maxAge)
			{
				if (strcmp(elem.status, "isolated") == 0)
				{
					fields[0]++;
				}
				else if (strcmp(elem.status, "deceased") == 0)
				{
					fields[1]++;
				}
				else if (strcmp(elem.status, "released") == 0)
				{
					fields[2]++;
				}
			}
		}
	}
	return fields;
}

int compareTo(void const *str1, void const *str2)
{
	char *compStr1 = (char *)str1;
	char *compStr2 = (char *)str2;

	return strcmp(compStr1, compStr2);
}
