#include <stdio.h>
#include <locale.h>

int main() {

    // Task 2
    int len_talk;
    printf("Call duration: "); // Продолжительность разговоров
    scanf("%d", &len_talk);

    int pay;
    printf("Subscriber fee: "); // Величина абонентской платы
    scanf("%d", &pay);

    int cost;
    printf("Cost per minute: "); // Стоимость минуты
    scanf("%d", &cost);

    int excess = len_talk - 499;
    int sum;
    if (excess > 0){
        sum = pay + excess * cost;
    } else{
        sum = pay;
    }
    printf("Monthly maintenance cost - %d\n", sum); // Стоимость месячного обслуживания

    // Task 5
    int s, r, m;

    printf("Interest rate: "); // Процентная ставка
    scanf("%d", &r);

    printf("Amount: "); // Сумма
    scanf("%d", &s);

    printf("Number of months: "); // Кол-во месяцев
    scanf("%d", &m);


    for (int i = 1; i < m + 1; i++) {
        s = s + s * r / 100;
    }

    printf("%d ", s);

    return 0;
}