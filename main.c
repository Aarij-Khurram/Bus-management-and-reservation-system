
//main file for whole bus reservation system
//feature is under development
#include <stdio.h>
#include "bus.h"
#include "reservation.h"
#include "seat.h"

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
        if (scanf("%d", &choice) != 1)
{
    printf("Invalid input! Please enter a number from 1 to 7.\n");

    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        /* Clear invalid input */
    }

    choice = 0;
    continue;
}
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }

        switch (choice)
        {
            case 1:
                printf("\nTotal buses listed: %d\n", getBusCount());
                viewBuses();
                break;

            case 2:
                searchBusByID();
                break;

            case 3:
                 displayseats();
                break;

            case 4:
                reserveTicket();
                break;

            case 5:
                 cancelReservation();
                 break;


            case 6:
                  viewReservation();
                break;

            case 7:
                printf("\nThank you for using the Bus Ticket Reservation System!\n");
                break;

            default:
                // "Invalid choice"
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 7);

    return 0;
}

