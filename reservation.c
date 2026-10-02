// src for reservations
#include <stdio.h>
#include "reservation.h"

void reserveTicket()
{
    char passengerName[50];
    char phone[25];

    printf("\n========== RESERVE TICKET ==========\n");

    printf("Enter passenger name: ");
    fgets(passengerName, sizeof(passengerName), stdin);
    printf("Enter phone number: ");
    fgets(phone, sizeof(phone), stdin);

    printf("\nPassenger: %s", passengerName);
    printf("Phone: %s", phone);
}

void cancelReservation()
{
    printf("Cancel reservation\n");
}

void viewReservation()
{
    printf("View reservation\n");
}

