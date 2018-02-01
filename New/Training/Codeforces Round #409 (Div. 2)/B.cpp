#include <bits/stdc++.h>

using namespace std;

string x, y;

int main() {
    cin >> x >> y;

    string s = "";
    for (int i = 0; i < x.size(); i++) {
        if (x[i] < y[i]) {
            printf("-1\n");
            exit(0);
        }
        else {
            s += y[i];
        }
    }

    cout << s << endl;

    return 0;
}
