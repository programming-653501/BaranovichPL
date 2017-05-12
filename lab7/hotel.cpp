#include "hotel.h"

void WriteRoomCount(rooms &availableRooms){
    cout << "Количество свободных номеров обычного класса: " << availableRooms.standart << endl;
    cout << "Количество свободных полулюксов: " << availableRooms.juniorSuite << endl;
    cout << "Количество свободных люксов: " << availableRooms.suite << endl;
    cout << "Количество свободных королевских номеров: " << availableRooms.royalSuite << endl;

    getch();
    system("cls");
}

void EarlyDeparture(list<guestInformation> &guestList, rooms &availableRooms, rooms &occupiedRooms){
    WriteGuestList(guestList);
    cout << "Введите номер паспорта:\n";
    int passportNumber;
    cin >> passportNumber;
    for (list<guestInformation>::iterator it = guestList.begin(); it != guestList.end(); ++it)
        if ((*it).passportNumber == passportNumber){
            WriteAccomadationCost((*it).roomType, (*it).dateOfArrival, (*it).departureDate);
            ChangeRoomsCount((*it).roomType, availableRooms, occupiedRooms);
            cout << endl;
            guestList.erase(it);

            getch();
            system("cls");
            return;
        }
}

void FindGuest(list<guestInformation> &guestList){
    cout << "Выберите поле для поиска:\n";
    cout << "1. Фамилия\n";
    cout << "2. Имя\n";
    cout << "3. Отчество\n";
    cout << "4. Номер паспорта\n";
    cout << "5. Порядковый номер комнаты\n";
    cout << "6. Дата заселения\n";
    cout << "7. Дата выселения\n";
    int choice;
    cin >> choice;
    cout << "Введите значение поля: ";

    bool flag = true;
    int intTemp;
    char stringTemp[30];
    if (choice == 1 || choice == 2 || choice == 3 || choice == 6 || choice == 7)
        scanf("%s", stringTemp);
    else
        scanf("%d", &intTemp);
    system("cls");
    cout << "Подходящие постояльцы:\n";
    for (list<guestInformation>::iterator it = guestList.begin(); it != guestList.end(); ++it){
        switch (choice){
            case 1:
                StringCompare((*it).surname, stringTemp, it, flag);
                break;
            case 2:
                StringCompare((*it).name, stringTemp, it, flag);
                break;
            case 3:
                StringCompare((*it).patronymic, stringTemp, it, flag);
                break;
            case 4:
                IntCompare((*it).passportNumber, intTemp, it, flag);
                break;
            case 5:
                IntCompare((*it).roomNumber, intTemp, it, flag);
                break;
            case 6:
                StringCompare((*it).dateOfArrival, stringTemp, it, flag);
                break;
            case 7:
                StringCompare((*it).departureDate, stringTemp, it, flag);
                break;
        }
    }

    if (flag){
        system("cls");
        cout << "Постояльцев не найдено!\n";
    }

    getch();
    system("cls");
}

int GetTime(char *currentDate){
    struct tm *increaseDate;
    time_t timer = time(NULL);

    increaseDate = localtime(&timer);
    increaseDate->tm_mday = StringToInt(currentDate, 0, 1);
    increaseDate->tm_mon = StringToInt(currentDate, 3, 4) - 1;
    increaseDate->tm_year = StringToInt(currentDate, 6, 9) - 1900;
    timer = mktime(increaseDate);

    return timer;
}

int DaysCount(char *dateOfArrival, char *departureDate){
    return (GetTime(departureDate) - GetTime(dateOfArrival)) / (24 * 60 * 60) + 1;
}

void WriteAccomadationCost(int roomType, char *dateOfArrival, char *departureDate){
    cout << "Стоимость суточного проживания: " << 10 * roomType << " руб.\n";
    cout << "Общая стоимость проживания: " << 10 * roomType * DaysCount(dateOfArrival, departureDate) << " руб.\n";
}

void ChangeRoomsCount(int roomType, rooms &availableRooms, rooms &occupiedRooms){
    switch (roomType){
        case 1:
            ++availableRooms.standart;
            --occupiedRooms.standart;
            break;
        case 2:
            ++availableRooms.juniorSuite;
            --occupiedRooms.juniorSuite;
            break;
        case 3:
            ++availableRooms.suite;
            --occupiedRooms.suite;
            break;
        case 4:
            ++availableRooms.royalSuite;
            --occupiedRooms.royalSuite;
            break;
    }
}

void DepartureGuests(list<guestInformation> &guestList, char *currentDate, rooms &availableRooms, rooms &occupiedRooms){
    system("cls");
    cout << "Список выселенных сегодня:\n\n";
    bool flag = true;
    for (list<guestInformation>::iterator it = guestList.begin(); it != guestList.end();){
        if (!strcmp((*it).departureDate, currentDate)){
            WriteGuestInformation(*it);
            WriteAccomadationCost((*it).roomType, (*it).dateOfArrival, (*it).departureDate);
            ChangeRoomsCount((*it).roomType, availableRooms, occupiedRooms);
            cout << endl;
            it = guestList.erase(it);
            flag = false;
        }
        else
            ++it;
    }

    if (flag){
        system("cls");
        return;
    }

    getch();
    system("cls");
}

void StringCompare(char *first, char *second, list<guestInformation>::iterator it, bool &flag){
    if (!strcmp(first, second)){
        WriteGuestInformation(*it);
        flag = false;
        cout << endl;
    }
}

void IntCompare(int first, int second, list<guestInformation>::iterator it, bool &flag){
    if (first == second){
        WriteGuestInformation(*it);
        flag = false;
        cout << endl;
    }
}

void WriteGuestInformation(guestInformation temp){
    cout << "Фамилия: " << temp.surname << endl;
    cout << "Имя: " << temp.name << endl;
    cout << "Отчество: " << temp.patronymic << endl;
    cout << "Номер паспорта: " << temp.passportNumber << endl;

    cout << "Тип номера: ";
    switch (temp.roomType){
        case 1: cout << "Обычный класс\n"; break;
        case 2: cout << "Полулюкс\n"; break;
        case 3: cout << "Люкс\n"; break;
        case 4: cout << "Королевский номер\n"; break;
    }

    cout << "Порядковый номер комнаты: " << temp.roomNumber << endl;
    cout << "Дата заселения: " << temp.dateOfArrival << endl;
    cout << "Дата выселения: " << temp.departureDate << endl;
}

void WriteGuestList(list<guestInformation> &guestList){
    guestInformation temp;
    int i = 0;
    for (list<guestInformation>::iterator it = guestList.begin(); it != guestList.end(); ++it){
        cout << "№" << ++i << endl;
        WriteGuestInformation(*it);
        cout << endl;
    }
}

int GetRoomType(rooms &availableRooms){
    cout << "Выберите нужный тип номера:\n";
    cout << "1. Обычный класс(оталось свободных номеров: " << availableRooms.standart << ")\n";
    cout << "2. Полулюкс(оталось свободных номеров: " << availableRooms.juniorSuite << ")\n";
    cout << "3. Люкс(оталось свободных номеров: " << availableRooms.suite << ")\n";
    cout << "4. Королевский номер(оталось свободных номеров: " << availableRooms.royalSuite << ")\n";

    int choice;
    cin >> choice;
    return choice;
}

int GetFreeRoomNumber(int roomType, list<guestInformation> &guestList, rooms &availableRooms, rooms &occupiedRooms){
    int count;
    switch (roomType){
        case 1:
            count = availableRooms.standart + occupiedRooms.standart;
            --availableRooms.standart;
            ++occupiedRooms.standart;
            break;
        case 2:
            count = availableRooms.juniorSuite + occupiedRooms.juniorSuite;
            --availableRooms.juniorSuite;
            ++occupiedRooms.juniorSuite;
            break;
        case 3:
            count = availableRooms.suite + occupiedRooms.suite;
            --availableRooms.suite;
            ++occupiedRooms.suite;
            break;
        case 4:
            count = availableRooms.royalSuite + occupiedRooms.royalSuite;
            --availableRooms.royalSuite;
            ++occupiedRooms.royalSuite;
            break;
    }

    int *usedRooms = new int[++count];
    for (int i = 1; i <= count; ++i){
        usedRooms[i] = 0;
    }
    for (list<guestInformation>::iterator it = guestList.begin(); it != guestList.end(); ++it){
        if ((*it).roomType == roomType) usedRooms[(*it).roomNumber] = 1;
    }
    int answer = 0;
    for (int i = 1; i <= count; ++i)
        if (!usedRooms[i]){
            answer = i;
            break;
        }

    delete usedRooms;
    return answer;
}

void AddGuest(list<guestInformation> &guestList, rooms &availableRooms, rooms &occupiedRooms, char *currentDate){
    guestInformation temp;

    if (!availableRooms.standart && !availableRooms.juniorSuite && !availableRooms.suite && !availableRooms.royalSuite){
        cout << "Нет свободных номеров!\n";
        return;
    }

    cout << "Введите фамилию:\n";
    cin >> temp.surname;
    system("cls");
    cout << "Введите имя:\n";
    cin >> temp.name;
    system("cls");
    cout << "Введите отчество:\n";
    cin >> temp.patronymic;
    system("cls");
    cout << "Введите номер паспорта:\n";
    cin >> temp.passportNumber;
    system("cls");

    temp.roomType = GetRoomType(availableRooms);
    temp.roomNumber = GetFreeRoomNumber(temp.roomType, guestList, availableRooms, occupiedRooms);
    strcpy(temp.dateOfArrival, currentDate);
    system("cls");

    cout << "Введите дату отъезда в формате dd.mm.yyyy:\n";
    cin >> temp.departureDate;
    system("cls");

    guestList.push_back(temp);
}

int StringToInt(char *currentDate, int initialPosition, int finalPosition){
    int answer = 0;
    for (int i = finalPosition, tenDegree = 1; i >= initialPosition; --i, tenDegree *= 10){
        answer += tenDegree * (currentDate[i] - '0');
    }
    return answer;
}

void IncDate(char *currentDate){
    struct tm *increaseDate;
    time_t timer = time(NULL);

    increaseDate = localtime(&timer);
    increaseDate->tm_mday = StringToInt(currentDate, 0, 1);
    increaseDate->tm_mon = StringToInt(currentDate, 3, 4) - 1;
    increaseDate->tm_year = StringToInt(currentDate, 6, 9) - 1900;
    timer = mktime(increaseDate);
    timer += 24 * 60 * 60;
    increaseDate = localtime(&timer);

    char temp[11] = {NULL};
    strftime(temp, 11, "%d.%m.%Y", increaseDate);

    strcpy(currentDate, temp);
}
