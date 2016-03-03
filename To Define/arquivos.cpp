#include <stdio.h>
#include <stdlib.h>

int main()
{
   int n,bits,tam,a=0,b=0,r,c,i;

    scanf("%d %d", &n, &bits);

    for(i=0 ; i<n ; i++){

        scanf("%d", &tam);

            a +=tam;
    }

        c = a/bits;

            if(a%bits != 0){

                    b++; }

        r = c+b;

           printf("%d\n", r);

    return 0;
}
