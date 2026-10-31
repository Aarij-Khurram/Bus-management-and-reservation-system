// src for reservations
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "reservation.h"
#include "bus.h"
#include "seat.h"

 #define NameSize 50
 #define  PhoneSize 25
 #define  MaxReservations 100

 static int resID[MaxReservations];
 static char resName[MaxReservations][NameSize];
 static char resPhone[MaxReservations][PhoneSize];
 static int resBus[MaxReservations];
static int resSeat[MaxReservations];
static int resCount = 0;
static int nextID = 1001;

static int generateReservationID(void){
    return nextID++;
}
int findReservation(int id){
    int i;
    for(i=0;i<resCount;i++){
        if (resID[i] == id){
            return i;
        }
    }
    return -1;
}

static int addReservation(char name[], char phone[], int busID, int seat){
    int id;

    if(resCount >= MaxReservations){
        return -1;
    }

    id = generateReservationID();
    resID[resCount] = id;
    strcpy(resName[resCount], name);
    strcpy(resPhone[resCount], phone);
    resBus[resCount] = busID;
    resSeat[resCount] = seat;
    resCount++;
    return id;

}

 static void readLine(char text[], int size)
 {
     fgets(text, size, stdin);
     text[strcspn(text, "\n")] = '\0'; 
 }

static int readInt(void){
    char line[20];
    int n;

    readLine(line, 20);
    if(sscanf(line, "%d", &n) == 1) return n;
    return -1;
}

 static int isValidName(char name[])
{
    int i, letters = 0;
    int len = strlen(name);

    if (len == 0)
    {
        return 0; 
    }
    for (i = 0; i < len; i++){
        if(isalpha(name[i])) letters++;
        else if(name[i] != ' ') return 0;
    }
    return letters >0;
}

static int isValidPhone(char phone[]){
    int i;
    int len = strlen(phone);

    if (len != 11) return 0;

    for (i=0; i<len; i++){
        if(!isdigit(phone[i])) return 0;
    }
    return 1;
}

static void getPassengerName(char name[]){
    while(1){
        printf("Enter passenger name: ");
        readLine(name, NameSize);
        if(isValidName(name)) break;
        printf("Invalid name. Use letters and spaces only.\n");
    }
}

static void getphone(char phone[]){
    while(1){
        printf("Enter phone number(11-digits): ");
        readLine(phone, PhoneSize);
        if(isValidPhone(phone)) break;
        printf("Invalid phone number. Digits only.\n");
    }
}

static int chooseBus(void){
    int busID;
    
    printf("Enter bus ID: ");
    busID = readInt();

    if(!busExists(busID)){
        printf("Invalid bus ID.\n");
        return -1;
    }
    return busID;
}

static int chooseSeat(int busID){
    int seat;
    int busIndex = findBusIndex(busID);

    displaySeats(busIndex);
    printf("Enter seat number (1-%d): ", MAX_SEATS);
    seat = readInt();

    if(seat < 1 || seat > MAX_SEATS){
        printf("Invalid seat number.\n");
        return -1;
    }
    if(!isSeatAvailable(busIndex, seat)){
        printf("Seat %d is already taken.\n", seat);
        return -1;
    }
    return seat;
}
static void printReservation(int index){
    printf("\nReservation ID: R%d\n", resID[index]);
    printf("Passenger: %s\n", resName[index]);
    printf("Phone: %s\n", resPhone[index]);
    printf("Seat: %d\n", resSeat[index]);
    displayBusDetails(findBusIndex(resBus[index]));
}
static int readReservationID(void){
    char line[20];
    int i, start =0, len;

    printf("Enter reservation ID (e.g. R1001): ");
    readLine(line, 20);

    if(line[0] == 'R' || line[0] == 'r') start =1;

    len=strlen(line);
    if(len == start) return -1;
    if(len - start >9) return -1;
    for(i =start; i< len; i++){
        if(!isdigit(line[i])) return -1;
    }
    return atoi(&line[start]);
}
static void removeReservation(int index){
    int i;
    for(i =index; i < resCount -1; i++){
        resID[i] = resID[i+1];
        strcpy(resName[i],resName[i+1]);
        strcpy(resPhone[i],resPhone[i+1]);
        resBus[i] = resBus[i+1];
        resSeat[i] = resSeat[i+1];
    }
    resCount--;
}

void reserveTicket()
{
    char passengerName[NameSize];
    char phone[PhoneSize];
    int busID, seat;
    int busIndex, id;

    printf("\n========== RESERVE TICKET ==========\n");

    busID = chooseBus();
    if (busID == -1) return;

    getPassengerName(passengerName);
    getphone(phone);

    seat = chooseSeat(busID);
    if (seat == -1) return;

    busIndex =findBusIndex(busID);

    if(!reserveSeat(busIndex, seat)){
        printf("Could not reserve the seat. NO reservation was made.\n");
        return ;
    }

    id = addReservation(passengerName, phone, busID, seat);
    if(id == -1){
        releaseSeat(busIndex, seat);
        printf("Reservation list is full. The seat was released.\n");
        return;
    }
    printf("\nReservation successful!");
    printReservation(findReservation(id));
}

void cancelReservation(void){
    int id, index, busIndex, seat;
    char answer[10];

    printf("\n========== CANCEL RESERVATION ==========\n");
    id = readReservationID();
    if(id == -1){
        printf("Invalid reservation ID.\n");
        return;
    }

    index = findReservation(id);
    if(index == -1){
        printf("Reservation not found.\n");
        return;
    }

    printReservation(index);
    printf("\nCancel this reservation? (y/n): ");
    readLine(answer, 10);

    if(answer[0] != 'y' && answer[0] != 'Y'){
        printf("Cancellation aborted.\n");
        return;
    }

    busIndex = findBusIndex(resBus[index]);
    seat = resSeat[index];

    if(!releaseSeat(busIndex, seat)){
        printf("Could not release the seat. Reservation not cancelled.\n");
        return;
    }

    removeReservation(index);
    printf("Reservation cancelled.\n");
}

void viewReservation()
{
    int id, index;

    printf("\n=========== VIEW RESERVATION ===========\n");
    id =readReservationID();
    if(id == -1){
        printf("Invalid reservation ID.\n");
        return;
    }

    index = findReservation(id);
    if(index == -1){
        printf("Reservation not found.\n");
        return;
    }
    printReservation(index);
}


