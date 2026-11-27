/* packInv.h
 *
 * Author: <TODO: your name here>
 * Lab instructor: <TODO: Your lab instructor's name here>
 * Lecture instructor: <TODO: Your lecture instructor's name here>
 */
#ifndef packInv_h
#define packInv_h

#include "sharedInv.h"

int checkHeader(char * line);

int checkDayTime(char * line);

int checkEvent(char * line);

int checkSKU(char * line);

int checkQuantity(char * line);

int checkNote(char * line);

#endif 
