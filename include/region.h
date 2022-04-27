#pragma once

typedef struct region{
	char name[40];
	char capital[40];
	int population;
	float area;
} Region;

/**
 * @brief Creates instance of region
 *
 * @param name name
 * @param capital capital
 * @param population population
 * @param area area
 * @return Region created region
 */
Region regionCreate(char *name,char *capital, int population, float area);

/**
 * @brief Prints region information
 *
 * @param region region
 */
void regionPrint(Region *region);
