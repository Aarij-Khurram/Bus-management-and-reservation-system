//search.c is underdevelopment
//search source code

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "search.h"
#include "bus.h"
#include "data.h"

//str to lower case
void toLowerCase(char text[])
{
    int i;

    for (i = 0; text[i] != '\0'; i++)
    {
        text[i] = tolower((unsigned char)text[i]);
    }
}

void searchbus(void){
    char sourceInput[30];
    char destinationInput[30];
    char tempSource[20];
    char tempDestination[20];
    int found = 0;
    
    printf("\n========== SEARCH BUSES ==========\n");
    
    printf("Enter source city: "); //input
    scanf(" %29s", sourceInput);
    printf("Enter destination city: ");
    scanf(" %29s", destinationInput);

    //input to lowercase
    toLowerCase(sourceInput);
    toLowerCase(destinationInput);
    

    // Searching
    for (int i = 0; i < BUS_COUNT; i++)
    {
        // stored source and destination in temp
        strcpy(tempSource, buses[i].source);
        strcpy(tempDestination, buses[i].destination);

        //stored values to lowercase
        toLowerCase(tempSource);
        toLowerCase(tempDestination);

        // compare both source and destination
        if (strcmp(tempSource, sourceInput) == 0 &&
            strcmp(tempDestination, destinationInput) == 0)
        {
            printf("\n========== BUS FOUND ==========\n");
            displayBusDetails(i);
            found = 1;
        }
    }
    if (found == 0) //no bus matched input
    {
        printf("\nNo buses found for this route.\n");
    }


}
