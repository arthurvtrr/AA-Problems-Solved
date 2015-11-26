#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main() {
    string name;
    double sum = 0.0;
    int v, times = 0;

    while(!(getline(cin, name)).eof()) {
        scanf("%d", &v);
        sum += v;
        times++;
    }

    double m = sum / times;
    printf("%.1f\n", m);

    return 0;
}
