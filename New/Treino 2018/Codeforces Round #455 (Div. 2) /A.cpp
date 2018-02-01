#include <bits/stdc++.h>

using namespace std;

string a, b;
set < string > aux;

int main() {
    cin >> a >> b;

    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < b.size(); j++) {
            string x = "";
            for (int k = 0; k <= i; k++)
                x += a[k];
            for (int k = 0; k <= j; k++)
                x += b[k];
            aux.insert(x);
        }

    cout << *aux.begin() << endl;
    return 0;
}
