//header file
//header file
#ifndef SEAT_H
#define SEAT_H
#include "bus.h"

#define MAX_SEATS 40
extern int seatStatus[BUS_COUNT][MAX_SEATS];
void displaySeats(int busIndex);
int isSeatAvailable(int busIndex,int seatNumber);
int reserveSeat(int busIndex,int seatNumber);
int releaseSeat(int busIndex,int seatNumber);
#endif

