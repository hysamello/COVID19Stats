/* PROJETO  ATAD 2019-20
 * Identificacao dos Alunos:
 *
 *      Numero: 190221039 | Nome: Hysa Mello de Alcântara
 *      Numero: 190221048 | Nome: Rafael da Rosa Marçalo
 *
 */
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ADT/ADTList/list.h"
#include "ADT/ADTMap/map.h"
#include "include/commandHandler.h"
#include "include/utils.h"

typedef char String[255];

/* definicao de prototipos de funcoes, definidas depois do main() */
int equalsStringIgnoreCase(char str1[], char str2[]);
void printCommandsMenu();

/*
 * Descrição do Programa
 * Um indexador de informações relativas
 * ao COVID 19.
 */
int main(int argc, char **argv)
{

	/* declaracao de variaveis */
	PtList patients;
	PtMap regions;
	int patCheck = ADT_NULL, regCheck = ADT_NULL, aux;

	/* interpretador de comandos */
	String command;
	int quit = 0;

	setlocale(LC_ALL, "PT");
	while (!quit)
	{

		printCommandsMenu();
		fgets(command, sizeof(command), stdin);
		command[strlen(command) - 1] = '\0';

		if (equalsStringIgnoreCase(command, "QUIT"))
		{
			quit = 1;
			if (patCheck == ADT_FULL)
			{
				clearPatients(&patients, &aux);
				listDestroy(&patients);
			}
			else
			{
				printf("No patient data available...");
			}

			if (regCheck == ADT_FULL)
			{
				clearRegions(&regions, &aux);
				mapDestroy(&regions);
			}
			else
			{
				printf("No regions data available...");
			}
		}
		else if (equalsStringIgnoreCase(command, "LOADP"))
		{
			if (patCheck != ADT_FULL)
			{
				patCheck = loadP(&patients);
			}
			else
			{
				printf("Patients already imported\n");
			}
		}
		else if (equalsStringIgnoreCase(command, "LOADR"))
		{
			if (regCheck != ADT_FULL)
			{
				regCheck = loadR(&regions);
			}
			else
			{
				printf("Regions already imported\n");
			}
		}
		else if (equalsStringIgnoreCase(command, "CLEAN"))
		{
			system("clear");
		}
		else if (equalsStringIgnoreCase(command, "CLEAR"))
		{
			int sizeList = 0, sizeMap = 0;
			if (patCheck == ADT_FULL)
			{
				patCheck = clearPatients(&patients, &sizeList);
				listDestroy(&patients);
			}

			if (regCheck == ADT_FULL)
			{
				regCheck = clearRegions(&regions, &sizeMap);
				mapDestroy(&regions);
			}
			printf("%d records deleted from < %d Patients | %d Regions >", sizeList + sizeMap, sizeList, sizeMap);
		}
		else if (equalsStringIgnoreCase(command, "LISTP"))
		{
			if (patCheck == ADT_FULL)
			{
				listPrint(patients);
			}
			else
			{
				printf("No patient data available...");
			}
		}
		else if (equalsStringIgnoreCase(command, "LISTR"))
		{
			if (regCheck == ADT_FULL)
			{
				mapPrint(regions);
			}
			else
			{
				printf("No regions data available...");
			}
		}
		else if (equalsStringIgnoreCase(command, "AVERAGE"))
		{
			if (patCheck == ADT_FULL)
			{
				average(&patients);
			}
			else
			{
				printf("No patient data available...");
			}
		}
		else if (equalsStringIgnoreCase(command, "FOLLOW"))
		{
			if (patCheck == ADT_FULL)
			{
				followPatient(&patients);
			}
			else
			{
				printf("No patient data available...");
			}
		}
		else if (equalsStringIgnoreCase(command, "SEX"))
		{
			if (patCheck == ADT_FULL)
			{
				sex(&patients);
			}
			else
			{
				printf("No patient data available...");
			}
		}
		else if (equalsStringIgnoreCase(command, "SHOW"))
		{
			if (patCheck == ADT_FULL)
			{
				show(&patients);
			}
			else
			{
				printf("No patient data available...");
			}
		}
		else if (equalsStringIgnoreCase(command, "TOP5"))
		{
			if (patCheck == ADT_FULL)
			{
				topFive(&patients);
			}
			else
			{
				printf("No patient data available...");
			}
		}
		else if (equalsStringIgnoreCase(command, "OLDEST"))
		{
			if (patCheck == ADT_FULL)
			{
				oldestPatients(&patients);
			}
			else
			{
				printf("No patient data available...");
			}
		}
		else if (equalsStringIgnoreCase(command, "GROWTH"))
		{
			if (patCheck == ADT_FULL)
			{
				growth(&patients);
			}
			else
			{
				printf("No patient data available...");
			}
		}
		else if (equalsStringIgnoreCase(command, "MATRIX"))
		{
			if (patCheck == ADT_FULL)
			{
				matrixGenerator(&patients);
			}
			else
			{
				printf("No patient data available...");
			}
		}
		else if (equalsStringIgnoreCase(command, "REGIONS"))
		{
			if (patCheck == ADT_FULL && regCheck == ADT_FULL)
			{
				regionsAlphaOrder(&regions, &patients);
			}
			else
			{
				printf("No patient/regions data available...");
			}
		}
		else if (equalsStringIgnoreCase(command, "REPORT"))
		{
			if (patCheck == ADT_FULL && regCheck == ADT_FULL)
			{
				reportMaker(&patients, &regions);
			}
			else
			{
				printf("No patient/regions data available...");
			}
		}
		else
		{
			printf("%s : Command not found.\n", command);
		}
	}
	return (EXIT_SUCCESS);
}

int equalsStringIgnoreCase(char str1[], char str2[])
{
	return (strcasecmp(str1, str2) == 0);
}

void printCommandsMenu()
{
	printf("\n\n===================================================================================");
	printf("\n                          PROJECT: COVID-19                    ");
	printf("\n===================================================================================");
	printf("\nA. Base Commands (LOADP, LOADR, CLEAN, CLEAR).");
	printf("\nB. Simple Indicators and searchs (AVERAGE, FOLLOW, LISTP, LISTR, MATRIX, OLDEST, GROWTH, SEX, SHOW, TOP5).");
	printf("\nC. Advanced indicator (REGIONS, REPORT)");
	printf("\nD. Exit (QUIT)\n\n");
	printf("COMMAND> ");
}
