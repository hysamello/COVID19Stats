#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "keyString.h"

KeyString keyStringCreate(char *str){
	KeyString ks;
	strcpy(ks.str,str);
	return ks;
}

void keyStringPrint(KeyString ks){
	printf("%-20s",ks.str);
}
