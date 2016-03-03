#include <stdio.h>
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    int n, m, p, quantidade;
    double preco, conta;
    string fruta;
    map < string, double > precos;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &m);

        for (int j = 0; j < m; j++) {
            cin >> fruta >> preco;
            precos[fruta] = preco;
        }

        scanf("%d", &p);

        conta = 0;
        for (int j = 0; j < p; j++) {
            cin >> fruta >> quantidade;
            conta += precos[fruta] * quantidade;
        }

        printf("R$ %.2lf\n", conta);
        precos.clear();
    }

    return 0;
}
