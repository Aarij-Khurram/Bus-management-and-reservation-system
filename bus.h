//Header file for bus
//feature is under development
// Header file for bus

#ifndef BUS_H
#define BUS_H

#define BUS_COUNT 4

typedef struct
{
    int busID;
    char destination[20];
    char departure[20];
    float fare;
} Bus;



void viewBuses(void);
void displayBusDetails(int index);
int findBusIndex(int id);
void searchBusByID(void);
int getBusCount(void);
int busExists(int id);
int getBusID(int index);
const char *getBusDestination(int index);

#endif
