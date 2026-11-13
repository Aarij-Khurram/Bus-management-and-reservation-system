#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "search.h"
#include "bus.h"
#include "data.h"

// Convert a string into lowercase
void toLowerCase(char str[])
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

// Clear any remaining characters from the input line
void clearInputBuffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

// Take and validate a city name
int getCityName(char city[])
{
    printf("Enter city name: ");

    if (fgets(city, 30, stdin) == NULL)
        return 0;

    // Check whether the complete input was read
    if (strchr(city, '\n') == NULL)
    {
        clearInputBuffer();
        printf("City name is too long.\n");
        return 0;
    }

    // Remove newline
    city[strcspn(city, "\n")] = '\0';

    // Remove spaces from the beginning
    int start = 0;

    while (isspace((unsigned char)city[start]))
        start++;

    // Remove spaces from the end
    int end = (int)strlen(city) - 1;

    while (end >= start && isspace((unsigned char)city[end]))
        end--;

    // Reject empty input
    if (start > end)
    {
        printf("City name cannot be empty.\n");
        return 0;
    }

    // Move the cleaned city name to the beginning
    int i = 0;

    while (start <= end)
    {
        city[i++] = city[start++];
    }

    city[i] = '\0';

    // Allow letters, spaces and hyphens only
    for (i = 0; city[i] != '\0'; i++)
    {
        if (!isalpha((unsigned char)city[i]) &&
            city[i] != ' ' && city[i] != '-')
        {
            printf("Invalid city name. Use letters, spaces or hyphens only.\n");
            return 0;
        }
    }

    toLowerCase(city);

    return 1;
}

// Search buses
void searchbus(void)
{
    int choice;
    int found = 0;

    char source[30];
    char destination[30];

    char tempSource[20];
    char tempDestination[20];

    float minFare;
    float maxFare;

    printf("\n========== SEARCH BUSES ==========\n");
    printf("1. Search by source\n");
    printf("2. Search by destination\n");
    printf("3. Search by source and destination\n");
    printf("4. Search by fare range\n");

    printf("\nEnter your choice: ");

    if (scanf("%d", &choice) != 1)
    {
        printf("Invalid input! Please enter a number.\n");
        clearInputBuffer();
        return;
    }

    clearInputBuffer();

    if (choice < 1 || choice > 4)
    {
        printf("Invalid choice! Select an option from 1 to 4.\n");
        return;
    }

    // Search by source
    if (choice == 1 || choice == 3)
    {
        if (!getCityName(source))
            return;
    }

    // Search by destination
    if (choice == 2 || choice == 3)
    {
        if (!getCityName(destination))
            return;
    }

    // Search by fare range
    if (choice == 4)
    {
        printf("Enter minimum fare: ");

        if (scanf("%f", &minFare) != 1)
        {
            printf("Invalid fare! Enter a numeric value.\n");
            clearInputBuffer();
            return;
        }

        if (!isfinite(minFare) || minFare < 0)
        {
            printf("Minimum fare must be a valid non-negative number.\n");
            clearInputBuffer();
            return;
        }

        printf("Enter maximum fare: ");

        if (scanf("%f", &maxFare) != 1)
        {
            printf("Invalid fare! Enter a numeric value.\n");
            clearInputBuffer();
            return;
        }

        clearInputBuffer();

        if (!isfinite(maxFare) || maxFare < 0)
        {
            printf("Maximum fare must be a valid non-negative number.\n");
            return;
        }

        if (minFare > maxFare)
        {
            printf("Minimum fare cannot be greater than maximum fare.\n");
            return;
        }
    }

    // Search through all buses
    printf("\n========== SEARCH RESULTS ==========\n");

    for (int i = 0; i < BUS_COUNT; i++)
    {
        strcpy(tempSource, buses[i].source);
        strcpy(tempDestination, buses[i].destination);

        toLowerCase(tempSource);
        toLowerCase(tempDestination);

        // Option 1: Search by source
        if (choice == 1 &&
            strcmp(tempSource, source) == 0)
        {
            displayBusDetails(i);
            found = 1;
        }

        // Option 2: Search by destination
        else if (choice == 2 &&
                 strcmp(tempDestination, destination) == 0)
        {
            displayBusDetails(i);
            found = 1;
        }

        // Option 3: Search by both cities
        else if (choice == 3 &&
                 strcmp(tempSource, source) == 0 &&
                 strcmp(tempDestination, destination) == 0)
        {
            displayBusDetails(i);
            found = 1;
        }

        // Option 4: Search by fare range
        else if (choice == 4 &&
                 buses[i].fare >= minFare &&
                 buses[i].fare <= maxFare)
        {
            displayBusDetails(i);
            found = 1;
        }
    }

    if (found == 0)
    {
        printf("\nNo buses found for your search.\n");
    }
    else
    {
        printf("\nSearch completed successfully.\n");
    }
}
