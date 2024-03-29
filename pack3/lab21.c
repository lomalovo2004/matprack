#include <stdio.h>
#include <stdlib.h>

void decimal_to_base(int number, int r) {
    char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int base = 1 << r;
    char* res = (char*)malloc(32 * sizeof(char));
    if (res == NULL){
        printf("Memmory does not allocated\n");
        return;
    }
    int i = 0;
    int is_negative = 0;

    if (number < 0) {
        is_negative = 1;
        number = -number;
    }

    while (number > 0) {
        res[i] = digits[number & (base - 1)];
        number = number >> r;
        i++;
    }

    if (is_negative) {
        printf("-");
    }

    for (int j = i - 1; j >= 0; j--) {
        printf("%c", res[j]);
    }
    printf("\n");

    free(res);
}

int main() {
    int number = 10000000;

    if (number == 0 || number == -0){
        printf("0\n");
        printf("0\n");
        printf("0\n");
        printf("0\n");
        printf("0\n");
    }
    else{
        for (int r = 1; r <= 5; r++) {
            decimal_to_base(number, r);
        }
    }

    return 0;
}
