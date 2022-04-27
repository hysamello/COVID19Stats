#pragma once
#include <stdbool.h>
#include "../ADT/ADTList/list.h"
#include "../ADT/ADTMap/map.h"
#include "../ADT/ADTMap/keyString.h"

/**
 * @brief This function splits a string into various fields inputted by the user.
 *
 * @param string The inputted string.
 * @param nFields The number of fields that will be split.
 * @param delim The delimiter thats wished to be used to split the string by.
 *
 * @return The inputted divided by the delimiter.
 */
char** split(char *string, int nFields, const char *delim);
/**
 * @brief Replaces a character of the string with the desired new character
 *
 * @param string The inputted string.
 * @param current The current character whoms't be replaced.
 * @param new The character which will take over it's position.
 *
 * @return Reformatted string.
 */
char* searchAndReplace(char *string, char current, char new);
/**
 * @brief Imports a PatientReport CSV file and converts it into a list.
 *
 * @param filename The inputted CSV file.
 * @param listPatients The list that's wished the be filled by the CSV.
 */
int importPatientsFromFile(char *filename, PtList *listPatients);

/**
 * @brief Imports a RegionReport CSV file and converts it into a map.
 *
 * @param filename The inputted CSV file.
 * @param listRegions The map that's wished the be filled by the CSV.
 */
int importRegionsFromFile(char *filename, PtMap *mapRegions);

/**
 * @brief Verify if exists patient with an ID
 * 
 * @param patients list
 * @param patient id 
 * @return patient position in list if patientexixts
 * @return INVALID_FIELD if does not exist
 */
int patientIdExists(PtList *list, long int id);

/**
 * @brief Gets rank of the last infected patient
 * 
 * @param patients list
 * @return rank of the list
 */
int mostRecentConfirmedPatientRank(PtList *list);

/**
 * @brief Turns an int on a char array
 * 
 * @param value 
 * @return char array
 */
char *intToString(int value);

/**
 * @brief Create an array by age gap 
 * 
 * @param patients list
 * @param minimum age
 * @param maximum age
 * @return array
 */
int *ageGapArray(PtList *list, int minAge, int maxAge);

/**
 * @brief Compares two strings
 * 
 * @param str1 
 * @param str2 
 * @return -1 if str1 is smaller
 * @return 0 if str1 equals str2
 * @return 1 if str1 is bigger
 */
int compareTo(void const *str1, void const *str2);
