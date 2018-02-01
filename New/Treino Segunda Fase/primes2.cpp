#include <bits/stdc++.h>

using namespace std;

bool prime[100000002];

int main() {
    for (int i = 2; i < 1000000002; i++) prime[i/10] = true;

    printf("fim\n");
    return 0;
}
