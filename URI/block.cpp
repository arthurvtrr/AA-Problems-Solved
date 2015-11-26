#include <stdio.h>
#include <string>
#include <stack>
#include <iostream>

using namespace std;

stack < int > blockW[30];
stack < int > aux;
int n, x, pos[30];

void move_onto(int a, int b) {
    while (blockW[pos[a]].top() != a) {
        x = blockW[pos[a]].top();
        blockW[x].push(x);
        pos[x] = x;
        blockW[pos[a]].pop();
    }
    while (blockW[pos[b]].top() != b) {
        x = blockW[pos[b]].top();
        blockW[x].push(x);
        pos[x] = x;
        blockW[pos[b]].pop();
    }

    blockW[pos[b]].pop();
    pos[b] = b;
    blockW[b].push(b);

    blockW[b].push(blockW[pos[a]].top());
    blockW[pos[a]].pop();
    pos[a] = pos[b];
}

void move_over(int a, int b) {
    while (blockW[pos[a]].top() != a) {
        x = blockW[pos[a]].top();
        blockW[x].push(x);
        pos[x] = x;
        blockW[pos[a]].pop();
    }
    blockW[pos[b]].push(blockW[pos[a]].top());
    blockW[pos[a]].pop();
    pos[a] = pos[b];
}

void pile_onto(int a, int b) {
    while (blockW[pos[b]].top() != b) {
        x = blockW[pos[b]].top();
        blockW[x].push(x);
        pos[x] = x;
        blockW[pos[b]].pop();
    }

    blockW[pos[b]].pop();
    pos[b] = b;
    blockW[b].push(b);

    while (blockW[pos[a]].top() != a) {
        aux.push(blockW[pos[a]].top());
        blockW[pos[a]].pop();
    }

    aux.push(blockW[pos[a]].top());
    blockW[pos[a]].pop();

    while (!aux.empty()) {
        blockW[pos[b]].push(aux.top());
        pos[aux.top()] = pos[b];
        aux.pop();
    }
}

void pile_over(int a, int b) {
    while (blockW[pos[a]].top() != a) {
        aux.push(blockW[pos[a]].top());
        blockW[pos[a]].pop();
    }
    aux.push(blockW[pos[a]].top());
    blockW[pos[a]].pop();
    while (!aux.empty()) {
        blockW[pos[b]].push(aux.top());
        pos[aux.top()] = pos[b];
        aux.pop();
    }
}

int main() {
    string c[4];
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        blockW[i].push(i);
        pos[i] = i;
    }

    int a, b;
    while (cin >> c[0]) {
        if (c[0][0] == 'q') break;

        cin >> a >> c[2] >> b;

        if(a != b && pos[a] != pos[b]) {
            if (c[0][0] == 'm') {
                if (c[2][1] == 'n') move_onto(a,b);
                else move_over(a,b);
            }
            else {
                if (c[2][1] == 'n') pile_onto(a,b);
                else pile_over(a,b);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << i << ":";
        if (blockW[i].empty()) cout << endl;
        else {
            while (!blockW[i].empty()) {
                aux.push(blockW[i].top());
                blockW[i].pop();
            }
            while (!aux.empty()) {
                cout << " " << aux.top();
                aux.pop();
            }
            cout << endl;
        }
    }

    return 0;
}
