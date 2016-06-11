#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

struct Node {
    int val = 0;
    int quant = 0;

    vector < Node > children;

    Node &left() {
        if (children.empty())
            children.resize(2);
        return children[0];
    }

    Node &right() {
        if (children.empty())
            children.resize(2);
        return children[1];
    }

    void update(int ini, int fim, int pos, int x) {
        if (ini == fim) {
            if (x == pos) {
                val = x;
                quant++;
            }
            else {
                if (quant <= 1) {
                    val = 0;
                    quant = 0;
                }
                else quant--;
            }
            return;
        }
        int meio = (ini + fim) / 2;

        if (pos <= meio) left().update(ini, meio, pos, x);
        else right().update(meio+1, fim, pos, x);

        val = gcd(left().val, right().val);
    }

    int query(int ini, int fim, int start, int end) {
        if (start > fim || end < ini)
            return 0;
        if (ini >= start && fim <= end)
            return val;

        int meio = (ini + fim) / 2;

        return gcd(left().query(ini, meio, start, end), right().query(meio+1, fim, start, end));
    }
};

int main() {
    int q, x;
    char c;
    Node segTree;

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf(" %c %d", &c, &x);
        if (c == '+')
            segTree.update(1, 1000000000, x, x);
        else
            segTree.update(1, 1000000000, x, 0);

        int aux = segTree.query(1, 1000000000, 1, 1000000000);

        printf("%d\n", aux? aux : 1);
    }
    return 0;
}
