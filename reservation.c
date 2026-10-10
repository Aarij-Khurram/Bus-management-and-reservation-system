// src for reservations
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "reservation.h"

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
        printf("Enter phone number: ");
        readLine(phone, PhoneSize);
        if(isValidPhone(phone)) break;
        printf("Invalid phone number. Digits only.\n");
    }
}
void reserveTicket()
{
    char passengerName[NameSize];
    char phone[PhoneSize];

    printf("\n========== RESERVE TICKET ==========\n");
    getPassengerName(passengerName);
    getphone(phone);

    printf("\nPassenger: %s\n", passengerName);
    printf("Phone: %s\n", phone);
   
}

void cancelReservation()
{
    printf("Cancel reservation\n");
}

void viewReservation()
{
    printf("View reservation\n");
}


