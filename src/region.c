#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/region.h"
#include "../include/utils.h"

Region regionCreate(char *name, char *capital, int population, float area)
{
	Region region;
	if (name != NULL && strlen(name) > 0 && capital != NULL && strlen(capital) > 0 && population >= 0 && area > 0.0)
	{
		strcpy(region.name, name);
		strcpy(region.capital, capital);
		region.population = population;
		region.area = area;
	}

	return region;
}

void regionPrint(Region *region)
{
	printf("%s;%s;%d;%.02f", region->name, region->capital, region->population, region->area);
}
