
// .c file for bus
// feature is under development

#include <stdio.h>
#include <stddef.h>
#include "bus.h"
#include "data.h"

Bus buses[BUS_COUNT] = {
    {101, "Lahore", "08:00 AM", 2500},
    {102, "Islamabad", "10:00 AM", 3000},
    {103, "Multan", "09:00 AM", 2200},
    {104, "Peshawar", "11:00 AM", 3500}
};

void viewBuses(void)
{
    printf("\n========== AVAILABLE BUSES ==========\n");

    for (int i = 0; i < BUS_COUNT; i++)
    {
        printf("\nBus ID: %d\n", buses[i].busID);
        printf("Route: Karachi -> %s\n", buses[i].destination);
        printf("Departure: %s\n", buses[i].departure);
        printf("Fare: Rs. %.2f\n", buses[i].fare);
    }
}

void displayBusDetails(int index)
{
    if (index < 0 || index >= BUS_COUNT)
    {
        printf("Invalid bus index!\n");
        return;
    }

    printf("\n========== BUS DETAILS ==========\n");

    printf("Bus ID: %d\n", buses[index].busID);
    printf("Route: Karachi -> %s\n", buses[index].destination);
    printf("Departure: %s\n", buses[index].departure);
    printf("Fare: Rs. %.2f\n", buses[index].fare);
}

int findBusIndex(int id)
{
    for (int i = 0; i < BUS_COUNT; i++)
    {
        if (buses[i].busID == id)
        {
            return i;
        }
    }

    return -1;
}

void searchBusByID(void)
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

int getBusCount(void)
{
    return BUS_COUNT;
}

int busExists(int id)
{
    if (findBusIndex(id) != -1)
    {
        return 1;
    }

    return 0;
}

int getBusID(int index)
{
    if (index < 0 || index >= BUS_COUNT)
    {
        return -1;
    }

    return buses[index].busID;
}

const char *getBusDestination(int index)
{
    if (index < 0 || index >= BUS_COUNT)
    {
        return NULL;
    }

    return buses[index].destination;
}
