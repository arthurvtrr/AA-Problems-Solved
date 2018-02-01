#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <string>

using namespace std;

int n, pos[4] = {0, 2, 6, 19};
string s;
int cont[50];

int main() {
    scanf("%d", &n);
    cin >> s;

    if (n % 4 != 0) printf("===\n");
    else {
        for (int i = 0; i < n; i++)
            if (s[i] != '?')
                cont[s[i] - 'A']++;

        bool valid = true;

        for (int i = 0; i < 50; i++)
            if (cont[i] > n / 4)
                valid = false;

        if (!valid) printf("===\n");
        else {
            int ind = 0;

            for (int i = 0; i < n; i++)
                if (s[i] == '?') {
                    while (cont[pos[ind]] == n / 4)
                        ind++;

                    s[i] = pos[ind] + 'A';
                    cont[pos[ind]]++;
                }

            cout << s << endl;
        }
    }

    return 0;
}

