#include <stdio.h>
#include <malloc.h>

#define N 4
int main() {

    
    // Task 1
    int a[] = {0, 3, 5, 7};
    int *pa = a;
    for (int i = 0; i < N; i++) {
        printf("%d ", *(pa + i));
    }
    printf("\n\n");




    // Task 2
    // указатель для блока памяти
    int i, *b;
    // число элементов массива
    int n = 4;
    // выделяем память для массива
    b = malloc(n * sizeof(int));
     
    // вводим числа в массив
    for (i = 0; i < n; i++) {
        printf("b[%d]=", i);
        scanf("%d", &b[i]);
    }
    printf("\n");
     
    // вывод введенных чисел на консоль
    for(i = 0; i < n; i++) {
        printf("%d ", b[i]);
    }
     
    // освобождаем память
    free(b);
    return 0;
}