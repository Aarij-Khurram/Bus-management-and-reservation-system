
//main file for whole bus reservation system
//feature is under development
#include <stdio.h>
#include "bus.h"
#include "reservation.h"

int main()
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("      BUS TICKET RESERVATION SYSTEM\n");
        printf("========================================\n");

        printf("1. View All Buses\n");
        printf("2. Search Bus\n");
        printf("3. View Seat Availability\n");
        printf("4. Reserve Ticket\n");
        printf("5. Cancel Reservation\n");
        printf("6. View Reservation Details\n");
        printf("7. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }

        switch (choice)
        {
            case 1:
                viewBuses();
                break;

            case 2:
                // "Search for a bus" function will be added here later on.
                break;

            case 3:
                // "View seat availability" function will be added here later on.
                break;

            case 4:
                reserveTicket();
                break;

            case 5:
                // "Cancel a reservation" function will be added here later on.
                break;

            case 6:
                // "View reservation details" function will be added here later on.
                break;

            case 7:
                // "Exit the program" function will be added here later on.
                printf("\nThank you for using the Bus Ticket Reservation System!\n");
                break;

            default:
                // "Invalid choice"
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 7);

    return 0;
}

