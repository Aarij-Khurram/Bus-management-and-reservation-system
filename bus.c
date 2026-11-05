// .c file for bus
//feature is under development
#include <stdio.h>
#include <stddef.h>
#include "bus.h"

Bus buses[BUS_COUNT] = {
    {101, "Lahore", "08:00 AM", 2500},
    {102, "Islamabad", "10:00 AM", 3000},
    {103, "Multan", "09:00 AM", 2200},
    {104, "Peshawar", "11:00 AM", 3500}
};


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

    if (scanf("%d", &id) != 1)
{
    printf("Invalid input! Please enter a numeric bus ID.\n");

    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        /* Clear invalid input */
    }

    return;
}

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




int getBusID(int index)                   //function 7
{
    if (index < 0 || index >= BUS_COUNT)
    {
        return -1;
    }

    return busID[index];
}




const char *getBusDestination(int index)       //function 8
{
    if (index < 0 || index >= BUS_COUNT)
    {
        return NULL;
    }

    return destination[index];
}