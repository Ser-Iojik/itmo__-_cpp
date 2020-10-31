#include <stdio.h>
#include <locale.h>

// Перечисляемый тип данных
enum PrintDevices {
    Book = 0,
    Magazine = 1,
    Newspaper = 2
};

// структура для отрезка
// Записывает последовательно различные переменные (int, char и тд)
struct Section {
    int length;
};

// union позволяет переиспользовать одну и ту же область памяти для хранения разных полей данных
union StateMP3 {
    int value;
    struct {
        unsigned Reproduction : 1; // Воспроизведение
        unsigned Pause : 1; // Пауза
        unsigned Recording : 1; // Запись
    };
};

int main() {
    setlocale(LC_ALL, "RUS");
    // Task 1
    // Отобразим Газету
    enum PrintDevices a = 2;
    printf("%d\n", a);

    // Task 2
    struct Section rect;

    printf("Section length: ");
    scanf("%d", &rect.length);

    printf("Section length = %d\n\n", rect.length);

    // Task 3
    union StateMP3 st;
    printf(" 16-: ");
    scanf("%x", &st.value);

    printf("DSL: %s\nPPP: %s\nLink: %s\n",
        st.Reproduction ? "ON" : "OFF",
        st.Pause ? "ON" : "OFF",
        st.Recording ? "ON" : "OFF");

    return 0;
}
