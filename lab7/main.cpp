#include "hotel.h"
#include "fileInformation.h"

using namespace std;

void MainMenu(char *currentDate){
    cout << "Сегодняшняя дата: " << currentDate << "\n\n";
    cout << "Выберите нужный пункт меню:\n";
    cout << "1. Заселить гостя\n";
    cout << "2. Оформить досрочный отъезд\n";
    cout << "3. Поиск постояльца\n";
    cout << "4. Вывести список всех постояльцев\n";
    cout << "5. Вывести количество свободных номеров\n";
    cout << "6. Перейти на следующий день\n";
    cout << "7. Ввести текущую дату\n";
    cout << "0. Выход\n";
}

int main()
{
    setlocale(LC_ALL, "Russian");
    rooms availableRooms, occupiedRooms;
    list<guestInformation> guestList;
    int guestCount;
    char currentDate[11];

    LoadInformationFromFile(guestList, availableRooms, occupiedRooms, guestCount, currentDate);

    int choice;
    while (true){
        MainMenu(currentDate);
        cin >> choice;
        system("cls");
        switch(choice){
            case 1:
                AddGuest(guestList, availableRooms, occupiedRooms, currentDate);
                break;
            case 2:
                EarlyDeparture(guestList, availableRooms, occupiedRooms);
                break;
            case 3:
                FindGuest(guestList);
                break;
            case 4:
                WriteGuestList(guestList);
                getch();
                system("cls");
                break;
            case 5:
                WriteRoomCount(availableRooms);
                break;
            case 6:
                IncDate(currentDate);
                DepartureGuests(guestList, currentDate, availableRooms, occupiedRooms);
                break;
            case 7:
                cout << "Введите текущую дату: ";
                scanf("%s", currentDate);
                DepartureGuests(guestList, currentDate, availableRooms, occupiedRooms);
                break;
            case 0:
                LoadInformationToFile(guestList, availableRooms, occupiedRooms, guestCount, currentDate);
                return 0;
        }
    }

    LoadInformationToFile(guestList, availableRooms, occupiedRooms, guestCount, currentDate);

    return 0;
}
