#include "main.h"
#include "funcMath.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <random>
using namespace std;

uint64_t readPositiveInt(const string& prompt) {
    uint64_t val;
    do {
        cout << prompt;
        cin >> val;
        if (val <= 0) cout << "Число должно быть положительным! Попробуйте снова.\n";
    } while (val <= 0);
    return val;
}

void teoremaFerma() {
    uint64_t a = readPositiveInt("Введите число a (положительное): ");
    uint64_t x = readPositiveInt("Введите число x (положительное): ");
    uint64_t p = readPositiveInt("Введите число p (простое и положительное): ");

    if (!isPrime(p)) {
        cout << "Число p не является простым!\n";
        return;
    }

    uint64_t reducedExponent = x % (p - 1);
    uint64_t result = modularPow(a, reducedExponent, p);

    cout << "Результат a^x mod p = " << result << endl;
}

void algEvklid() {
    uint64_t c = readPositiveInt("Введите число c (положительное): ");
    uint64_t m = readPositiveInt("Введите число m (положительное): ");

    int64_t u, v;
    uint64_t g = extendedGcd(c, m, u, v);

    cout << "НОД(" << c << ", " << m << ") = " << g << endl;
    cout << "Коэффициенты: u = " << u << ", v = " << v << endl;

    if (g == 1) {
        cout << "Обратный элемент: d = " << (u % m + m) % m << endl;
    } else {
        cout << "Обратного элемента нет (НОД ≠ 1)\n";
    }
}

void invElement() {
    uint64_t c = readPositiveInt("Введите число c (положительное): ");
    uint64_t m = readPositiveInt("Введите число m (положительное): ");

    int64_t u, v;
    uint64_t g = extendedGcd(c, m, u, v);

    if (g != 1) {
        cout << "Обратного элемента не существует, так как НОД ≠ 1\n";
    } else {
        uint64_t d = (u % m + m) % m;
        cout << "Обратный элемент: " << d << endl;
    }
}


void cipherHughes() {
    using namespace std;
    cout << "Введите сообщение для шифрования (Ctrl+D для окончания ввода):\n";

    string message, line;
    while (getline(cin, line)) {
        message += line + '\n';
    }
    if (!message.empty() && message.back() == '\n') message.pop_back();
    if (message.empty()) {
        cout << "Пустое сообщение.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    
    // Генерируем простой модуль m (200..500)
    vector<uint64_t> primes;
    for (uint64_t i = 200; i <= 500; ++i) {
        bool prime = true;
        for (uint64_t j = 2; j*j <= i; ++j) if (i % j == 0) { prime = false; break; }
        if (prime) primes.push_back(i);
    }
    random_device rd; mt19937 gen(rd()); uniform_int_distribution<size_t> dist_prime(0, primes.size() - 1);
    uint64_t m = primes[dist_prime(gen)];

    // Генерируем ключ k, взаимно простой с m-1
    int64_t u, v;
    uniform_int_distribution<uint64_t> dist_k(1, m - 2);
    uint64_t k;
    auto gcdExt = [](int64_t a, int64_t b, int64_t& x, int64_t& y) {
        if (b == 0) { x = 1; y = 0; return a; }
        int64_t x1, y1;
        uint64_t d = gcdExt(b, a % b, x1, y1);
        x = y1; y = x1 - (a / b)*y1;
        return d;
    };
    do {
        k = dist_k(gen);
    } while (gcdExt(k, m - 1, u, v) != 1);

    cout << "\nИспользуется модуль m = " << m << ", ключ k = " << k << "\n";

    auto modularPow = [](uint64_t base, uint64_t exp, uint64_t mod) {
        uint64_t res = 1; base %= mod;
        while (exp > 0) {
            if (exp & 1) res = (res * base) % mod;
            base = (base * base) % mod; exp >>= 1;
        }
        return res;
    };

    vector<uint64_t> encrypted;
    for (unsigned char ch : message)
        encrypted.push_back(modularPow(ch, k, m));

    cout << "\nЗашифрованное сообщение (числа):\n";
    for (auto val : encrypted) cout << val << " ";
    cout << "\n";

    gcdExt(k, m - 1, u, v);
    uint64_t kInv = (u % (m - 1) + (m - 1)) % (m - 1);

    string decrypted;
    for (auto val : encrypted)
        decrypted += static_cast<char>(modularPow(val, kInv, m));

    cout << "\nРасшифрованное сообщение:\n" << decrypted << "\n";

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void chainFraction() {
    int64_t a = 439;
    int64_t b = 118;
    int64_t r = 3;

    cout << "Разложение " << a << "/" << b << " в цепную дробь:\n";

    vector<int64_t> cf;
    int64_t num = a, den = b;
    while (den != 0) {
        cf.push_back(num / den);
        int64_t temp = num % den;
        num = den;
        den = temp;
    }

    cout << "Цепная дробь: [";
    cout << cf[0];
    if (cf.size() > 1) {
        cout << "; ";
        for (size_t i = 1; i < cf.size(); ++i) {
            cout << cf[i];
            if (i != cf.size() - 1)
                cout << ", ";
        }
    }
    cout << "]" << endl << endl;

    int64_t u, v;
    uint64_t g = extendedGcd(a, b, u, v);
    if (r % static_cast<int64_t>(g) != 0) {
        cout << "Уравнение не имеет решений.\n";
        return;
    }

    u *= (r / static_cast<int64_t>(g));
    v *= (r / static_cast<int64_t>(g));

    cout << "Решение уравнения " << a << "*a + " << b << "*b = " << r << ":\n";
    cout << "a = " << u << ", b = " << v << endl;
}


void attackEmulation() {
    cout << "Введите сообщение для атаки (завершите ввод пустой строкой):\n";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    string message;
    string line;
    while (true) {
        getline(cin, line);
        if (line.empty()) break;
        message += line + '\n';
    }

    vector<uint64_t> primes;
    for (uint64_t i = 200; i <= 500; ++i)
        if (isPrime(i)) primes.push_back(i);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<uint64_t> prime_dist(0, primes.size() - 1);
    uint64_t m = primes[prime_dist(gen)];

    uniform_int_distribution<uint64_t> dist_k(1, m - 2);
    int64_t k, u, v;
    do {
        k = dist_k(gen);
    } while (extendedGcd(k, m - 1, u, v) != 1);

    ofstream alice("alice.txt"), bob("bob.txt"), eve("eve.txt");

    vector<uint64_t> encrypted;
    for (char ch : message)
        encrypted.push_back(modularPow(static_cast<uint64_t>(ch), k, m));

    alice << "Открытое сообщение:\n" << message << endl;
    alice << "Ключ k: " << k << "\nМодуль m: " << m << "\nЗашифрованное сообщение (числа):\n";
    for (auto val : encrypted) alice << val << " ";
    alice << "\n\n";

    extendedGcd(k, m - 1, u, v);
    uint64_t kInv = (u % (m - 1) + (m - 1)) % (m - 1);

    string decrypted;
    for (auto val : encrypted)
        decrypted += static_cast<char>(modularPow(val, kInv, m));
    bob << "Расшифрованное сообщение:\n" << decrypted << endl;

    // Подробный лог для Евы
    eve << "=== АТАКА НА ШИФР ХЬЮЗА ===\n\n";
    eve << "Исходное сообщение:\n" << message << "\n";
    eve << "Выбранные параметры:\n";
    eve << "  Модуль m = " << m << "\n";
    eve << "  Ключ шифрования k = " << k << "\n";
    eve << "  Обратный ключ k^-1 = " << kInv << " (по модулю m-1)\n\n";

    eve << "Зашифрованное сообщение (числа):\n";
    for (auto val : encrypted) eve << val << " ";
    eve << "\n\n";

    eve << "Попытка расшифровки с обратным ключом:\n" << decrypted << "\n\n";

    eve << "Детали:\n";
    eve << "  НОД(k, m-1) = 1 подтверждает существование обратного ключа.\n";
    eve << "  Использована функция modularPow для возведения в степень по модулю.\n";

    eve.close();
    alice.close();
    bob.close();

    cout << "Файлы alice.txt, bob.txt и eve.txt созданы с подробной информацией.\n";
}

void cryptoStand() {
    ifstream fin("standards.txt");
    if (!fin) {
        cout << "Не удалось открыть файл standards.txt!\n";
        return;
    }

    cout << "\nСтандарты криптографии:\n\n";
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
    fin.close();
}
