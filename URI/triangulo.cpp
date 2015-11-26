#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int lista[4];
    for (int i = 0; i < 4; i++) {
        scanf("%d", &lista[i]);
    }
    sort(lista, lista+4);

    if (lista[2] < lista[1] + lista[0] || lista[3] < lista[2] + lista[1]) printf("S\n");
    else printf("N\n");
    return 0;
}
