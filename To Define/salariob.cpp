#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
    string nome;
    double sal, tv, t;

    cin >> nome;
    scanf("%lf", &sal);
    scanf("%lf", &tv);

    t = sal + tv*0.15;

    printf("TOTAL = R$ %.2f\n", t);

    return 0;
}
