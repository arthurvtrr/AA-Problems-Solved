#include <bits/stdc++.h>

using namespace std;

#define N 100100
#define psi pair < string, int >

string s;
int k;
priority_queue < psi, vector <psi>, greater<psi> > fila;

int main() {
	cin >> s;
	scanf("%d", &k);
	long long n = s.size();

	if (n * (n+1) / 2 < k) printf("No such line.\n");
	else {
        for (int i = 0; i < n; i++) {
            string aux = "";
            aux += s[i];
            fila.push(psi(aux, i));
        }

        for (int i = 0; i < k-1; i++) {
            psi x = fila.top();
            fila.pop();
            if (x.second != n-1) fila.push(psi(x.first + s[x.second+1], x.second+1));
        }

        cout << fila.top().first << endl;
    }
	return 0;
}
