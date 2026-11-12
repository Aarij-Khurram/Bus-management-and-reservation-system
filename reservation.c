// src for reservations
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "reservation.h"
#include "bus.h"
#include "seat.h"
#include "data.h"

 #define RES_FILE "reservations.dat"
 #define NameSize 50
 #define  PhoneSize 25
 #define  MaxReservations 100
 #define MaxTries 3

 
static struct Reservation reservations[MaxReservations];
static int resCount = 0;
static int nextID = 1001;
static int generateReservationID(void){
    return nextID++;
}
int findReservation(int id){
    int i;
    for(i = 0; i < resCount; i++){
        if(reservations[i].reservationID == id) return i;
    }
    return -1;
}
void saveReservations(void){
    FILE *fp = fopen(RES_FILE, "wb");

    if(fp == NULL){
        printf("Error: could not save reservations.\n");
        return;
    }

    fwrite(&nextID, sizeof(int), 1, fp);
    fwrite(&resCount, sizeof(int), 1, fp);
    if(fwrite(reservations, sizeof(struct Reservation), resCount, fp) != (size_t)resCount){
        printf("Error: reservations may not have been saved completely.\n");
    }

    fclose(fp);
}
static void loadFromFile(void){
    FILE *fp = fopen(RES_FILE, "rb");
    int savedNextID, savedCount;

    if(fp == NULL) return;                      

    if(fread(&savedNextID, sizeof(int), 1, fp) != 1 ||
       fread(&savedCount, sizeof(int), 1, fp) != 1){
        printf("Warning: reservations file is damaged. Starting empty.\n");
        fclose(fp);
        return;
    }

    if(savedCount < 0 || savedCount > MaxReservations){
        printf("Warning: reservations file is damaged. Starting empty.\n");
        fclose(fp);
        return;
    }

    if(fread(reservations, sizeof(struct Reservation), savedCount, fp) != (size_t)savedCount){
        printf("Warning: reservations file is damaged. Starting empty.\n");
        fclose(fp);
        return;
    }

    resCount = savedCount;
    nextID = savedNextID;
    fclose(fp);
}
static void syncSeatsWithReservations(void){
    int i, busIndex;

    for(i= 0; i < resCount; i++){
        busIndex = findBusIndex(reservations[i].busID);
        if(busIndex == -1 || !reserveSeat(busIndex, reservations[i].seatNumber)){
            printf("Warning: could not mark seat %d on bus %d as booked. \n", reservations[i].seatNumber, reservations[i].busID);
        }
    }
}
void loadReservations(void){
    resCount = 0;
    nextID = 1001;
    loadFromFile();
    syncSeatsWithReservations();
}
static int addReservation(char name[], char phone[], int busID, int seat){
    int id;

    if(resCount >= MaxReservations) return -1;

    id = generateReservationID();
    reservations[resCount].reservationID = id;
    strcpy(reservations[resCount].passengerName, name);
    strcpy(reservations[resCount].phone, phone);
    reservations[resCount].busID = busID;
    reservations[resCount].seatNumber = seat;
    resCount++;
    return id;
}
 static int readLine(char text[], int size)
 {
    int c;

    if(fgets(text, size, stdin) == NULL)
    {
        text[0] = '\0';
        return 1;
    }

    if(strchr(text, '\n') == NULL){
        while((c = getchar()) != '\n' && c !=EOF){

        }
        return 0;
    } 
    text[strcspn(text, "\n")] = '\0';
    return 1;
}
static void trimSpaces(char text[]){
    int start = 0, end, i;

    while(text[start] == ' ') start++;

    end = strlen(text) - 1;
    while(end >= start && text[end] == ' ') end--;

    for(i = 0; i <= end - start; i++){
        text[i] = text[start + i];
    }
    text[end - start + 1] = '\0';
}
static int readInt(void){
    char line[20];
    int i, len;

    if(!readLine(line, 20)) return -1;

    trimSpaces(line);
    len = strlen(line);
    if(len == 0 || len > 9) return -1;

    for(i = 0; i < len; i++){
        if(!isdigit(line[i])) return -1;
    }
    return atoi(line);
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
        if(!readLine(name, NameSize)){
            printf("Name too long (max %d characters).\n", NameSize - 1);
            continue;
        }
        trimSpaces(name);
        if(isValidName(name)) break;
        printf("Invalid name. Use letters and spaces only.\n");
    }
}

static void getPhone(char phone[]){
    while(1){
        printf("Enter phone number (11 digits): ");
        if(!readLine(phone, PhoneSize)){
            printf("Phone number too long.\n");
            continue;
        }
        trimSpaces(phone);
        if(isValidPhone(phone)) break;
        printf("Invalid phone number. Enter exactly 11 digits.\n");
    }
}

static int chooseBus(void){
    int tries, busID;

    for(tries = 1; tries <= MaxTries; tries++){
        printf("Enter bus ID: ");
        busID = readInt();
        if(busExists(busID)) return busID;
        printf("Invalid bus ID. (attempt %d of %d)\n", tries, MaxTries);
    }
    printf("Too many invalid attempts. Reservation cancelled.\n");
    return -1;
}

static int chooseSeat(int busID){
    int busIndex = findBusIndex(busID);
    int tries, seat;

    displaySeats(busIndex);

    for(tries = 1; tries <= MaxTries; tries++){
        printf("Enter seat number (1-%d): ", MAX_SEATS);
        seat = readInt();

        if(seat < 1 || seat > MAX_SEATS){
            printf("Invalid seat number.\n");
        }
        else if(!isSeatAvailable(busIndex, seat)){
            printf("Seat %d is already taken.\n", seat);
        }
        else{
            return seat;
        }
    }
    printf("Too many invalid attempts. Reservation cancelled.\n");
    return -1;
}
static void printReservation(int index){
    struct Reservation r = reservations[index];

    printf("\nReservation ID: R%d\n", r.reservationID);
    printf("Passenger: %s\n", r.passengerName);
    printf("Phone: %s\n", r.phone);
    printf("Seat: %d\n", r.seatNumber);
    displayBusDetails(findBusIndex(r.busID));
}
static int readReservationID(void){
    char line[20];
    int i, start = 0, len;

    printf("Enter reservation ID (e.g. R1001): ");
    if(!readLine(line, 20)) return -1;
    trimSpaces(line);

    if(line[0] == 'R' || line[0] == 'r') start = 1;

    len = strlen(line);
    if(len == start || len - start > 9) return -1;

    for(i = start; i < len; i++){
        if(!isdigit(line[i])) return -1;
    }
    return atoi(&line[start]);
}
static void removeReservation(int index){
    int i;
    for(i = index; i < resCount - 1; i++){
        reservations[i] = reservations[i + 1];
    }
    resCount--;
}

static int askYesNo(void){
    char answer[10];
    int i;

    readLine(answer, 10);
    trimSpaces(answer);

    for(i = 0; answer[i] != '\0'; i++){
        answer[i] = tolower(answer[i]);
    }
    return strcmp(answer, "y") == 0 || strcmp(answer, "yes") == 0;
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
    getPhone(phone);

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
    saveReservations();
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

        printf("\nCancel this reservation? (y/n): ");
    if(!askYesNo()){
        printf("Cancellation aborted.\n");
        return;
    }

    busIndex = findBusIndex(reservations[index].busID);
    seat = reservations[index].seatNumber;

    if(!releaseSeat(busIndex, seat)){
        printf("Could not release the seat. Reservation not cancelled.\n");
        return;
    }

    removeReservation(index);
    saveReservations();
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


