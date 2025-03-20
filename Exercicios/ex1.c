#include <stdio.h>

int main(){
    int entrada = 0;
    int a,b,c;
    a = 1;
    b = 2;
    c = 3;
    scanf("%d", &entrada);
    int bool = 0;
    int resp=0;
    while(!bool)
    {
        if ((resp = a*b*c) >= entrada)
            bool = 1;
        else
        {
            a++;
            b++;
            c++;
        }
    }
    if (entrada == resp)
        printf("1\n");
    else
        printf("0\n");
    
    return 0;
}