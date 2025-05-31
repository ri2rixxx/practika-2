#include "funcMath.h"

bool isPrime(uint64_t p) {
    if (p < 2) return false;
    for (uint64_t i = 2; i * i <= p; ++i)
        if (p % i == 0) return false;
    return true;
}

uint64_t modularPow(uint64_t a, uint64_t x, uint64_t p) {
    uint64_t res = 1;
    a %= p;
    while (x > 0) {
        if (x % 2 == 1)
            res = (__uint128_t(res) * a) % p;
        a = (__uint128_t(a) * a) % p;
        x /= 2;
    }
    return res;
}

// Расширенный алгоритм Евклида с корректной работой со знаковыми числами
uint64_t extendedGcd(int64_t a, int64_t b, int64_t &x, int64_t &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return static_cast<uint64_t>(a >= 0 ? a : -a);  // возвращаем модуль
    }
    int64_t x1, y1;
    uint64_t d = extendedGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return d;
}
