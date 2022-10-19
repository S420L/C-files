#include <stdio.h>

int main()
{
    unsigned int v = 19;
    char parity = 0;
    while (v) {
    printf("%i\t", v);
    printf("%c\t", parity);
    parity = !parity;
    v = v & (v - 1);
    printf("%i\n", v);
    }
}