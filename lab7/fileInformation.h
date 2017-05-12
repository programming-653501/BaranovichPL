#pragma once
#include "hotel.h"
#include <list>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>

using namespace std;

void LoadInformationToFile(list<guestInformation> &guestList, rooms &availableRooms, rooms &occupiedRooms, int &guestCount, char *currentDate);
void LoadInformationFromFile(list<guestInformation> &guestList, rooms &availableRooms, rooms &occupiedRooms, int &guestCount, char *currentDate);
void Read(guestInformation &guest);
