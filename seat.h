//header file
//header file
#ifndef SEAT_H
#define SEAT_H
#include "bus.h"


void displaySeats(int busIndex);
void displaySeatSummary(int busIndex);
int isSeatAvailable(int busIndex,int seatNumber);
int reserveSeat(int busIndex,int seatNumber);
int releaseSeat(int busIndex,int seatNumber);
#endif

