#pragma once
#include "../ADT/ADTList/list.h"
#include "../ADT/ADTMap/map.h"

#define INVALID_FIELD   -1
#define ADT_OK	        0
#define ADT_NULL	    1
#define ADT_EMPTY   	2
#define ADT_FULL        3
#define ADT_INVALID     4

/**
 * @brief Loads the patients file
 *
 * Complexidade O(n)
 *
 * @param list list to receive the patients
 * @return ADT_NULL if list is null
 * @return ADT_EMPTY if nothing done
 * @return ADT_OK if successful
 * @return ADT_INVALID if not possible to read the file
 */
int loadP(PtList *list);

/**
 * @brief Loads the regions file
 *
 * Complexidade O(n)
 *
 * @param list list to receive the regions
 * @return ADT_NULL if map is null
 * @return ADT_EMPTY if nothing done
 * @return ADT_OK if successful
 * @return ADT_INVALID if not possible to read the file
 */
int loadR(PtMap *map);

/**
 * @brief Clear the patients file
 *
 * @param list list to have patients cleaned
 * @return ADT_EMPTY if nothing done
 * @return ADT_FULL if successful
 * @return ADT_NULL if there are no patients
 */
int clearPatients(PtList *list, int *size);

/**
 * @brief Clear the regions file
 *
 * @param list list to have regions cleaned
 * @return ADT_EMPTY if nothing done
 * @return ADT_FULL if successful
 * @return ADT_NULL if there are no regions
 */
int clearRegions(PtMap *map, int *size);

/**
 * @brief Shows average age from patients
 *
 * Complexidade O(n)
 *
 * @param patients list
 */
void average(PtList *list);

/**
 * @brief Shows contamination sequence of a patient
 *
 * Complexidade O(n)
 *
 * @param patients list
 */
void followPatient(PtList *list);

/**
 * @brief Shows patients percentage by sex
 *
 * Complexidade O(n²)
 *
 * @param patients list
 */
void sex(PtList *list);

/**
 * @brief Shows data of a chosen patient
 *
 * Complexidade O(n)
 *
 * @param patients list
 */
void show(PtList *list);

/**
 * @brief Shows the 5 patients that took longer to recover, descending order
 *
 * Complexidade O(n)
 *
 * @param patients list
 */
void topFive(PtList *list);

/**
 * @brief Shows the oldest patients of each sex
 *
 * Complexidade O(n)
 *
 * @param patients list
 */
void oldestPatients(PtList *list);

/**
 * @brief Shows growth tax of deseased and infected, given a date
 *
 * Complexidade O(n)
 *
 * @param patients list
 */
void growth(PtList *list);

/**
 * @brief Creates a matrix with information of infected by age
 *
 * Complexidade O(n)
 *
 * @param patients list
 */
void matrixGenerator(PtList *list);

/**
 * @brief Shows the regions that still have patients unreleased,
 *           descending order
 *
 * Complexidade O(n²)
 *
 * @param regions map
 * @param patients list
 */
void regionsAlphaOrder(PtMap *regions, PtList *patients);

/**
 * @brief Creates a file with information about the desease by region
 *
 * Complexidade O(n³)
 *
 * @param patients list
 * @param regions map
 */
void reportMaker(PtList *list, PtMap *map);
