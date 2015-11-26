#include <stdio.h>
#include <cstring>

using namespace std;

bool correct(char s1[110], char s2[110], char s3[110], char s4[110]) {
    if ((strlen(s1) - 2) / 2 >= (strlen(s2) - 2) && (strlen(s1) - 2) / 2 >= (strlen(s3) - 2) && (strlen(s1) - 2) / 2 >= (strlen(s4) - 2))
        return true;
    if ((strlen(s1) - 2) <= (strlen(s2) - 2) / 2 && (strlen(s1) - 2) <= (strlen(s3) - 2) / 2 && (strlen(s1) - 2) <= (strlen(s4) - 2) / 2)
        return true;

    return false;
}

int main() {
    char aux[2], word[5][110];

    for (int i = 0; i < 4; i++)
        scanf("%s", word[i]);

    int cont = 0;
    char last;
    if (correct(word[0], word[1], word[2], word[3])) {
        cont++;
        last = 'A';
    }
    if (correct(word[1], word[0], word[2], word[3])) {
        cont++;
        last = 'B';
    }
    if (correct(word[2], word[1], word[3], word[0])) {
        cont++;
        last = 'C';
    }
    if (correct(word[3], word[1], word[2], word[0])) {
        cont++;
        last = 'D';
    }
    if (cont != 1) last = 'C';

    printf("%c\n", last);

    return 0;
}
