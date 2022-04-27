#pragma once

typedef struct keyString{
	char str[40];
}KeyString;

/**
 * @brief Creates an instance of KeyString
 * 
 * @param string
 * @return KeyString 
 */
KeyString keyStringCreate(char *str);

/**
 * @brief Prints the KeyString
 * 
 * @param KeyString
 */
void keyStringPrint(KeyString ks);
