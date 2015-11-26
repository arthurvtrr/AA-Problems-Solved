#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

int main()
{
    int x[200],mud,bal,i,r=0,p=0,d;

        scanf("%d %d", &bal, &mud);

    for(i=0 ; i<bal ; i++){

        scanf("%d", &x[i]);

            p += x[i];
    }

    sort(x, x+bal);

    for(i=0 ; i<mud ; i++){

        r += x[i]*-1;
    }

        d = (r*2) + p;

            printf("%d\n", d);

    return 0;
}
