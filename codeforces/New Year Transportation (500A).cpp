#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

int numCells, goal, atual = 1;
int cells[33000];

int main()
{
    scanf("%d %d\n", &numCells, &goal);
    for (int i = 0; i < numCells - 1; i++) {
        scanf("%d", &cells[i]);
    }

    int j = 1;
    while (atual < numCells) {
        atual = j + cells[j-1];
        j = atual;
        if (atual == goal) {
            printf("YES");
            exit(0);
        }
    }

    printf("NO");
    return 0;
}