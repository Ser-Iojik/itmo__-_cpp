#include <stdio.h>  

// Вариант 10
int main() {
    // 1 Task
    // Вводим константы - границы диапазона
    const int MIN_VALUE = 88;
    const int MAX_VALUE = 99;
    int x = 0;
    scanf("%d", &x);
    // Проверяем наличие x в диапазоне, если есть - выводим 1, иначе 0
    int result = MIN_VALUE <= x && x <= MAX_VALUE;
    printf("%d\n", result);

    // 2 Task
    int z;
    // Вводим число
    scanf("%d", &z);
    // Находим элемент на 10 бите
    z = z >> 9;
    z = z % 2;
    printf("%d", z);
    int x;
    // Вводим число
    scanf("%d", &x);
    z = z / 512;
    z = z % 2;
    printf("%d", x);

    return 0;
}