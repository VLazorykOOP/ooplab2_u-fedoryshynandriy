#include <iostream>
using namespace std;
#include "Tasks.h"
#include "Examples.h"
void MenuTask()
{
    system("chcp 1251");
   
    cout << "    1.  Обчислення виразів з використанням побітових операцій  \n";
    cout << "    2.  Шифрування даних з використання побітових операцій  \n";
    cout << "    3.  Шифрування даних з використання стуктур з бітовими полями \n";
    cout << "    4.  Задача із використання побітових операцій \n";
    cout << "    5.  Exit \n";
    cout << "Виберіть завдання:   \n";
}
void task1() {
    system("chcp 1251");
    cout << " Обчислення виразів з використанням побітових операцій  \n";
    int a, b, c, d, x, y;
    cout << "Вираз : " <<endl<<
        "            x = b * 2049 + ((d * 15 + 12 * a) / 2048) - c * 100 + d * 127; "<<endl<<
        "            x = b + 2^11 * b + ((d*2^4 - b + a*2^3 + a*2^2) / 2^11) - c*2^7 - c*2^4 - c*2^3- c*2^2 + d*2^7 - d" <<endl<<
        "            x = b + 2048*b + ((d * 16 - b + 8 * a + 4 * a) / 2048) - c * 128 + c * 16 + c * 8 + c*4 + d * 128 - d" << endl << endl;
    cout << " Введiть a b c d " << endl;
    cin >> a >> b >> c >> d;
    cout << endl;
    auto st = cin.rdstate();
    if (st != cin.goodbit) { cin.clear(); cout << " error \n"; cin.get(); cin.get(); return; }

    x = b + (b<<11) + (((d << 4) - b + (a << 3) + (a<< 2)) >>11) - (c << 7) + (c << 4 )+ (c << 3)+(c<<2) + (d << 7) - d;
    y = b * 2049 + ((d * 15 + 12 * a) / 2048) - c * 100 + d * 127;

    cout << " a= " << a << "  b= " << b << " c= " << c << " d= " << d << endl;
    cout << "  x1(побітові операції)= " << x << endl << "  x2(перевірка)= " << y << endl;
    cin.get();
    cin.get();
    return;
}

void task2(){
    system("chcp 1251");
    // Шифрування даних з використання побітових операцій 
    // Data encryption using bitwise operations
    cout << " Шифрування даних з використання побітових операцій   \n";

}

void task3()
{
    system("chcp 1251");
    // Шифрування даних з використання стуктур з бітовими полями 
    // Data encryption using structures with bit fields
    cout << "  Шифрування даних з використання стуктур з бітовими полями \n";
}


void task4()
{
    system("chcp 1251");
    // Задача із використання побітових операцій
    // The problem of using bitwise operations
    cout << " Задача із використання побітових операцій \n";

}


