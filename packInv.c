/* packInv.c
 *
 * Author: Ben C
 * Lab instructor: Hanan S.
 * Lecture instructor: Hanan S.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#include "sharedInv.h"
#include "packInv.h"

void packInventory(int argc, char *argv[])
{
    //Open File
    FILE *src;
    src = fopen(argv[1], "r");
    if (src == NULL)
    {
        fprintf(stderr,"Unable to open %s.", argv[1]);
        exit(1);
    }

    //read header
    char line[256];
    if(fgets(line, sizeof(line), src) != NULL)
    {   
        int check = (checkHeader(line));

        if (check == 0)
        {
            printf("%s",line);
        }
        else
        {
            printf("Header missing or incorrect format.");
            exit(1);
        }
    }

    //iterate through lines in log
    while(fgets(line, sizeof(line), src) != NULL)
    {
        int check;

        //datetime
        char * token = strtok(line, "|\n");
        check = checkDayTime(token);
        
        if (check == 1)
        {
            continue;
        }

        struct tm dt = {0};
        sscanf(token,"%d/%d/%d %d:%d:%d\n", &dt.tm_mday, &dt.tm_mon, &dt.tm_year, &dt.tm_hour, &dt.tm_min, &dt.tm_sec);

        dt.tm_mon -=1;
        dt.tm_year-=1900;
        dt.tm_isdst = -1;

        //time_t unixTime = mktime(&dt); - test for unixTime

        //event
        token = strtok(NULL, "|\n");
        check = checkEvent(token);

        if (check == 1)
        {
            continue;
        }

        int eLen = strlen(token);
        char event[eLen];
        strcpy(event, token);

        //item
        token = strtok(NULL, "|\n");
        check = checkSKU(token);

        if (check == 1)
        {
            continue;
        }

        int iLen = strlen(token);
        char item[iLen];
        strcpy(item, token);

        //quantity
        token = strtok(NULL, "|\n");
        check = checkQuantity(token);

        if (check == 1)
        {
            continue;
        }

        signed int quantity;
        sscanf(token, "%d", &quantity);

        //note
        token = strtok(NULL, "|\n");
        check = checkNote(token);

        if (check == 1)
        {
            continue;
        }

        int nLen = strlen(token);
        char note[nLen];
        strcpy(note, token);

        //test print
        printf("%d/%d/%d %d:%d:%d|%s|%s|%d|%s\n", 
            dt.tm_mday, dt.tm_mon+1, dt.tm_year+1900, dt.tm_hour, dt.tm_min, dt.tm_sec, 
            event, item, quantity, note);
        //printf("%jd\n", (intmax_t)unixTime); - UNIX TIME PRINT FOR TESTING
    }

    fclose(src);

}

int checkHeader(char * line)
{
    char test[] = "<datetime>|<event>|<item>|<quantity>|<note>\n";
    if (strcmp(line, test) == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int checkDayTime(char * line)
{
    int mday, mon, year, hour, min, sec;
    if(sscanf(line,"%d/%d/%d %d:%d:%d\n", &mday, &mon, &year, &hour, &min, &sec) == 6)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int checkEvent(char * line)
{
    if(strcmp(line,"IN") == 0 || strcmp(line,"OUT") == 0 || strcmp(line,"ADJ") == 0 || strcmp(line,"ALERT") == 0 ||
       strcmp(line,"IN*") == 0 || strcmp(line,"OUT*") == 0 || strcmp(line,"ADJ*") == 0 || strcmp(line,"ALERT*") == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int checkSKU(char * line)
{
    if (strlen(line) <= MAX_SKU_LEN && strstr(line, "SKU") != NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int checkQuantity(char * line)
{
    signed int test;
    sscanf(line, "%d", &test);

    if (test >= MIN_QUANTITY && test <= MAX_QUANTITY)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int checkNote(char * line)
{
    if (strstr(line, "-") != NULL || strlen(line) > 0 )
    {
        if (strlen(line) <= MAX_NOTE_LEN)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 1;
    }
}