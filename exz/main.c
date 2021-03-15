#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// #define FOR printf("Hello world!")

int main(int argc, char* argv[]) {

    int count = 20;
    int result = 0;
    for(int i = 0; i < 100; i++) {
        count = 20 + count;
        result += count;
    }

    printf("%d", result);
    return 0;
}