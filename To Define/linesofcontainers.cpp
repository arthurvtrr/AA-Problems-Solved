#include <stdio.h>
#include <algorithm>

using namespace std;

int l, c, cont[330][330];

int main() {
    while (scanf("%d %d", &l, &c) != EOF) {
        for (int i = 0; i < l; i++)
            for (int j = 0; j < c; j++)
                scanf("%d", &cont[i][j]);


    }
    return 0;
}
