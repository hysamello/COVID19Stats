/**
 * @file mapElem.c
 * @brief Implements operations for types MapKey and MapValue.
 *
 * @author Bruno Silva (brunomnsilva@gmail.com)
 * @bug No known bugs.
 */

#include "mapElem.h"
#include "../../include/region.h"
#include <stdio.h>
#include <string.h>



void mapKeyPrint(MapKey key) {
	keyStringPrint(key);
}

void mapValuePrint(MapValue value) {
	regionPrint(&value);
}

bool mapKeyEquals(MapKey key1, MapKey key2) {
	if ( strcmp(key1.str, key2.str) == 0)
	{
		return true;
	}
	return false;
}
