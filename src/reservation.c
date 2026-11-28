
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#include "reservation.h"
#include "bus.h"
#include "seat.h"
#include "data.h"

#define RES_FILE "reservations.dat"
#define TEMP_RES_FILE "reservations.tmp"


#define MAX_RESERVATIONS 1200
#define MAX_TRIES 3
#define FIRST_RESERVATION_ID 1001

static struct Reservation reservations[MAX_RESERVATIONS];
static int resCount = 0;
static int nextID = FIRST_RESERVATION_ID;
static int seatsSynced = 0;

int findReservation(int id)
{
    int i;

    for (i = 0; i < resCount; i++)
    {
        if (reservations[i].reservationID == id)
        {
            return i;
        }
    }

    return -1;
}

static int generateReservationID(void)
{
    if (nextID < FIRST_RESERVATION_ID || nextID >= INT_MAX)
    {
        return -1;
    }

    return nextID++;
}

static int readLine(char text[], int size)
{
    int c;
    size_t length;

    if (text == NULL || size < 2)
    {
        return -1;
    }

    if (fgets(text, size, stdin) == NULL)
    {
        text[0] = '\0';
        return -1;
    }

    length = strlen(text);

    if (length > 0 && text[length - 1] == '\n')
    {
        text[length - 1] = '\0';
        return 1;
    }

    c = getchar();

    if (c == '\n' || c == EOF)
    {
        if (c == EOF && ferror(stdin))
        {
            text[0] = '\0';
            return -1;
        }

        return 1;
    }

    while ((c = getchar()) != '\n' && c != EOF)
    {
    }

    return 0;
}

static void trimSpaces(char text[])
{
    size_t start = 0;
    size_t end;
    size_t length;

    length = strlen(text);

    while (start < length && text[start] == ' ')
    {
        start++;
    }

    end = length;

    while (end > start && text[end - 1] == ' ')
    {
        end--;
    }

    if (start > 0)
    {
        memmove(text, text + start, end - start);
    }

    text[end - start] = '\0';
}

static int readPositiveInteger(void)
{
    char line[20];
    int status;
    int i;
    int value = 0;
    size_t length;

    status = readLine(line, sizeof(line));

    if (status == -1)
    {
        return -2;
    }

    if (status == 0)
    {
        return -1;
    }

    trimSpaces(line);

    length = strlen(line);

    if (length == 0 || length > 9)
    {
        return -1;
    }

    for (i = 0; i < (int)length; i++)
    {
        unsigned char ch = (unsigned char)line[i];

        if (!isdigit(ch))
        {
            return -1;
        }

        value = value * 10 + (ch - '0');
    }

    return value;
}

static int isValidName(const char name[])
{
    int i;
    int letters = 0;

    if (name == NULL || name[0] == '\0')
    {
        return 0;
    }

    for (i = 0; name[i] != '\0'; i++)
    {
        unsigned char ch = (unsigned char)name[i];

        if (isalpha(ch))
        {
            letters++;
        }
        else if (name[i] != ' ')
        {
            return 0;
        }
    }

    return letters > 0;
}

static int isValidPhone(const char phone[])
{
    int i;

    if (phone == NULL || strlen(phone) != 11)
    {
        return 0;
    }

    for (i = 0; phone[i] != '\0'; i++)
    {
        unsigned char ch = (unsigned char)phone[i];

        if (!isdigit(ch))
        {
            return 0;
        }
    }

    return 1;
}

static int getPassengerName(char name[])
{
    int status;

    while (1)
    {
        printf("Enter passenger name: ");

        status = readLine(name, NAME_SIZE);

        if (status == -1)
        {
            return 0;
        }

        if (status == 0)
        {
            printf("Name too long. Maximum %d characters.\n",
                   NAME_SIZE - 1);
            continue;
        }

        trimSpaces(name);

        if (isValidName(name))
        {
            return 1;
        }

        printf("Invalid name. Use letters and spaces only.\n");
    }
}

static int getPhone(char phone[])
{
    int status;

    while (1)
    {
        printf("Enter phone number (11 digits): ");

        status = readLine(phone, PHONE_SIZE);

        if (status == -1)
        {
            return 0;
        }

        if (status == 0)
        {
            printf("Phone number too long.\n");
            continue;
        }

        trimSpaces(phone);

        if (isValidPhone(phone))
        {
            return 1;
        }

        printf("Invalid phone number. Enter exactly 11 digits.\n");
    }
}

int saveReservations(void)
{
    FILE *fp;
    int success = 1;

    fp = fopen(TEMP_RES_FILE, "wb");

    if (fp == NULL)
    {
        printf("Error: could not create temporary reservation file.\n");
        return 0;
    }

    if (fwrite(&nextID, sizeof(nextID), 1, fp) != 1)
    {
        success = 0;
    }

    if (success &&
        fwrite(&resCount, sizeof(resCount), 1, fp) != 1)
    {
        success = 0;
    }

    if (success &&
        fwrite(reservations,
               sizeof(struct Reservation),
               (size_t)resCount,
               fp) != (size_t)resCount)
    {
        success = 0;
    }

    if (fflush(fp) != 0)
    {
        success = 0;
    }

    if (fclose(fp) != 0)
    {
        success = 0;
    }

    if (!success)
    {
        printf("Error: reservation data could not be saved completely.\n");
        remove(TEMP_RES_FILE);
        return 0;
    }

        if (rename(TEMP_RES_FILE, RES_FILE) != 0)
    {
        
        remove(RES_FILE);

        if (rename(TEMP_RES_FILE, RES_FILE) != 0)
        {
            printf("Error: could not replace the reservation file.\n");
            remove(TEMP_RES_FILE);
            return 0;
        }
    }

    return 1;
}

static int isValidSavedRecord(
    const struct Reservation *record,
    int previousRecords)
{
    int i;
    int busIndex;

    if (record->reservationID < FIRST_RESERVATION_ID ||
        record->reservationID >= INT_MAX)
    {
        return 0;
    }

    if (memchr(record->passengerName, '\0',
               sizeof(record->passengerName)) == NULL)
    {
        return 0;
    }

    if (memchr(record->phone, '\0',
               sizeof(record->phone)) == NULL)
    {
        return 0;
    }

    if (!isValidName(record->passengerName) ||
        !isValidPhone(record->phone))
    {
        return 0;
    }

    if (record->seatNumber < 1 ||
        record->seatNumber > MAX_SEATS)
    {
        return 0;
    }

    busIndex = findBusIndex(record->busID);

    if (busIndex == -1)
    {
        return 0;
    }

    for (i = 0; i < previousRecords; i++)
    {
        if (reservations[i].reservationID == record->reservationID)
        {
            return 0;
        }

        if (reservations[i].busID == record->busID &&
            reservations[i].seatNumber == record->seatNumber)
        {
            return 0;
        }
    }

    return 1;
}

static void loadFromFile(void)
{
    FILE *fp;
    struct Reservation loaded[MAX_RESERVATIONS];

    int savedNextID;
    int savedCount;
    int calculatedNextID = FIRST_RESERVATION_ID;
    int i;
    int valid = 1;
    int extra;

    fp = fopen(RES_FILE, "rb");

    if (fp == NULL)
    {
        return;
    }

    if (fread(&savedNextID, sizeof(savedNextID), 1, fp) != 1 ||
        fread(&savedCount, sizeof(savedCount), 1, fp) != 1)
    {
        valid = 0;
    }

    if (valid &&
        (savedCount < 0 || savedCount > MAX_RESERVATIONS))
    {
        valid = 0;
    }

    if (valid &&
        fread(loaded,
              sizeof(struct Reservation),
              (size_t)savedCount,
              fp) != (size_t)savedCount)
    {
        valid = 0;
    }

    if (valid)
    {
        extra = fgetc(fp);

        if (extra != EOF || ferror(fp))
        {
            valid = 0;
        }
    }

    if (fclose(fp) != 0)
    {
        valid = 0;
    }

    if (!valid)
    {
        printf("Warning: reservations file is damaged. "
               "Starting with no loaded reservations.\n");
        return;
    }

    resCount = 0;

    for (i = 0; i < savedCount; i++)
    {
        if (!isValidSavedRecord(&loaded[i], i))
        {
            valid = 0;
            break;
        }

        reservations[i] = loaded[i];
        resCount++;
    }

    if (!valid)
    {
        printf("Warning: reservation file contains invalid or "
               "duplicate records. Starting empty.\n");

        resCount = 0;
        nextID = FIRST_RESERVATION_ID;
        return;
    }

    for (i = 0; i < resCount; i++)
    {
        if (reservations[i].reservationID >= calculatedNextID)
        {
            calculatedNextID = reservations[i].reservationID + 1;
        }
    }

    if (savedNextID > calculatedNextID)
    {
        calculatedNextID = savedNextID;
    }

    if (calculatedNextID < FIRST_RESERVATION_ID)
    {
        calculatedNextID = FIRST_RESERVATION_ID;
    }

    if (calculatedNextID >= INT_MAX)
    {
        nextID = INT_MAX;
    }
    else
    {
        nextID = calculatedNextID;
    }
}

static void syncSeatsWithReservations(void)
{
    int i;
    int busIndex;

    if (seatsSynced)
    {
        return;
    }

    for (i = 0; i < resCount; i++)
    {
        busIndex = findBusIndex(reservations[i].busID);

        if (busIndex == -1 ||
            !restoreSeat(busIndex, reservations[i].seatNumber))
        {
            printf("Warning: could not restore seat %d on bus %d.\n",
                   reservations[i].seatNumber,
                   reservations[i].busID);
        }
    }

    seatsSynced = 1;
}

void loadReservations(void)
{
    resCount = 0;
    nextID = FIRST_RESERVATION_ID;

    loadFromFile();
    syncSeatsWithReservations();
}

static int addReservation(
    const char name[],
    const char phone[],
    int busID,
    int seat)
{
    int id;

    if (resCount >= MAX_RESERVATIONS)
    {
        return -1;
    }

    if (name == NULL || phone == NULL ||
        strlen(name) >= sizeof(reservations[0].passengerName) ||
        strlen(phone) >= sizeof(reservations[0].phone))
    {
        return -1;
    }

    if (!isValidName(name) || !isValidPhone(phone))
    {
        return -1;
    }

    id = generateReservationID();

    if (id == -1)
    {
        printf("Error: reservation ID limit reached.\n");
        return -1;
    }

    reservations[resCount].reservationID = id;

    strcpy(reservations[resCount].passengerName, name);
    strcpy(reservations[resCount].phone, phone);

    reservations[resCount].busID = busID;
    reservations[resCount].seatNumber = seat;

    resCount++;

    return id;
}

static void removeReservation(int index)
{
    int i;

    if (index < 0 || index >= resCount)
    {
        return;
    }

    for (i = index; i < resCount - 1; i++)
    {
        reservations[i] = reservations[i + 1];
    }

    resCount--;
}

static void insertReservation(
    int index,
    const struct Reservation *record)
{
    int i;

    if (resCount >= MAX_RESERVATIONS ||
        index < 0 || index > resCount)
    {
        return;
    }

    for (i = resCount; i > index; i--)
    {
        reservations[i] = reservations[i - 1];
    }

    reservations[index] = *record;
    resCount++;
}

static int chooseBus(void)
{
    int tries;
    int busID;

    for (tries = 1; tries <= MAX_TRIES; tries++)
    {
        printf("Enter bus ID: ");

        busID = readPositiveInteger();

        if (busID == -2)
        {
            return -1;
        }

        if (busID > 0 && busExists(busID))
        {
            return busID;
        }

        printf("Invalid bus ID. Attempt %d of %d.\n",
               tries, MAX_TRIES);
    }

    printf("Too many invalid attempts. Reservation cancelled.\n");
    return -1;
}

static int chooseSeat(int busID)
{
    int busIndex;
    int tries;
    int seat;

    busIndex = findBusIndex(busID);

    if (busIndex == -1)
    {
        printf("Error: bus not found.\n");
        return -1;
    }

    displaySeats(busIndex);

    for (tries = 1; tries <= MAX_TRIES; tries++)
    {
        printf("Enter seat number (1-%d): ", MAX_SEATS);

        seat = readPositiveInteger();

        if (seat == -2)
        {
            return -1;
        }

        if (seat < 1 || seat > MAX_SEATS)
        {
            printf("Invalid seat number.\n");
        }
        else if (!isSeatAvailable(busIndex, seat))
        {
            printf("Seat %d is already taken.\n", seat);
        }
        else
        {
            return seat;
        }
    }

    printf("Too many invalid attempts. Reservation cancelled.\n");
    return -1;
}

static void printReservation(int index)
{
    int busIndex;
    struct Reservation record;

    if (index < 0 || index >= resCount)
    {
        printf("Error: invalid reservation record.\n");
        return;
    }

    record = reservations[index];

    printf("\nReservation ID: R%d\n", record.reservationID);
    printf("Passenger: %s\n", record.passengerName);
    printf("Phone: %s\n", record.phone);
    printf("Seat: %d\n", record.seatNumber);

    busIndex = findBusIndex(record.busID);

    if (busIndex == -1)
    {
        printf("Bus details are unavailable.\n");
        return;
    }

    displayBusDetails(busIndex);
}

static int readReservationID(void)
{
    char line[20];
    int status;
    int start = 0;
    int i;
    int value = 0;
    size_t length;

    printf("Enter reservation ID (e.g. R1001): ");

    status = readLine(line, sizeof(line));

    if (status != 1)
    {
        return -1;
    }

    trimSpaces(line);

    if (line[0] == 'R' || line[0] == 'r')
    {
        start = 1;
    }

    length = strlen(line);

    if (length <= (size_t)start ||
        length - (size_t)start > 9)
    {
        return -1;
    }

    for (i = start; i < (int)length; i++)
    {
        unsigned char ch = (unsigned char)line[i];

        if (!isdigit(ch))
        {
            return -1;
        }

        value = value * 10 + (ch - '0');
    }

    return value;
}

static int askYesNo(void)
{
    char answer[10];
    int status;
    int i;

    while (1)
    {
        status = readLine(answer, sizeof(answer));

        if (status == -1)
        {
            return -1;
        }

        if (status == 0)
        {
            printf("Answer too long. Enter yes or no: ");
            continue;
        }

        trimSpaces(answer);

        for (i = 0; answer[i] != '\0'; i++)
        {
            answer[i] = (char)tolower((unsigned char)answer[i]);
        }

        if (strcmp(answer, "y") == 0 ||
            strcmp(answer, "yes") == 0)
        {
            return 1;
        }

        if (strcmp(answer, "n") == 0 ||
            strcmp(answer, "no") == 0)
        {
            return 0;
        }

        printf("Please enter yes or no: ");
    }
}

void reserveTicket(void)
{
    char passengerName[NAME_SIZE];
    char phone[PHONE_SIZE];

    int busID;
    int seat;
    int busIndex;
    int id;
    int oldNextID;

    printf("\n========== RESERVE TICKET ==========\n");

    if (resCount >= MAX_RESERVATIONS)
    {
        printf("Reservation list is full.\n");
        return;
    }

    busID = chooseBus();

    if (busID == -1)
    {
        return;
    }

    if (!getPassengerName(passengerName))
    {
        printf("\nInput ended. Reservation cancelled.\n");
        return;
    }

    if (!getPhone(phone))
    {
        printf("\nInput ended. Reservation cancelled.\n");
        return;
    }

    seat = chooseSeat(busID);

    if (seat == -1)
    {
        return;
    }

    busIndex = findBusIndex(busID);

    if (busIndex == -1)
    {
        printf("Error: bus not found. No reservation was made.\n");
        return;
    }

    if (!reserveSeat(busIndex, seat))
    {
        printf("Could not reserve the seat. No reservation was made.\n");
        return;
    }

    oldNextID = nextID;

    id = addReservation(passengerName, phone, busID, seat);

    if (id == -1)
    {
        releaseSeat(busIndex, seat);
        nextID = oldNextID;

        printf("Could not create the reservation. "
               "The seat was released.\n");
        return;
    }

    if (!saveReservations())
    {
        removeReservation(findReservation(id));
        nextID = oldNextID;

        if (!releaseSeat(busIndex, seat))
        {
            printf("Warning: the seat could not be released "
                   "after the save failure.\n");
        }

        printf("Reservation failed because it could not be saved.\n");
        return;
    }

    printf("\nReservation successful!\n");
    printReservation(findReservation(id));
}

void cancelReservation(void)
{
    int id;
    int index;
    int busIndex;
    int seat;
    int answer;

    struct Reservation oldReservation;

    printf("\n========== CANCEL RESERVATION ==========\n");

    id = readReservationID();

    if (id == -1)
    {
        printf("Invalid reservation ID.\n");
        return;
    }

    index = findReservation(id);

    if (index == -1)
    {
        printf("Reservation not found.\n");
        return;
    }

    printReservation(index);

    printf("\nCancel this reservation? (y/n): ");

    answer = askYesNo();

    if (answer != 1)
    {
        printf("Cancellation aborted.\n");
        return;
    }

    oldReservation = reservations[index];

    busIndex = findBusIndex(oldReservation.busID);
    seat = oldReservation.seatNumber;

    if (busIndex == -1)
    {
        printf("Could not find the bus. Reservation not cancelled.\n");
        return;
    }

    if (!releaseSeat(busIndex, seat))
    {
        printf("Could not release the seat. "
               "Reservation not cancelled.\n");
        return;
    }

    removeReservation(index);

    if (!saveReservations())
    {
        insertReservation(index, &oldReservation);

        if (!reserveSeat(busIndex, seat))
        {
            printf("Warning: reservation was restored in memory, "
                   "but the seat could not be marked as booked.\n");
        }

        printf("Cancellation failed because the updated data "
               "could not be saved.\n");
        return;
    }

    printf("Reservation cancelled successfully.\n");
}

void viewReservation(void)
{
    int id;
    int index;

    printf("\n=========== VIEW RESERVATION ===========\n");

    id = readReservationID();

    if (id == -1)
    {
        printf("Invalid reservation ID.\n");
        return;
    }

    index = findReservation(id);

    if (index == -1)
    {
        printf("Reservation not found.\n");
        return;
    }

    printReservation(index);
}
