#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/commandHandler.h"
#include "../include/date.h"
#include "../include/patient.h"

Patient patientCreate(long int id, char *sex, int birthYear, char *country, char *region, char *infectionReason,
		long int infectedBy, char *confirmedDate, char *releasedDate, char *deceasedDate, char *status)
{
	Patient patient;

	if (id > 0)
	{
		patient.id = id;
	}
	else
	{
		patient.id = -1;
	}

	if (sex != NULL && (strcmp(sex, "male") == 0 || strcmp(sex, "female") == 0))
	{
		strcpy(patient.sex, sex);
	}
	else
	{
		strcpy(patient.sex, "");
	}

	if (birthYear > 0)
	{
		patient.birthYear = birthYear;
	}
	else
	{
		patient.birthYear = -1;
	}

	if (country != NULL && strlen(country) > 0)
	{
		strcpy(patient.country, country);
	}
	else
	{
		strcpy(patient.country, "");
	}

	if (region != NULL && strlen(region) > 0)
	{
		strcpy(patient.region, region);
	}
	else
	{
		strcpy(patient.region, "");
	}

	if (infectionReason != NULL && strlen(infectionReason) > 0)
	{
		strcpy(patient.infectionReason, infectionReason);
	}
	else
	{
		strcpy(patient.infectionReason, "");
	}

	if (infectedBy > 0)
	{
		patient.infectedBy = infectedBy;
	}
	else
	{
		patient.infectedBy = -1;
	}

	if (status != NULL && strlen(status) > 0 &&
			(strcmp(status, "isolated\r\n") == 0 || strcmp(status, "released\r\n") == 0 ||
			 strcmp(status, "deceased\r\n") == 0))
	{
		strcpy(patient.status, statusClean(status));
	}
	else
	{
		strcpy(patient.status, "");
	}

	Date date1 = toDate(confirmedDate);
	Date date2 = toDate(releasedDate);
	Date date3 = toDate(deceasedDate);
	patient.confirmedDate = date1;
	patient.releasedDate = date2;
	patient.deceasedDate = date3;
	return patient;
}

char *statusClean(char *status)
{
	status[strlen(status) - 2] = '\0';
	return status;
}

void patientPrint(Patient patient)
{
	char *confirmed = toString(&(patient.confirmedDate));
	char *released = toString(&(patient.releasedDate));
	char *deceased = toString(&(patient.deceasedDate));
	printf("%ld;%s;%d;%s;%s;%s;%ld;%s;%s;%s;%s\n", patient.id, patient.sex, patient.birthYear, patient.country,
			patient.region, patient.infectionReason, patient.infectedBy, confirmed, released, deceased, patient.status);
	free(confirmed);
	free(released);
	free(deceased);
}

int patientAge(Patient patient)
{
	if (patient.birthYear > 0)
	{
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		return (1900 + tm.tm_year) - patient.birthYear;
	}
	return INVALID_FIELD;
}

bool validPatient(Patient patient)
{
	char *confirmed = toString(&patient.confirmedDate);
	char *released = toString(&patient.releasedDate);
	char *deceased = toString(&patient.deceasedDate);
	if (strcmp(confirmed, "00/00/00") != 0 && strcmp(released, "00/00/00") != 0)
	{
		free(confirmed);
		free(released);
		free(deceased);
		return true;
	}
	else if (strcmp(confirmed, "00/00/00") != 0 && strcmp(deceased, "00/00/00") != 0)
	{
		free(confirmed);
		free(released);
		free(deceased);
		return true;
	}
	free(confirmed);
	free(released);
	free(deceased);
	return false;
}

int getInfectionTime(Patient patient)
{
	int diff = INVALID_FIELD;
	char *confirmed = toString(&patient.confirmedDate);
	char *released = toString(&patient.releasedDate);
	char *deceased = toString(&patient.deceasedDate);
	if (strcmp(confirmed, "00/00/00") != 0 && strcmp(released, "00/00/00") != 0)
	{
		diff = dayDifference(&patient.confirmedDate, &patient.releasedDate);
	}
	else if (strcmp(confirmed, "00/00/00") != 0 && strcmp(deceased, "00/00/00") != 0)
	{
		diff = dayDifference(&patient.confirmedDate, &patient.deceasedDate);
	}
	free(confirmed);
	free(released);
	free(deceased);
	return diff;
}
