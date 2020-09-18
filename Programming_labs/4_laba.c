#include <stdio.h>  

void main() {
    // Вводим константы - границы диапазона
    const int MIN_VALUE = 88;
    const int MAX_VALUE = 99;
    int x = 0;
    scanf("%d", &x);
    // Проверяем наличие x в диапазоне, если есть - выводим 1, иначе 0
    int result = MIN_VALUE <= x && x <= MAX_VALUE;
    printf("%d\n", result);

    
}