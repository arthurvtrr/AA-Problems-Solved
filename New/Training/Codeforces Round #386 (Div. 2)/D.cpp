#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <string>

using namespace std;

int n, k, a, b, quant[100100];

int main() {
    scanf("%d %d %d %d", &n, &k, &a, &b);

    int pos = 0;
    for (int i = 0; i < max(a, b); i++) {
        quant[pos]++;
        pos++;
        pos %= min(a,b)+1;
    }

    if (quant[0] > k) printf("NO\n");
    else {
        string s = "";

        for (int i = 0; i < min(a,b); i++) {
            for (int j = 0; j < quant[i]; j++) {
                if (a > b) s += 'G';
                else s += 'B';
            }
            if (a > b) s += 'B';
            else s += 'G';
        }

        for (int i = 0; i < quant[min(a, b)]; i++) {
            if (a > b) s += 'G';
            else s += 'B';
        }

        cout << s << endl;
    }

    return 0;
}



