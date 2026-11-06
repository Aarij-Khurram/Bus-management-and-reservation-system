// initilization of data.h
#ifndef DATA_H
#define DATA_H

#define NAME_SIZE   50
#define PHONE_SIZE  25

typedef struct // Okasha reservation
{
    int  reservationID;
    char passengerName[NAME_SIZE];
    char phone[PHONE_SIZE];
    int  busID;
    int  seatNumber;
} Reservation;



#define BUS_COUNT 4 // Aarij bus information
#define MAX_SEATS 40

typedef struct
{
    int busID;
    char source[20];
    char destination[20];
    char departure[20];
    float fare;
    int seats[MAX_SEATS];
} Bus;



#endif