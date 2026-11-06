//sourcecode seat underdevelopment
//sourcecode seat

#include <stdio.h>
#include "seat.h"
#include "data.h"


void displaySeats(int busIndex){
    if(busIndex<0 || busIndex>=BUS_COUNT){
        printf("Invalid bus selection.\n");
        return;
    }
    printf("\n============ SEAT AVAILABILITY ==========\n");
    printf("Key:  _ = Available    X = Booked\n\n");
    printf("          [ FRONT OF BUS ]\n\n");

    for (int i = 0; i < MAX_SEATS; i++)
    {
    char mark = (buses[busIndex].seats[i] == 0) ? '_' : 'X';

    printf("%2d[%c] ", i + 1, mark);

    if ((i + 1) % 4 == 2)          
        printf("         ");

    if ((i + 1) % 4 == 0 || i == MAX_SEATS - 1)   
        printf("\n");
    }
    printf("\n=========================================\n");    
}

int isSeatAvailable(int busIndex,int seatNumber){
    if(busIndex<0 || busIndex >= BUS_COUNT)
        return 0;
    
    if(seatNumber<1 || seatNumber>MAX_SEATS)
        return 0;

    if (buses[busIndex].seats[seatNumber-1] == 0){
        return 1;
    } else{
        return 0;
    }
}

int reserveSeat(int busIndex,int seatNumber){

    if(busIndex<0 || busIndex >= BUS_COUNT){
        printf("Invalid bus selection.\n");
        return 0;
    }
    if(seatNumber<1 || seatNumber > MAX_SEATS){
        printf("Invalid seat number. Choose 1 to %d.\n",MAX_SEATS);
        return 0;
    }
    if (buses[busIndex].seats[seatNumber-1] != 0){
        printf("This seat is already booked. \n");
        return 0;
    }

    buses[busIndex].seats[seatNumber-1] = 1;
    printf("Seat %d reserved successfully. \n",seatNumber);
    return 1;
}

int releaseSeat(int busIndex,int seatNumber){
    if(busIndex<0 || busIndex >= BUS_COUNT){
        printf("Invalid bus selection.\n");
        return 0;
    }
    if(seatNumber<1 || seatNumber > MAX_SEATS){
        printf("Invalid seat number. Choose 1 to %d.\n",MAX_SEATS);
        return 0;
    }
    if (buses[busIndex].seats[seatNumber-1] == 0){
        printf("This seat is already available. \n");
        return 0;
    }
    buses[busIndex].seats[seatNumber-1] = 0;
    printf("Seat %d released successfully. \n",seatNumber);
    return 1;
}


