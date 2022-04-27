#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../ADT/ADTList/list.h"
#include "../ADT/ADTMap/map.h"
#include "../include/commandHandler.h"
#include "../include/utils.h"

int loadP(PtList *list)
{
	if (list != NULL)
	{
		char *filename = (char *)calloc(80, sizeof(char));
		printf("Patients file name: ");
		fgets(filename, 80, stdin);
		filename[strlen(filename) - 1] = '\0';
		int error = importPatientsFromFile(filename, list);
		free(filename);
		return error;
	}
	else
	{
		return ADT_NULL;
	}
	return ADT_EMPTY;
}

int loadR(PtMap *map)
{
	if (map != NULL)
	{
		char *filename = (char *)calloc(80, sizeof(char));
		printf("Regions file name: ");
		fgets(filename, 80, stdin);
		filename[strlen(filename) - 1] = '\0';
		int error = importRegionsFromFile(filename, map);
		free(filename);
		return error;
	}
	else
	{
		return ADT_NULL;
	}
	return ADT_EMPTY;
}

int clearPatients(PtList *list, int *size)
{
	int error = listSize(*list, size);
	if (error != LIST_NULL)
	{
		listClear(*list);
		return ADT_EMPTY;
	}
	else
	{
		return ADT_NULL;
	}
	return ADT_FULL;
}

int clearRegions(PtMap *map, int *size)
{
	int error = mapSize(*map, size);
	if (error != MAP_NULL)
	{
		mapClear(*map);
		return ADT_EMPTY;
	}
	else
	{
		return ADT_NULL;
	}
	return ADT_FULL;
}

void average(PtList *list)
{
	int size = 0;
	float qtdDec = 0, qtdRel = 0, qtdIso = 0, agesDec = 0, agesRel = 0, agesIso = 0;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	listSize(*list, &size);
	ListElem pat;
	for (int i = 0; i < size; i++)
	{
		listGet(*list, i, &pat);
		if (strcmp(pat.status, "deceased") == 0)
		{
			qtdDec++;
			agesDec += patientAge(pat);
		}
		if (strcmp(pat.status, "released") == 0)
		{
			qtdRel++;
			agesRel += patientAge(pat);
		}
		if (strcmp(pat.status, "isolated") == 0)
		{
			qtdIso++;
			agesIso += patientAge(pat);
		}
	}
	printf("Average Age for deceased patients: %.2f\n", agesDec / qtdDec);
	printf("Average Age for released patients: %.2f\n", agesRel / qtdRel);
	printf("Average Age for isolated patients: %.2f\n", agesIso / qtdIso);
}

void followPatient(PtList *list)
{
	int size = 0, loop = 0;
	ListElem patient;
	char *id = (char *)calloc(80, sizeof(char));
	printf("Patient ID: ");
	fgets(id, 80, stdin);
	id[strlen(id) - 1] = '\0';
	long int patId = atol(id);
	free(id);
	int rank = patientIdExists(list, patId);

	int error = listSize(*list, &size);
	if (error != LIST_NULL)
	{
		if (!listIsEmpty(*list))
		{
			if (rank >= 0)
			{
				printf("Following ");
				while (loop == 0)
				{
					rank = patientIdExists(list, patId);
					if (rank >= 0)
					{
						listGet(*list, rank, &patient);
						printf("Patient: ID:%ld, SEX: %s, AGE: %d, "
								"COUNTRY/REGION: %s / %s, STATE: %s \n",
								patient.id, patient.sex, patientAge(patient), patient.country, patient.region,
								patient.status);
						if (patient.infectedBy > 0)
						{
							if (patientIdExists(list, patient.infectedBy) > 0)
							{
								patId = patient.infectedBy;
								printf("contaminated by ");
							}
							else
							{
								printf("contaminated Patient: ID: %ld : does "
										"not exist record\n",
										patient.infectedBy);
								loop = 1;
							}
						}
						else
						{
							printf("contaminated by: Unknown\n");
							loop = 1;
						}
					}
					else
					{
						printf("contaminated by: Unknown\n");
						loop = 1;
					}
				}
			}
			else
			{
				printf("Unknown Patient");
			}
		}
	}
}

void sex(PtList *list)
{
	int size = 0;
	float fem = 0, male = 0, ukn = 0;
	listSize(*list, &size);
	ListElem pat;
	for (int i = 0; i < size; i++)
	{
		listGet(*list, i, &pat);
		if (strcmp(pat.sex, "female") == 0)
		{
			fem++;
		}
		else if (strcmp(pat.sex, "male") == 0)
		{
			male++;
		}
		else
		{
			ukn++;
		}
	}
	printf("Percentage of Females: %d%%\n", (int)round(fem * 100 / size));
	printf("Percentage of Males: %d%%\n", (int)round(male * 100 / size));
	printf("Percentage of Unknown: %d%%\n", (int)round(ukn * 100 / size));
	printf("Total of patients: %d", size);
}

void show(PtList *list)
{
	int size = 0;
	char *id = (char *)calloc(80, sizeof(char));
	printf("Patient ID: ");
	fgets(id, 80, stdin);
	id[strlen(id) - 1] = '\0';
	long int patId = atol(id);
	free(id);

	int error = listSize(*list, &size);
	if (error != LIST_NULL)
	{
		if (!listIsEmpty(*list))
		{
			if (patientIdExists(list, patId) > 0)
			{
				int patientRank = patientIdExists(list, patId);
				int diff = -1;
				ListElem patient;
				listGet(*list, patientRank, &patient);
				if (getInfectionTime(patient) > 0)
				{
					diff = getInfectionTime(patient);
				}
				else if (strcmp(patient.status, "isolated") == 0)
				{
					ListElem aux;
					listGet(*list, mostRecentConfirmedPatientRank(list), &aux);
					diff = dayDifference(&patient.confirmedDate, &aux.confirmedDate);
				}
				char *days = intToString(diff);
				printf("ID: %ld\nSEX: %s\nAGE: %d\nCOUNTRY/REGION: %s / "
						"%s\nINFECTION REASON: %s\nSTATE: %s\nNUMBER OF DAYS "
						"WITH ILLNESS: %s\n",
						patient.id, patient.sex, patientAge(patient), patient.country, patient.region,
						patient.infectionReason, patient.status, days);
				free(days);
			}
			else
			{
				printf("Unexistant Patient\n");
			}
		}
	}
}

void topFive(PtList *list)
{
	if (list != NULL)
	{
		ListElem one, two, three, four, five, aux;
		int rankOne, rankTwo, rankThree, rankFour, rankFive;
		rankOne = rankTwo = rankThree = rankFour = rankFive = 0;

		int size = 0;
		listSize(*list, &size);

		for (int i = 0; i < size; i++)
		{
			listGet(*list, i, &aux);
			if (validPatient(aux) == 1 && getInfectionTime(aux) > rankOne && strcmp(aux.status, "deceased") != 0 &&
					strcmp(aux.status, "isolated") != 0)
			{
				rankOne = getInfectionTime(aux);
				listGet(*list, i, &one);
			}
			else if (validPatient(aux) == 1 && getInfectionTime(aux) == rankOne &&
					strcmp(aux.status, "deceased") != 0 && strcmp(aux.status, "isolated") != 0)
			{
				if (patientAge(one) < patientAge(aux))
				{
					rankOne = getInfectionTime(aux);
					listGet(*list, i, &one);
				}
			}
		}

		for (int i = 0; i < size; i++)
		{
			listGet(*list, i, &aux);
			if (getInfectionTime(aux) > rankTwo && aux.id != one.id && strcmp(aux.status, "deceased") != 0 &&
					strcmp(aux.status, "isolated") != 0)
			{
				rankTwo = getInfectionTime(aux);
				listGet(*list, i, &two);
			}
			else if (getInfectionTime(aux) == rankTwo && aux.id != one.id && strcmp(aux.status, "deceased") != 0 &&
					strcmp(aux.status, "isolated") != 0)
			{
				if (patientAge(two) < patientAge(aux))
				{
					rankTwo = getInfectionTime(two);
					listGet(*list, i, &two);
				}
			}
		}

		for (int i = 0; i < size; i++)
		{
			listGet(*list, i, &aux);
			if (getInfectionTime(aux) > rankThree && aux.id != one.id && aux.id != two.id &&
					strcmp(aux.status, "deceased") != 0 && strcmp(aux.status, "isolated") != 0)
			{
				rankThree = getInfectionTime(aux);
				listGet(*list, i, &three);
			}
			else if (getInfectionTime(aux) == rankThree && aux.id != one.id && aux.id != two.id &&
					strcmp(aux.status, "deceased") != 0 && strcmp(aux.status, "isolated") != 0)
			{
				if (patientAge(three) < patientAge(aux))
				{
					rankThree = getInfectionTime(three);
					listGet(*list, i, &three);
				}
			}
		}

		for (int i = 0; i < size; i++)
		{
			listGet(*list, i, &aux);
			if (getInfectionTime(aux) > rankFour && aux.id != one.id && aux.id != two.id && aux.id != three.id &&
					strcmp(aux.status, "deceased") != 0 && strcmp(aux.status, "isolated") != 0)
			{
				rankFour = getInfectionTime(aux);
				listGet(*list, i, &four);
			}
			else if (getInfectionTime(aux) == rankFour && aux.id != one.id && aux.id != two.id && aux.id != three.id &&
					strcmp(aux.status, "deceased") != 0 && strcmp(aux.status, "isolated") != 0)
			{
				if (patientAge(four) < patientAge(aux))
				{
					rankFour = getInfectionTime(four);
					listGet(*list, i, &four);
				}
			}
		}

		for (int i = 0; i < size; i++)
		{
			listGet(*list, i, &aux);
			if (getInfectionTime(aux) > rankFive && aux.id != one.id && aux.id != two.id && aux.id != three.id &&
					aux.id != four.id && strcmp(aux.status, "deceased") != 0 && strcmp(aux.status, "isolated") != 0)
			{
				rankFive = getInfectionTime(aux);
				listGet(*list, i, &five);
			}
			else if (getInfectionTime(aux) == rankFive && aux.id != one.id && aux.id != two.id && aux.id != three.id &&
					aux.id != four.id && strcmp(aux.status, "deceased") != 0 && strcmp(aux.status, "isolated") != 0)
			{
				if (patientAge(five) < patientAge(aux))
				{
					rankFive = getInfectionTime(five);
					listGet(*list, i, &five);
				}
			}
		}

		char *oneString = intToString(patientAge(one));
		char *twoString = intToString(patientAge(two));
		char *threeString = intToString(patientAge(three));
		char *fourString = intToString(patientAge(four));
		char *fiveString = intToString(patientAge(five));

		printf("ID: %ld\nSEX: %s\nAGE: %s\nCOUNTRY/REGION: %s / %s\nINFECTION "
				"REASON: %s\nSTATE: %s\nNUMBER OF DAYS WITH ILLNESS: %d\n\n",
				one.id, one.sex, oneString, one.country, one.region,
				(strcmp(one.infectionReason, "") == 0) ? "Unknown" : one.infectionReason, one.status,
				getInfectionTime(one));
		printf("ID: %ld\nSEX: %s\nAGE: %s\nCOUNTRY/REGION: %s / %s\nINFECTION "
				"REASON: %s\nSTATE: %s\nNUMBER OF DAYS WITH ILLNESS: %d\n\n",
				two.id, two.sex, twoString, two.country, two.region,
				(strcmp(two.infectionReason, "") == 0) ? "Unknown" : two.infectionReason, two.status,
				getInfectionTime(two));
		printf("ID: %ld\nSEX: %s\nAGE: %s\nCOUNTRY/REGION: %s / %s\nINFECTION "
				"REASON: %s\nSTATE: %s\nNUMBER OF DAYS WITH ILLNESS: %d\n\n",
				three.id, three.sex, threeString, three.country, three.region,
				(strcmp(three.infectionReason, "") == 0) ? "Unknown" : three.infectionReason, three.status,
				getInfectionTime(three));
		printf("ID: %ld\nSEX: %s\nAGE: %s\nCOUNTRY/REGION: %s / %s\nINFECTION "
				"REASON: %s\nSTATE: %s\nNUMBER OF DAYS WITH ILLNESS: %d\n\n",
				four.id, four.sex, fourString, four.country, four.region,
				(strcmp(four.infectionReason, "") == 0) ? "Unknown" : four.infectionReason, four.status,
				getInfectionTime(four));
		printf("ID: %ld\nSEX: %s\nAGE: %s\nCOUNTRY/REGION: %s / %s\nINFECTION "
				"REASON: %s\nSTATE: %s\nNUMBER OF DAYS WITH ILLNESS: %d\n",
				five.id, five.sex, fiveString, five.country, five.region,
				(strcmp(five.infectionReason, "") == 0) ? "Unknown" : five.infectionReason, five.status,
				getInfectionTime(five));

		free(oneString);
		free(twoString);
		free(threeString);
		free(fourString);
		free(fiveString);
	}
}

void oldestPatients(PtList *list)
{
	if (list != NULL)
	{
		int size = 0, femaleAge = 0, maleAge = 0, order = 0;
		listSize(*list, &size);
		ListElem female, male;

		for (int i = 0; i < size; i++)
		{
			listGet(*list, i, &female);
			if (patientAge(female) > femaleAge && strcmp(female.sex, "female") == 0)
			{
				femaleAge = patientAge(female);
			}
		}

		for (int i = 0; i < size; i++)
		{
			listGet(*list, i, &male);
			if (patientAge(male) > maleAge && strcmp(male.sex, "male") == 0)
			{
				maleAge = patientAge(male);
			}
		}

		printf("FEMALE:\n");
		for (int i = 0; i < size; i++)
		{
			listGet(*list, i, &female);
			if (patientAge(female) == femaleAge && strcmp(female.sex, "female") == 0)
			{
				++order;
				printf("%d - ID: %ld, SEX:%s, AGE: %d, COUNTRY/REGION: %s / "
						"%s, STATE: %s\n",
						order, female.id, female.sex, patientAge(female), female.country, female.region, female.status);
			}
		}

		order = 0;
		printf("MALE:\n");
		for (int i = 0; i < size; i++)
		{
			listGet(*list, i, &male);
			if (patientAge(male) == maleAge && strcmp(male.sex, "male") == 0)
			{
				++order;
				printf("%d - ID: %ld, SEX:%s, AGE: %d, COUNTRY/REGION: %s / "
						"%s, STATE: %s\n",
						order, male.id, male.sex, patientAge(male), male.country, male.region, male.status);
			}
		}
	}
}

void growth(PtList *list)
{
	if (list != NULL)
	{
		int size = 0;
		char *actualDate = (char *)calloc(12, sizeof(char));
		printf("Date: ");
		fgets(actualDate, 12, stdin);
		actualDate[strlen(actualDate) - 1] = '\0';
		Date date = toDate(actualDate);

		listSize(*list, &size);

		ListElem el1;

		Date dayBefore = theDayBefore(&date);
		datePrint(&dayBefore);
		int actualDead = 0, actualConf = 0, beforeDead = 0, beforeConf = 0, general = 0;
		for (int i = 0; i < size; i++)
		{
			listGet(*list, i, &el1);
			if (dateCompare(el1.deceasedDate, date))
			{
				actualDead++;
			}
			else if (dateCompare(el1.deceasedDate, dayBefore))
			{
				beforeDead++;
			}
			if (dateCompare(el1.confirmedDate, date))
			{
				actualConf++;
			}
			if (dateCompare(el1.confirmedDate, dayBefore))
			{
				beforeConf++;
			}
			general++;
		}

		double growthConf = round((double)(actualConf - beforeConf) / beforeConf * 100);
		double growthDead = round((double)(actualDead - beforeDead) / beforeDead * 100);

		printf("\nDate: <");
		datePrint(&dayBefore);
		printf(">");
		printf("\nNumber of dead : %d", beforeDead);
		printf("\nNumber of isolated : %d", beforeConf);

		printf("\n\nDate: <");
		datePrint(&date);
		printf(">");
		printf("\nNumber of dead : %d", actualDead);
		printf("\nNumber of isolated : %d", actualConf);

		printf("\n\nRate of new infected: %.0f%%", growthConf);
		printf("\nRate of new dead: %.0f%%", growthDead);

		free(actualDate);
	}
}

void matrixGenerator(PtList *list)
{
	if (list != NULL)
	{
		int *fieldsOne = ageGapArray(list, 0, 15);
		int *fieldsTwo = ageGapArray(list, 16, 30);
		int *fieldsThree = ageGapArray(list, 31, 45);
		int *fieldsFour = ageGapArray(list, 46, 60);
		int *fieldsFive = ageGapArray(list, 61, 75);
		int *fieldsSix = ageGapArray(list, 76, INVALID_FIELD);

		printf("|%s\t|%s\t|%s\t|%s\t|\n", "Age Gap", "Isolated", "Deceased", "Released");
		printf("|%-10s\t|%-10d\t|%-10d\t|%-10d\t|\n", "[0-15]", fieldsOne[0], fieldsOne[1], fieldsOne[2]);
		printf("|%-10s\t|%-10d\t|%-10d\t|%-10d\t|\n", "[16-30]", fieldsTwo[0], fieldsTwo[1], fieldsTwo[2]);
		printf("|%-10s\t|%-10d\t|%-10d\t|%-10d\t|\n", "[31-45]", fieldsThree[0], fieldsThree[1], fieldsThree[2]);
		printf("|%-10s\t|%-10d\t|%-10d\t|%-10d\t|\n", "[46-60]", fieldsFour[0], fieldsFour[1], fieldsFour[2]);
		printf("|%-10s\t|%-10d\t|%-10d\t|%-10d\t|\n", "[61-75]", fieldsFive[0], fieldsFive[1], fieldsFive[2]);
		printf("|%-10s\t|%-10d\t|%-10d\t|%-10d\t|\n", "[76-...]", fieldsSix[0], fieldsSix[1], fieldsSix[2]);

		free(fieldsOne);
		free(fieldsTwo);
		free(fieldsThree);
		free(fieldsFour);
		free(fieldsFive);
		free(fieldsSix);
	}
}

void regionsAlphaOrder(PtMap *regions, PtList *patients)
{
	int pSize = 0;
	listSize(*patients, &pSize);
	ListElem el1;

	int mSize = 0;
	mapSize(*regions, &mSize);

	KeyString *mkaux = (MapKey *)calloc(mSize + 1, sizeof(MapKey));

	KeyString *mk = mapKeys(*regions);

	for (int i = 0; i < mSize + 1; i++)
	{
		for (int j = 0; j < pSize; j++)
		{
			listGet(*patients, j, &el1);
			if (strcmp(el1.region, mk[i].str) == 0)
			{
				if (strcmp(el1.status, "isolated") == 0)
				{
					mkaux[i] = mk[i];
				}
			}
		}
	}

	qsort(mkaux, mSize, sizeof(MapKey), compareTo);

	for (int i = 0; i < mSize + 1; i++)
	{
		keyStringPrint(mkaux[i]);
		printf("\n");
	}

	free(mk);
	free(mkaux);
}

void reportMaker(PtList *list, PtMap *map)
{
	if (list != NULL && map != NULL)
	{
		FILE *report;
		report = fopen("report.txt", "w");
		if (report != NULL)
		{
			printf("Report created\n");
			int mSize = 0, lSize = 0;
			float mortality = 0, infected = 0, incidentRate = 0, lethality = 0;
			MapValue value;
			MapKey *keys = mapKeys(*map);
			ListElem el1;

			KeyString mk;

			mapSize(*map, &mSize);
			listSize(*list, &lSize);
			double dead = 0, iso = 0, total = 0;

			for (int j = 0; j < lSize; j++)
			{
				listGet(*list, j, &el1);
				mk = keyStringCreate(el1.region);
				if (strcmp(el1.status, "isolated") == 0)
				{
					iso++;
					total++;
				}
				if (strcmp(el1.status, "deceased") == 0)
				{
					dead++;
					total++;
				}
			}

			mapGet(*map, keys[0], &value);

			fprintf(report, "%-20s \tMortality %f%% \tIncidentRate: %f%% \tLethality %f%%\n", keys[0].str,
					(double)(dead / value.population * 10000), (double)(iso / value.population * 100),
					(double)(dead / lSize * 100));

			for (int i = 1; i < mSize; i++)
			{
				dead = 0, iso = 0, total = 0;
				for (int j = 0; j < lSize; j++)
				{
					listGet(*list, j, &el1);
					mk = keyStringCreate(el1.region);
					if (strcmp(keys[i].str, mk.str) == 0)
					{
						if (strcmp(el1.status, "isolated") == 0)
						{
							iso++;
						}
						if (strcmp(el1.status, "deceased") == 0)
						{
							dead++;
						}
						total++;
					}
				}
				mapGet(*map, keys[i], &value);
				fprintf(report,
						"%-20s \tMortality %f%% \tIncidentRate: %f%% "
						"\tLethality %f%%\n",
						keys[i].str, (double)(dead / value.population * 10000), (double)(iso / value.population * 100),
						(double)(dead / total * 100));
			}
			free(keys);
		}
		else
		{
			printf("Report not created\n");
		}
		fclose(report);
	}
}
