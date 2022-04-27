#include <stdio.h>
#include <stdlib.h>
#include "ADT/ADTList/listElem.h"
#include "ADT/ADTMap/keyString.h"
#include "ADT/ADTMap/mapElem.h"
#include "include/date.h"
#include "include/patient.h"
#include "include/region.h"
#include "include/utils.h"
#include "include/commandHandler.h"
#include "ADT/ADTList/list.h"
#include "ADT/ADTMap/map.h"

int main(){

	PtList patients;
	importPatientsFromFile("patients.csv",&patients);
	listDestroy(&patients);

	PtMap regions;
	importRegionsFromFile("regions.csv", &regions);
	mapDestroy(&regions);


	return EXIT_SUCCESS;
}
