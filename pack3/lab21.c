#include <stdio.h>
#include <stdlib.h>

void decimalToBase(int number, int r) {
    char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Символы для представления цифр в системе счисления
    int base = 1 << r; // Вычисляем основание системы счисления по формуле 2^r
    char* res = (char*)malloc(32 * sizeof(char)); // Выделяем память для хранения символов числа
    int i = 0;
    int is_negative = 0;
    if (res == NULL){
        printf("Memmory does not allocate\n");
        return;
    }
    // Проверяем, является ли число отрицательным
    if (number < 0) {
        is_negative = 1;
        number = -number; // Преобразуем отрицательное число в положительное
    }

    // Переводим число в выбранную систему счисления
    while (number > 0) {
        res[i] = digits[number & (base - 1)];
        number = number >> r;
        i++;
    }

    // Выводим знак минус, если число отрицательное
    if (is_negative) {
        printf("-");
    }

    // Выводим полученное число в обратном порядке
    for (int j = i - 1; j >= 0; j--) {
        printf("%c", res[j]);
    }
    printf("\n");

    free(res); // Освобождаем выделенную память
}

int main() {
    int number = 1200; // Число, которое нужно перевести

    for (int r = 1; r <= 5; r++) {
        decimalToBase(number, r);
    }

    return 0;
}
