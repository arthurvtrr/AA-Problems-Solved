#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char op[5];
    int n,r,i,a=0,b=0;

    scanf("%d", &n);

    for(i=0 ; i<n ; i++){

        scanf("%s", op);

        if(strcmp(op,"x++")==0){
            a++;
        }

        else if(strcmp(op,"x--")==0){
            b++;
        }
    }
                        r = a-b;

                                printf("%d\n", r);

    return 0;
}
