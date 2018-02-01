#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

string s;
vector < string > level[1000100];
stack < int > pilha;

int main() {
    cin >> s;

    pilha.push(1000000000);

    string aux = "";
    int lvl = 1, type = 0, quant = 0;

    int maxlvl = 1;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] != ',' && type == 0) {
            aux += s[i];
        }
        else if (s[i] != ',' && type == 1) {
            quant *= 10;
            quant += s[i] - '0';
        }
        else if (s[i] == ',' && type == 0) {
            maxlvl = max(maxlvl, lvl);
            level[lvl].push_back(aux);
            aux = "";
            lvl++;
            type = 1;
        }
        else if (s[i] == ',' && type == 1) {
            pilha.push(quant);
            quant = 0;
            type = 0;

            while (pilha.top() == 0) {
                pilha.pop();
                lvl--;
            }
            int x = pilha.top();
            pilha.pop();
            pilha.push(x-1);
        }
    }

    printf("%d\n", maxlvl);
    for (int i = 1; i <= maxlvl; i++) {
        for (int j = 0; j < level[i].size(); j++) {
            if (j > 0) printf(" ");
            cout << level[i][j];
        }
        printf("\n");
    }

    return 0;
}

