// .c file for bus
// feature is under development

#include <stdio.h>
#include <stddef.h>
#include <ctype.h>
#include "bus.h"
#include "data.h"

Bus buses[BUS_COUNT] = {
    {101, "Karachi", "Lahore", "08:00 AM", 2500, {0}},
    {102, "Islamabad", "Multan", "10:00 AM", 3000, {0}},
    {103, "Lahore", "Peshawar", "09:00 AM", 2200, {0}},
    {104, "Karachi", "Islamabad", "11:00 AM", 3500, {0}},
    {105, "Karachi", "Hyderabad", "07:00 AM", 1200, {0}},
    {106, "Lahore", "Islamabad", "08:30 AM", 1800, {0}},
    {107, "Peshawar", "Islamabad", "09:00 AM", 1500, {0}},
    {108, "Multan", "Karachi", "06:00 PM", 3200, {0}},
    {109, "Quetta", "Karachi", "07:30 AM", 4000, {0}},
    {110, "Faisalabad", "Lahore", "10:00 AM", 1000, {0}},
    {111, "Rawalpindi", "Multan", "11:00 AM", 2500, {0}},
    {112, "Hyderabad", "Sukkur", "12:00 PM", 1400, {0}},
    {113, "Sukkur", "Karachi", "02:00 PM", 2200, {0}},
    {114, "Islamabad", "Peshawar", "03:00 PM", 1200, {0}},
    {115, "Lahore", "Faisalabad", "04:00 PM", 1000, {0}},
    {116, "Karachi", "Quetta", "05:00 PM", 4200, {0}},
    {117, "Multan", "Lahore", "06:30 AM", 1600, {0}},
    {118, "Peshawar", "Lahore", "07:00 AM", 2800, {0}},
    {119, "Islamabad", "Karachi", "08:00 PM", 3800, {0}},
    {120, "Hyderabad", "Multan", "09:30 AM", 2600, {0}},
    {121, "Faisalabad", "Islamabad", "10:30 AM", 2000, {0}},
    {122, "Quetta", "Lahore", "11:30 AM", 4500, {0}},
    {123, "Sukkur", "Multan", "01:00 PM", 1800, {0}},
    {124, "Karachi", "Faisalabad", "02:30 PM", 3500, {0}},
    {125, "Lahore", "Quetta", "04:00 PM", 4300, {0}},
    {126, "Multan", "Peshawar", "05:30 PM", 3000, {0}},
    {127, "Rawalpindi", "Karachi", "07:00 PM", 3900, {0}},
    {128, "Islamabad", "Lahore", "09:00 AM", 1700, {0}},
    {129, "Faisalabad", "Multan", "01:30 PM", 1300, {0}},
    {130, "Karachi", "Sukkur", "10:00 PM", 2000, {0}}};

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