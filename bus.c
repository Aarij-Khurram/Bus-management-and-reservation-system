// .c file for bus
// feature is under development

#include <stdio.h>
#include <stddef.h>
#include <ctype.h>
#include "bus.h"
#include "data.h"

Bus buses[BUS_COUNT] = {
    {101, "Karachi", "Lahore", "08:00 AM", 2500},
    {102, "Islamabad", "Multan", "10:00 AM", 3000},
    {103, "Lahore", "Peshawar", "09:00 AM", 2200},
    {104, "Karachi", "Islamabad", "11:00 AM", 3500}
};

void viewBuses(void)
{
    printf("\n========== AVAILABLE BUSES ==========\n");

    for (int i = 0; i < BUS_COUNT; i++)
    {
        printf("\nBus ID: %d\n", buses[i].busID);
        printf("Route: %s -> %s\n", buses[i].source, buses[i].destination);
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
    printf("Route: %s -> %s\n", buses[index].source, buses[index].destination);
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

static int sameText(const char *a, const char *b)
{
    while (*a != '\0' && *b != '\0')
    {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b))
        {
            return 0;
        }
        a++;
        b++;
    }

    return *a == '\0' && *b == '\0';
}

void searchBusesByRoute(void)
{
    char source[20];
    char destination[20];
    int found = 0;

    printf("\n========== SEARCH BUSES BY ROUTE ==========\n");

    printf("Enter source city: ");
    if (scanf("%19s", source) != 1)
    {
        printf("Invalid input!\n");
        return;
    }

    printf("Enter destination city: ");
    if (scanf("%19s", destination) != 1)
    {
        printf("Invalid input!\n");
        return;
    }

    for (int i = 0; i < BUS_COUNT; i++)
    {
        if (sameText(buses[i].source, source) && sameText(buses[i].destination, destination))
        {
            displayBusDetails(i);
            found = 1;
        }
    }

    if (!found)
    {
        printf("\nNo direct bus found from %s to %s.\n", source, destination);
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