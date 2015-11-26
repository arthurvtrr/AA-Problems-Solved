#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,x,y,soma=0,i,j;

        scanf("%d", &n);

            for(i = 0 ; i < n ; i++){
                scanf("%d %d", &x, &y);

                if(x<y){

                for(j=x+1 ; j < y ; j++){

                    if(j%2 !=0){

                    soma +=j;

                    }

                    }

                }

                else{

                    for(j = y+1 ; j < x ; j++){

                        if(j%2 != 0){

                            soma +=j;

                        }
                    }

                }
                   printf("%d\n", soma);

                    soma = 0;
            }


    return 0;
}
