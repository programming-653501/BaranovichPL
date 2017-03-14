#include <iostream>
#include <windows.h>
#include <cmath>

using namespace std;

void menu(){
    cout << "Выберите нужное действие:\n";
    cout << "1. Ввод длины ребра тетраэдра.\n";
    cout << "2. Вывод общей длины всех ребер тетраэдра.\n";
    cout << "3. Вывод площади всех граней тетраэдра.\n";
    cout << "4. Вывод объема тетраэдра.\n";
    cout << "5. Вывод высоты тетраэдра.\n";
    cout << "6. Вывод радиуса вписанного шара.\n";
    cout << "7. Информация о версии и авторе программы.\n";
    cout << "8. Выход из программы.\n";
    cout << "\n\nВвод: ";
}

void input_data(double &edge){
    cout << "Введите длину ребра тетраэдра: ";
    cin >> edge;
    system("cls");
    if (edge <= 0.0) cout << "Неправильный ввод!\n\n";
}

double edges_length(double edge){
    return 6.0 * edge;
}

double faces_square(double edge){
    return sqrt(3.0) * edge * edge;
}

double tetrahedron_height(double edge){
    return sqrt(2.0 / 3) * edge;
}

double tetrahedron_volume(double edge){
    return 1.0 / 12 * tetrahedron_height(edge) * sqrt(3.0) * edge * edge;
}

double inscribed_ball_radius(double edge){
    return 3 * tetrahedron_volume(edge) / faces_square(edge);
}

void reference_information(){
    cout << "Версия программы:   1.0\n";
    cout << "Автор программы:    Баранович Павел\n\n";
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int choice = 0;
    double edge = 0;

    while (choice != 8){
        menu();
        cin >> choice;
        system("cls");
        switch (choice){
            case 1: input_data(edge); break;
            case 2:
                cout << "Общая длина всех ребер тетраэдра равна: ";
                cout << edges_length(edge) << "\n\n"; break;
            case 3:
                cout << "Площади всех граней тетраэдра равна: ";
                cout << faces_square(edge) << "\n\n"; break;
            case 4:
                cout << "Объем тетраэдра равен: ";
                cout << tetrahedron_volume(edge) << "\n\n"; break;
            case 5:
                cout << "Высота тетраэдра равна: ";
                cout << tetrahedron_height(edge) << "\n\n"; break;
            case 6:
                cout << "Радиус вписанного шара равен: ";
                cout << inscribed_ball_radius(edge) << "\n\n"; break;
            case 7:
                reference_information(); break;
            case 8: break;
            default: cout << "Неправильный ввод!\n\n";
        }
    }

    return 0;
}
