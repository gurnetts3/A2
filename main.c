/* main.c
 * 
 * Author: <TODO: your name here>
 * Lab instructor: <TODO: Your lab instructor's name here>
 * Lecture instructor: <TODO: Your lecture instructor's name here>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sharedInv.h"


int main(int argc, char *argv[]){
	char * extension = strchr(argv[1], '.');
	if(strcmp(extension, ".log") == 0)
	{
		printf("PACK INVENTORY:\n");
		packInventory(argc, argv);
	}
	else
	{
		printf("program only supports log files at this time\n.");
		exit(1);
	}
	return 0;
}
