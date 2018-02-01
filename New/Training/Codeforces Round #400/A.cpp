#include <bits/stdc++.h>

using namespace std;

string v1, v2;
string a, b;
int n;

int main() {
    cin >> v1 >> v2;
    cout << v1 << " " << v2 << endl;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        if (a == v1) v1 = b;
        else v2 = b;
        cout << v1 << " " << v2 << endl;
    }
    return 0;
}
