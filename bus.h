//Header file for bus
//feature is under development
// Header file for bus

#ifndef BUS_H
#define BUS_H
#include "data.h"

extern Bus buses[BUS_COUNT];

void viewBuses(void);
void displayBusDetails(int index);
int findBusIndex(int id);
void searchBusByID(void);
void searchBusesByRoute(void);
int getBusCount(void);
int busExists(int id);
int getBusID(int index);
const char *getBusDestination(int index);

#endif
