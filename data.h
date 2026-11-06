// initilization of data.h
#ifndef DATA_H
#define DATA_H

#define NAME_SIZE   50
#define PHONE_SIZE  25

struct Reservation // Okasha reservation
{
    int  reservationID;
    char passengerName[NAME_SIZE];
    char phone[PHONE_SIZE];
    int  busID;
    int  seatNumber;
}; 



#define BUS_COUNT 4 // Aarij bus information

typedef struct
{
    int busID;
    char destination[20];
    char departure[20];
    float fare;
} Bus;



#endif