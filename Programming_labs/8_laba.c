#include <stdio.h>
#include <string.h>
#include <locale.h>

int main(void) {
    // Task 1
    const char *first  = "first";
    const char *second = "second";
    printf("%s%s", first, second);
    printf("%s", "\n");

	// Task 3 посимвольное сравнение двух строк
    if (strcmp(first, second) == 0){
        printf("Strings are equal\n");
    }
    if (strcmp(first, second) > 0){
        printf("Second symbol codes are less than first symbol codes\n");
    }
    if (strcmp(first, second) < 0){
        printf("First symbol codes are greater than second symbol codes\n");
    }

    // Task 5 в строку first копируем строку second
    first = second;
    printf("%s %s%s", first, second, "\n");
    first = "first";

    // Task 10
    char str1[] = "string with symbol s";
    char str2[] = "s";
    char *p = NULL;
 
    p = strpbrk(str1, str2);
    int count = 0;
    while (p) {
        // printf("%c ", *p);
        p++;
        p = strpbrk(p, str2);
        count++;
    }
    printf("%s%d%s", "Symbols found: ", count ,"\n");

    // Task 12
    printf("%d\n", strcspn(first, second));

	return 0;
}
