#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;

int to_change[150];

char change(char c) {
    if (to_change[c]) {
        if (c - 'A' > 30) return 'f';
        return 'F';
    }
    return c;
}

int main() {
    char letters[] = {'s','j','b','z','p','v','x','S','J','B','Z','P','V','X'};
    for (char c : letters)
        to_change[c] = 1;

    char word[11000];
    while (fgets(word, sizeof word, stdin)) {
        if (feof(stdin)) break;
        int n = strlen(word);
        for (int i = 0; i < n; i++)
            word[i] = change(word[i]);

        int cont = 0;
        char f;
        for (int i = 0; i < n; i++) {
            if ((word[i] == 'f' || word[i] == 'F') && cont == 0) {
                f = word[i];
                cont++;
            }
            else if (word[i] == 'f' || word[i] == 'F') cont++;
            else {
                if (cont > 0) {
                    printf("%c", f);
                    cont = 0;
                }
                printf("%c", word[i]);
            }
        }

        if (cont > 0) printf("%c", f);
    }
    return 0;
}
