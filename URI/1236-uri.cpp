#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
    int n;
    string s;
    scanf("%d\n", &n);

    for (int t = 0; t < n; t++) {
        getline(cin, s);
        int cont0 = 0, cont_ = 0;
        string aux = "";

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '0') cont0++;
            else if (s[i] != '0' && cont0 > 2) {
                while (cont0) {
                    aux += '#';
                    aux += (char) (NULL + min(255, cont0));
                    cont0 -= min(255, cont0);
                }
            }
            else if (s[i] != '0') {
                for (int x = 0; x < cont0; x++) aux += '0';
                cont0 = 0;
            }

            if (s[i] == ' ') cont_++;
            else if (s[i] != ' ' && cont_ > 2) {
                while (cont_) {
                    aux += '$';
                    aux += (char) (NULL + min(255, cont_));
                    cont_ -= min(255, cont_);
                }
            }
            else if (s[i] != ' ') {
                for (int x = 0; x < cont_; x++) aux += ' ';
                cont_ = 0;
            }

            if (s[i] != '0' && s[i] != ' ') aux += s[i];
        }

        if (cont0 > 2) {
            while (cont0) {
                aux += '#';
                aux += (char) (NULL + min(255, cont0));
                cont0 -= min(255, cont0);
            }
        }
        else for (int x = 0; x < cont0; x++) aux += '0';
        if (cont_ > 2) {
            while (cont_) {
                aux += '$';
                aux += (char) (NULL + min(255, cont_));
                cont_ -= min(255, cont_);
            }
        }
        else for (int x = 0; x < cont_; x++) aux += ' ';

        cout << aux << "\n";
    }
    return 0;
}
