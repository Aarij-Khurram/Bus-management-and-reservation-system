// initilization of data.h
#ifndef DATA_H
#define DATA_H

#define NAME_SIZE   50
#define PHONE_SIZE  25

struct Reservation
{
    int  reservationID;
    char passengerName[NAME_SIZE];
    char phone[PHONE_SIZE];
    int  busID;
    int  seatNumber;
}; 

#endif