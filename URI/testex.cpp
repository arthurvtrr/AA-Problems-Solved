#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main()
{
    int coelhos=0,ratos=0,sapos=0,soma,n,num;
    char animal[3];

        scanf("%d", &n);

        for(int i = 0; i < n ; i++){

            scanf("%d %s", &num, animal);

            if(strcmp(animal,"C")== 0){

                coelhos += num;

            }

            else if(strcmp(animal,"R")== 0){

                ratos += num;

            }

            else if(strcmp(animal,"S")== 0){

                sapos += num;

            }

        }

        soma = coelhos + ratos + sapos;


               printf("Total: %d cobaias\nTotal de coelhos: %d\nTotal de ratos: %d\nTotal de sapos: %d\n",soma,coelhos,ratos,sapos);
               printf("Percentual de coelhos: %.2f %\n", (float)coelhos * 100.0 / soma);
               printf("Percentual de ratos: %.2f %\n", (float)ratos * 100.0 / soma);
               printf("Percentual de sapos: %.2f %\n", (float)sapos * 100.0 / soma);
    return 0;
}
