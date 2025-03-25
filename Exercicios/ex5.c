#include <stdio.h>

int main(){
    int multi = 0;
    int reg1,reg2;

    int entrada = 0;
    scanf ("%d", &entrada);
    multi = entrada * 37;

    reg1 = multi%10;
    while (multi)
    {
        multi /= 10;
        reg2 = multi%10;
        if (reg1 != reg2)
        {
            printf ("NAO\n");
            break;
        }
        if (multi < 10)
        {
            printf ("SIM\n");
            break;
        }
    }
}