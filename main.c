//main file for whole bus reservation system
//feature is under development
#include <stdio.h>
#include "bus.h"
#include "reservation.h"
#include "seat.h"
#include "data.h"

int main()
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("      BUS TICKET RESERVATION SYSTEM\n");
        printf("========================================\n");
        printf("1. View All Buses\n");
        printf("2. Search Bus by ID\n");
        printf("3. Search Buses by Route\n");
        printf("4. View Seat Availability\n");
        printf("5. Reserve Ticket\n");
        printf("6. Cancel Reservation\n");
        printf("7. View Reservation Details\n");
        printf("8. Exit\n");

        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input! Please enter a number from 1 to 8.\n");

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
                searchBusesByRoute();
                break;

            case 4:
            {
                int busID;
                int index;

                printf("\nEnter Bus ID to view seats: ");

                if (scanf("%d", &busID) != 1)
                {
                    printf("Invalid input! Please enter a numeric bus ID.\n");

                    while ((c = getchar()) != '\n' && c != EOF)
                    {
                    }

                    break;
                }

                index = findBusIndex(busID);

                if (index == -1)
                {
                    printf("Bus not found!\n");
                }
                else
                {
                    displaySeats(index);
                }

                break;
            }

            case 5:
                reserveTicket();
                break;

            case 6:
                cancelReservation();
                break;

            case 7:
                viewReservation();
                break;

            case 8:
                printf("\nThank you for using the Bus Ticket Reservation System!\n");
                break;

            default:
                // "Invalid choice"
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 8);

    return 0;
}