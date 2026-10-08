// .c file for bus
//feature is under development
#include <stdio.h>
#include "bus.h"

int busID[] = {101, 102, 103};
char destination[][20] = {"Lahore", "Islamabad", "Multan"};
char departure[][20] = {"08:00 AM", "10:00 AM", "09:00 AM"};
float fare[] = {2500, 3000, 2200};
//Array declaration for three buses for now



void viewBuses()
{
    printf("\n========== AVAILABLE BUSES ==========\n");

    for (int i = 0; i < 3; i++)
    {
        printf("\nBus ID: %d\n", busID[i]);
        printf("Route: Karachi -> %s\n", destination[i]);
        printf("Departure: %s\n", departure[i]);
        printf("Fare: Rs. %.2f\n", fare[i]);
    }
}
