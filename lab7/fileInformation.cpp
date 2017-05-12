#include "fileInformation.h"

void Read(FILE *database, guestInformation &guest){
    fscanf(database, "%s\n", &guest.surname);
    fscanf(database, "%s\n", &guest.name);
    fscanf(database, "%s\n", &guest.patronymic);
    fscanf(database, "%d\n", &guest.passportNumber);
    fscanf(database, "%d\n", &guest.roomNumber);
    fscanf(database, "%d\n", &guest.roomType);
    fscanf(database, "%s\n", &guest.dateOfArrival);
    fscanf(database, "%s\n", &guest.departureDate);
}

void Write(FILE *database, guestInformation guest){
    fprintf(database, "%s\n", guest.surname);
    fprintf(database, "%s\n", guest.name);
    fprintf(database, "%s\n", guest.patronymic);
    fprintf(database, "%d\n", guest.passportNumber);
    fprintf(database, "%d\n", guest.roomNumber);
    fprintf(database, "%d\n", guest.roomType);
    fprintf(database, "%s\n", guest.dateOfArrival);
    fprintf(database, "%s\n", guest.departureDate);
}

void LoadInformationFromFile(list<guestInformation> &guestList, rooms &availableRooms, rooms &occupiedRooms, int &guestCount, char *currentDate){
    FILE *database = fopen("database.txt", "r");
    if (database == NULL){
        cout << "Файл database.txt не найден!";
        exit(0);
    }

    fscanf(database, "%d%d%d%d\n", &availableRooms.standart, &availableRooms.juniorSuite, &availableRooms.suite, &availableRooms.royalSuite);
    fscanf(database, "%d%d%d%d\n", &occupiedRooms.standart, &occupiedRooms.juniorSuite, &occupiedRooms.suite, &occupiedRooms.royalSuite);

    fscanf(database, "%s\n", currentDate);
    fscanf(database, "%d\n", &guestCount);

    guestInformation guest;
    for (int i = 0; i < guestCount; ++i){
        Read(database, guest);
        guestList.push_back(guest);
    }
}

void LoadInformationToFile(list<guestInformation> &guestList, rooms &availableRooms, rooms &occupiedRooms, int &guestCount, char *currentDate){
    FILE *database = fopen("database.txt", "w");
    if (database == NULL){
        cout << "Файл database.txt не найден!";
        exit(0);
    }

    fprintf(database, "%d %d %d %d\n", availableRooms.standart, availableRooms.juniorSuite, availableRooms.suite, availableRooms.royalSuite);
    fprintf(database, "%d %d %d %d\n", occupiedRooms.standart, occupiedRooms.juniorSuite, occupiedRooms.suite, occupiedRooms.royalSuite);

    fprintf(database, "%s\n", currentDate);
    fprintf(database, "%d\n", guestList.size());

    for (list<guestInformation>::iterator it = guestList.begin(); it != guestList.end(); ++it){
        Write(database, *it);
    }

    fclose(database);
}
