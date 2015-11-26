#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,y,j,n[110],p;

        for(i=0 ; i<100 ; i++){
            scanf("%d",&n[i]);
        }

        y = n[0];

        for(j=0 ; j<100 ; j++){

            if(n[j] > y){
                y = n[j];
                    p=j;
            }

        }
                printf("%d\n%d\n",y,p+1);

    return 0;
}
