#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, people[110000], sum = 0, s = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", &people[i]);

    sort(people, people+n);

    for (int i = 0; i < n; i++) {
        if (people[i] >= sum) s++;
        sum += people[i];
    }

    printf("%d\n", s);

    return 0;
}
