#include <bits/stdc++.h>

using namespace std;

#define ll long long

string s;
ll q, p, m, g;
char ans;

struct node {
    ll sum, quant;
    node *child[30];
    node() {
        sum = quant = 0;
        for (int i = 0; i < 30; i++)
            child[i] = NULL;
    }
} *root;

void add(string x) {
    node *aux = root;
    ll n = x.size(), val = n * (n+1) / 2;

    for (int i = 0; i < n; i++) {
        if (!aux->child[x[i] - 'a'])
            aux->child[x[i] - 'a'] = new node();
        aux = aux->child[x[i] - 'a'];
        aux->sum += val; val -= i+1;
        aux->quant++;
    }
}

void get(ll k) {
    node *aux = root;
    string path = "";
    while (k) {
        for (int i = 0; i < 30; i++) {
            if (!aux->child[i]) continue;

            if (aux->child[i]->sum < k) k -= aux->child[i]->sum;
            else {
                ll val = aux->child[i]->quant * (path.size() + 1);
                if (val >= k) {
                    if (k % (path.size() + 1) == 0) ans = i + 'a';
                    else ans = path[(k % (path.size() + 1)) - 1];
                    k = 0; break;
                }
                else {
                    k -= aux->child[i]->quant * (path.size() + 1);
                    aux = aux->child[i];
                    path += i + 'a';
                    break;
                }
            }
        }
    }
}

int main() {
    cin >> s;
    root = new node();

    for (int i = 0; i < s.size(); i++) {
        string aux = "";
        for (int j = i; j < s.size(); j++)
            aux += s[j];
        add(aux);
    }

    scanf("%lld", &q);
    g = 0;
    for (int i = 0; i < q; i++) {
        scanf("%lld %lld", &p, &m);
        ll k = ((p * g) % m) + 1;
        get(k);
        printf("%c\n", ans);
        g += ans;
    }

    return 0;
}
