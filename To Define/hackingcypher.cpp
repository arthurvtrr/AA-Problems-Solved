#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#define ll long long

string word;
ll first[1100000], second[1100000];

ll fastPow(ll base, ll expo, ll mod) {
    if (expo == 0) return 1;
    if (expo == 1) return base;

    ll result = fastPow(base, expo / 2, mod) % mod;
    result *= result;
    result %= mod;
    if (expo % 2 != 0) result *= base;
    return result % mod;
}

int main() {
    cin >> word;
    int a, b;
    scanf("%d %d", &a, &b);

    int siz = word.size();

    first[0] = (word[0] - '0') % a;
    for (int i = 1; i < siz; i++)
        first[i] = (first[i-1] * 10 + (word[i] - '0')) % a;

    second[siz-1] = (word[siz-1] - '0') % b;
    for (int i = siz-2; i >= 0; i--) {
        second[i] = second[i+1] + (word[i] - '0') * fastPow(10, siz-i-1, b);
        second[i] %= b;
    }

    bool found = false;
    for (int i = 0; i < siz-1; i++)
        if (first[i] == 0 && second[i+1] == 0) {
            if (word[i+1] == '0') continue;
            found = true;
            printf("YES\n");
            for (int j = 0; j <= i; j++)
                printf("%c", word[j]);
            printf("\n");
            for (int j = i+1; j < siz; j++)
                printf("%c", word[j]);
            printf("\n");
            break;
        }

    if (!found) printf("NO\n");
    return 0;
}
