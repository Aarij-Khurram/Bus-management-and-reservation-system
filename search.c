//search.c is underdevelopment
//search source code

#include <stdio.h>
#include <string.h>

#include "search.h"
#include "bus.h"

void searchbus(void){
    char source[30];
    char destinationInput[30];
    int found = 0;
    
    printf("\n========== SEARCH BUSES ==========\n");
    
    printf("Enter source city: "); //input
    scanf(" %s", source);
    printf("Enter destination city: ");
    scanf(" %s", destinationInput);

    //departure city is only karachi rn
    if (strcmp(source, "karachi") != 0)
    {
        printf("\nNo buses found from this source.\n");
        return;
    }

    //searching for bus
    for (int i = 0; i < BUS_COUNT; i++)
    {
        if (strcmp(destination[i], destinationInput) == 0)
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
