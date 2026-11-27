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
        //datetime
        char * token = strtok(line, "|\n");
        int checkDT = checkDayTime(token);
        
        if (checkDT == 1)
        {
            continue;
        }

        struct tm dt = {0};
        sscanf(token,"%d/%d/%d %d:%d:%d\n", &dt.tm_mday, &dt.tm_mon, &dt.tm_year, &dt.tm_hour, &dt.tm_min, &dt.tm_sec);

        dt.tm_mon -=1;
        dt.tm_year-=1900;
        dt.tm_isdst = -1;

        time_t unixTime = mktime(&dt);

        //event
        token = strtok(NULL, "|\n");
        
        //test print
        printf("%d/%d/%d %d:%d:%d\n", dt.tm_mday, dt.tm_mon+1, dt.tm_year+1900, dt.tm_hour, dt.tm_min, dt.tm_sec);
        printf("%jd\n", (intmax_t)unixTime);
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