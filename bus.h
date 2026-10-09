//Header file for bus
//feature is under development
// Header file for bus

#ifndef BUS_H
#define BUS_H

#define BUS_COUNT 4

extern int busID[BUS_COUNT];
extern char destination[BUS_COUNT][20];
extern char departure[BUS_COUNT][20];
extern float fare[BUS_COUNT];

void viewBuses(void);
void displayBusDetails(int index);
int findBusIndex(int id);

#endif
