#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <math.h>
#include <map>

using namespace std;

string s, aux;
map < string, int > app;

int main() {
    cin >> s;
    aux = s;
    for (int i = 0; i < aux.size()-1; i++)
        s += aux[i];

    for (int i = 0; i < aux.size(); i++) {
        string x = "";
        for (int j = 0; j < aux.size(); j++)
            x += s[i+j];
        app[x]++;
    }

    printf("%d\n", app.size());

    return 0;
}
