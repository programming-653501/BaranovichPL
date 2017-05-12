#pragma once
#include <time.h>
#include <string.h>
#include <cstdlib>
#include <cstdio>
#include <list>
#include <iostream>
#include <conio.h>

using namespace std;

struct rooms{
    int standart;
    int juniorSuite;
    int suite;
    int royalSuite;
};

struct guestInformation{
    char surname[30];
    char name[30];
    char patronymic[30];
    int passportNumber;
    int roomNumber;
    int roomType;
    char dateOfArrival[11];
    char departureDate[11];
};

void IncDate(char *currentDate);
int StringToInt(char *currentDate, int initialPosition, int finalPosition);
void AddGuest(list<guestInformation> &guestList, rooms &availableRooms, rooms &occupiedRooms, char *currentDate);
int GetFreeRoomNumber(int roomType, list<guestInformation> &guestList, rooms &availableRooms, rooms &occupiedRooms);
int GetRoomType(rooms &availableRooms);
void WriteGuestList(list<guestInformation> &guestList);
void WriteGuestInformation(guestInformation temp);
void DepartureGuests(list<guestInformation> &guestList, char *currentDate, rooms &availableRooms, rooms &occupiedRooms);
int GetTime(char *currentDate);
void StringCompare(char *first, char *second, list<guestInformation>::iterator it, bool &flag);
void IntCompare(int first, int second, list<guestInformation>::iterator it, bool &flag);
void WriteAccomadationCost(int roomType, char *dateOfArrival, char *departureDate);
int DaysCount(char *dateOfArrival, char *departureDate);
void ChangeRoomsCount(int roomType, rooms &availableRooms, rooms &occupiedRooms);
void FindGuest(list<guestInformation> &guestList);
void EarlyDeparture(list<guestInformation> &guestList, rooms &availableRooms, rooms &occupiedRooms);
void WriteRoomCount(rooms &availableRooms);
