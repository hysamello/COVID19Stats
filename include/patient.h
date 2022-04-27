#pragma once
#include "../include/date.h"

typedef struct patient{
	long int id;
	char sex[6];
	int birthYear;
	char country[40];
	char region[40];
	char infectionReason[100];
	long int infectedBy;
	Date confirmedDate;
	Date releasedDate;
	Date deceasedDate;
	char status[10];
} Patient;

/**
 * @brief Creates a instance of region
 *
 * @param id identification
 * @param sex sex
 * @param birthYear birth year
 * @param country country
 * @param region region
 * @param infectionReason infection reason
 * @param infectedBy by who was infectes
 * @param confirmedDate confimation date of infection
 * @param releasedDate releasement date
 * @param deceasedDate death date
 * @param status patient status
 * @return PtPatient created patient
 */
Patient patientCreate(long int id, char sex[6], int birthYear,char country[40], char region[40], char infectionReason[100], long int infectedBy, char *confirmedDate, char *releasedDate, char *deceasedDate, char status[10]);
/**
 * @brief Removes ending \r\n characters from status string.
 *
 * @param The status string.
 *
 * @return The trimmed string.
 */
char *statusClean(char *status);
/**
 * @brief Prints the patient information
 *
 * @param patient patient
 */
void patientPrint(Patient patient);
/**
 * @brief Calculates the patient age thorugh his birthYearh.
 *
 * @param patient The patient who we want to calculate the age.
 *
 * @return The calculated age.
 */
int patientAge(Patient patient);

/**
 * @brief Verify if patient's information is valid 
 * 
 * @param patient 
 * @return true is valid
 * @return false not valid
 */
bool validPatient(Patient patient);

/**
 * @brief Get the Infection Time of the patient
 * 
 * @param patient 
 * @return infection time
 */
int getInfectionTime(Patient patient);
