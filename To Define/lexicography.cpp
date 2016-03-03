#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;

int main() {
    char word[20];
    int freq[30];
    long long k, x = 1, fat[16], pos[30];
    fat[0] = 0;
    for (int i = 1; i < 17; i++) {
        x *= i;
        fat[i] = x;
    }

    while(1) {
        for (int i = 0; i < 30; i++) {
            freq[i] = 0;
            pos[i] = 0;
        }

        scanf("%s %lld", word, &k);
        if (word[0] == '#' && k == 0) break;

        string sol = "";
        int l = strlen(word);

        for (int i = 0; i < l; i++)
            freq[word[i] - 'A']++;

        for (int i = 0; i < l; i++) {
            if (i == l-1) {
                for (int j = 0; j < 26; j++)
                    if (freq[j] == 1)
                        sol += (char) (j + 'A');
                continue;
            }
            long long num, den, sum, newl;
            for (int j = 0; j < 26; j++) {
                num = sum = newl = 0;
                den = 1;
                if (freq[j] > 0) {
                    freq[j]--;
                    for (int k = 0; k < 26; k++) {
                        if (freq[k] > 0) {
                            num += freq[k];
                            den *= fat[freq[k]];
                        }
                    }
                    num = fat[num];
                    pos[j] = num / den;
                    freq[j]++;
                }
            }
            while (sum < k) {
                sum += pos[newl];
                newl++;
            }
            newl--;
            sol += (char) (newl + 'A');
            k -= sum - pos[newl];
            freq[newl]--;
            pos[newl] = 0;
        }

        cout << sol << "\n";
    }
    return 0;
}
