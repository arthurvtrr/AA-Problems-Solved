#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,x[10010],a=1,f=0;

        while (1) {
           scanf("%d",&n);
            if (n == 0) break;
                for(i=0 ; i<n ; i++){
                    scanf("%d",&x[i]);
                }

                for(i=0 ; i<n-2 ; i++){
                    if((x[a] > x[i] && x[a] > x[i+2]) || (x[a] < x[i] && x[a] < x[i+2])){
                        f++;
                    }
                    a++;
                }

                if((x[0] > x[n-1] && x[0] > x[1]) || (x[0] < x[n-1] && x[0] < x[1])){
                    f++;
                }

                if((x[n-1] > x[0] && x[n-1] > x[n-2]) || (x[n-1] < x[0] && x[n-1] < x[n-2])){
                    f++;
                }

            printf("%d\n",f);
            f=0;
            a=1;
        }

    return 0;
}
