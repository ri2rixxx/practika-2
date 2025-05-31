#ifndef FUNCTIONS_MATH_H
#define FUNCTIONS_MATH_H

#include <cstdint>

// Проверка на простоту
bool isPrime(uint64_t p);

// Быстрое возведение в степень по модулю
uint64_t modularPow(uint64_t a, uint64_t x, uint64_t p);

// Расширенный алгоритм Евклида — x и y могут быть отрицательными
uint64_t extendedGcd(int64_t a, int64_t b, int64_t& x, int64_t& y);

#endif
