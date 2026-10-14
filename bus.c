// .c file for bus
//feature is under development
#include <stdio.h>
#include "bus.h"

int busID[BUS_COUNT] = {101, 102, 103, 104};

char destination[BUS_COUNT][20] = {
    "Lahore", "Islamabad", "Multan", "Peshawar"
};

char departure[BUS_COUNT][20] = {
    "08:00 AM", "10:00 AM", "09:00 AM", "11:00 AM"
};

float fare[BUS_COUNT] = {2500, 3000, 2200, 3500};
//Array declaration for four buses



void viewBuses()             // function 1 
{
    printf("\n========== AVAILABLE BUSES ==========\n");

    for (int i = 0; i < BUS_COUNT; i++)
    {
        printf("\nBus ID: %d\n", busID[i]);
        printf("Route: Karachi -> %s\n", destination[i]);
        printf("Departure: %s\n", departure[i]);
        printf("Fare: Rs. %.2f\n", fare[i]);
    }
}






void displayBusDetails(int index)           //function 2
{
    if (index < 0 || index >= BUS_COUNT)
    {
        printf("Invalid bus index!\n");
        return;
    }

    printf("\n========== BUS DETAILS ==========\n");

    printf("Bus ID: %d\n", busID[index]);
    printf("Route: Karachi -> %s\n", destination[index]);
    printf("Departure: %s\n", departure[index]);
    printf("Fare: Rs. %.2f\n", fare[index]);
}






int findBusIndex(int id)                   //function 3
{
    for (int i = 0; i < BUS_COUNT; i++)
    {
        if (busID[i] == id)
        {
            return i;
        }
    }

    return -1;
}






void searchBusByID(void)                          //function 4
{
    int id;
    int index;

    printf("\n========== SEARCH BUS BY ID ==========\n");
    printf("Enter Bus ID: ");

    scanf("%d", &id);

    index = findBusIndex(id);

    if (index == -1)
    {
        printf("Bus not found!\n");
    }
    else
    {
        displayBusDetails(index);
    }
}




int getBusCount(void)                       //function 5
{
    return BUS_COUNT;
}



int busExists(int id)                      //function 6
{
    if (findBusIndex(id) != -1)
    {
        return 1;
    }

    return 0;
}