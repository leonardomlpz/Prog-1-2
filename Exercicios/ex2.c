#include <stdio.h>

int main(){
    int a,b;
    int condicao = 1;
    scanf("%d",&a);

    while(a)
    {
        scanf("%d",&b);
        if (b != (a*a))
        {
            condicao = 0;
            break;
        }
        scanf("%d",&a);
    }
    if (condicao)
        printf("1\n");
    else
        printf("0\n");

    return 0;
}