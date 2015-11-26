#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,x,d=0,e=0,i;

    while(1){

        scanf("%d",&n);

            if(n == 0){
                break;
            }

         else{
                char a[n];

            scanf("%s",a);

            for(i = 0; i < n ; i++){



                    if(a[i] == 'D'){
                        d++;
                    }

                    else if(a[i] == 'E'){
                        e++;
                    }
            }

                    x = (d - e) % 4;

                        if(x == 0){
                            printf("N\n");
                        }

                        else if(x == 1 || x == -3){
                            printf("L\n");
                        }

                        else if(x == 2 || x == -2){
                            printf("S\n");
                        }

                        else if(x == 3 || x == -1){
                            printf("O\n");
                        }


                d = 0;
                e = 0;
        }
    }

    return 0;
}
