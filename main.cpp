#include <iostream>
#include "main.h"
using namespace std;

// Объявляем enum для меню
enum MenuOption {
    EXIT = 0,
    FERMAT = 1,
    EXTENDED_EUCLID,
    MODULAR_INVERSE,
    HUGHES_CIPHER,
    CHAIN_FRACTION,
    ATTACK_SIMULATION,
    CRYPTO_STANDARDS
};

int main() {
    int choice;

    while (true) {
        cout << "\nВыберите задание:\n";
        cout << "1. Теорема Ферма\n";
        cout << "2. Расширенный алгоритм Евклида\n";
        cout << "3. Обратный элемент по модулю\n";
        cout << "4. Шифр Хьюза\n";
        cout << "5. Цепные дроби\n";
        cout << "6. Эмуляция атаки на шифр Хьюза\n";
        cout << "7. Вывод стандартов криптографии\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (static_cast<MenuOption>(choice)) {
            case FERMAT: teoremaFerma(); break;
            case EXTENDED_EUCLID: algEvklid(); break;
            case MODULAR_INVERSE: invElement(); break;
            case HUGHES_CIPHER: cipherHughes(); break;
            case CHAIN_FRACTION: chainFraction(); break;
            case ATTACK_SIMULATION: attackEmulation(); break;
            case CRYPTO_STANDARDS: cryptoStand(); break;
            case EXIT: return 0;
            default: cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }
}
