#include <bits/stdc++.h>

using namespace std;

int n, k;
string effec[55], chosen[55];
vector <string> names;

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n - k + 1; i++)
        cin >> effec[i];

    for (int i = 0; i < 26; i++) {
        string x = "";
        x += i + 'A';
        names.push_back(x);
    }

    for (int i = 0; i < 26; i++) {
        string x = "A";
        x += i + 'a';
        names.push_back(x);
    }

    int next = 0;
    for (int i = 0; i < k - 1; i++)
        chosen[i] = names[next++];

    for (int i = k-1; i < n; i++) {
        if (effec[i - k + 1] == "YES") chosen[i] = names[next++];
        else chosen[i] = chosen[i - k + 1];
    }

    for (int i = 0; i < n; i++) {
        if (i) printf(" ");
        cout << chosen[i];
    }
    printf("\n");

    return 0;
}

