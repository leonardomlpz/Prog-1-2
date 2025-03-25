#include <stdio.h>

int fat_rec(int a){
    if (a == 1)
        return a;
    else return (a * fat_rec(a - 1));
}

int main(){
    int entr = 0;
    int resp = 0;
    scanf("%d", &entr);
    if (entr < 1)
        return 0;
    
    resp = fat_rec(entr);
    printf ("%d\n", resp);

    return 0;
}