#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "search.h"
#include "bus.h"
#include "data.h"

//tolower
void toLowerCase(char str[]){
    for (int i = 0; str[i] != '\0'; i++){
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}
void clearInputBuffer(void){
    int ch;
    while ((ch = getchar())!= '\n' && ch != EOF){}
}





int getCityName(char city[]){
    printf("Enter city name: ");


    if (fgets(city,30, stdin) == NULL)
        return 0;

    //check
    if (strchr(city,'\n') == NULL){
        clearInputBuffer();
        printf("City name is too long.\n");
        return 0;
    }
    
    city[strcspn(city, "\n")] = '\0'; //remove new line
    int start = 0; //remove spaces from the beginning



    while (isspace((unsigned char)city[start]))
        start++;

    
    int end = (int)strlen(city) - 1; //remove spaces from the end
    while (end>= start && isspace((unsigned char)city[end]))
        end--;

    //empty input
    if (start > end){
        printf("City name cannot be empty.\n");
        return 0;
    }

    // Move the cleaned city name to the beginning
    int i = 0;
    while (start<= end){
        city[i++] = city[start++];
    }
    city[i] = '\0';
    for (i = 0;city[i] != '\0'; i++){
        if (!isalpha((unsigned char)city[i]) && city[i] != ' ' && city[i] != '-'){
            printf("Invalid city name. Use letters, spaces or hyphens only.\n");
            return 0;
        }
    }
    toLowerCase(city);



    return 1;
}

//search buses func
void searchbus(void){
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
    if (scanf("%d", &choice) != 1){
        printf("Invalid input! Please enter a number.\n");
        clearInputBuffer();
        return;
    }

    clearInputBuffer();
    if (choice <1 || choice> 4){
        printf("Invalid choice! Select an option from 1 to 4.\n");
        return;
    }

    //by src
    if (choice == 1 || choice == 3){
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
    if (choice== 4){
        printf("Enter minimum fare: ");

        if (scanf("%f",&minFare) != 1){
            printf("Invalid fare! Enter a numeric value.\n");
            clearInputBuffer();
            return;
        }
        if (!isfinite(minFare) || minFare <0){
            printf("Minimum fare must be a valid non-negative number.\n");
            clearInputBuffer();
            return;
        }
        
        printf("Enter maximum fare: ");
        if (scanf("%f",&maxFare) != 1){
            printf("Invalid fare! Enter a numeric value.\n");
            clearInputBuffer();
            return;
        }



        clearInputBuffer();

        if(!isfinite(maxFare) || maxFare < 0){
            printf("Maximum fare must be a valid non-negative number.\n");
            return;
        }

        if(minFare> maxFare){
            printf("Minimum fare cannot be greater than maximum fare.\n");
            return;
        }
    }

    //all buses
    printf("\n========== SEARCH RESULTS ==========\n");

    for (int i = 0; i < BUS_COUNT; i++){
        strcpy(tempSource, buses[i].source);
        strcpy(tempDestination, buses[i].destination);
        
        
        toLowerCase(tempSource);
        toLowerCase(tempDestination);

    
        if(choice ==1 && strcmp(tempSource, source) == 0){
            displayBusDetails(i);
            found = 1;
        }else if (choice == 2 &&strcmp(tempDestination, destination) == 0){
            displayBusDetails(i);
            found = 1;
        } else if (choice == 3 &&strcmp(tempSource, source) == 0 && strcmp(tempDestination, destination) == 0){
            displayBusDetails(i);
            found = 1;
        } else if (choice == 4 && buses[i].fare >= minFare && buses[i].fare <= maxFare){
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
