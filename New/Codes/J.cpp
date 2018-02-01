#include <stdio.h>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

int t;
char op[30][30];
string s;

bool solve(string word, int player) {
    if (word.size() == 1) {
        if (word == "a" || word == "e" || word == "i" || word == "o" || word == "u") return true;
        else return false;
    }

    string a = "", b = "";
    for (int i = 0; i < word.size()-1; i += 2)
        a += op[word[i] - 'a'][word[i+1] - 'a'];

    for (int i = word.size()-1; i > 0; i -= 2)
        b += op[word[i] - 'a'][word[i-1] - 'a'];

    if (word.size() % 2 != 0) {
        a += word[word.size()-1];
        b += word[0];
    }

    if (player == 1)
        return solve(a, 2) || solve(b, 2);
    else
        return solve(a, 1) && solve(b, 1);
}

int main() {
    scanf("%d", &t);

    while (t--) {
        for (int i = 0; i < 26; i++)
            scanf("%s", op[i]);

        cin >> s;

        if (solve(s, 1)) printf("Salah\n");
        else printf("Marzo\n");
    }
}
