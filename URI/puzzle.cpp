#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

struct pos {
    int ind;
    int t;
    int num;
} posis[220];

bool comp(pos x, pos y) {
    return x.num < y.num;
}

int main() {
    int l, c, sum_l[110], sum_c[110];
    string mat[110][110];
    while (scanf("%d %d", &l, &c) != EOF) {
        for (int i = 0; i < l; i++) {
            for (int j = 0; j < c; j++)
                cin >> mat[i][j];
            scanf("%d", &sum_l[i]);
        }

        for (int i = 0; i < c; i++)
            scanf("%d", &sum_c[i]);

        map < string, int > dif;
        for (int i = 0; i < l; i++) {
            for (int j = 0; j < c; j++)
                dif[mat[i][j]]++;
            posis[i].ind = i;
            posis[i].t = 1;
            posis[i].num = dif.size();
            dif.clear();
        }

        for (int i = 0; i < c; i++) {
            for (int j = 0; j < l; j++)
                dif[mat[j][i]]++;
            posis[i+l].ind = i;
            posis[i+l].t = 2;
            posis[i+l].num = dif.size();
            dif.clear();
        }

        map < string, int > val;

        sort(posis, posis+l+c, comp);

        while (1) {
            int f = -1;
            for (int i = 0; i < l+c; i++)
                if (posis[i].num > 0) {
                    f = i;
                    break;
                }
            if (f == -1) break;

            int q = 0, total = 0;
            string x;
            if (posis[f].t == 1) {
                for (int i = 0; i < c; i++) {
                    if (!val.count(mat[posis[f].ind][i])) q++;
                    else total += val[mat[posis[f].ind][i]];
                }
                for (int i = 0; i < c; i++)
                    if (!val.count(mat[posis[f].ind][i])) {
                        val[mat[posis[f].ind][i]] = (sum_l[posis[f].ind] - total) / q;
                        x = mat[posis[f].ind][i];
                        break;
                    }
            }
            else {
                for (int i = 0; i < l; i++) {
                    if (!val.count(mat[i][posis[f].ind])) q++;
                    else total += val[mat[i][posis[f].ind]];
                }
                for (int i = 0; i < l; i++)
                    if (!val.count(mat[i][posis[f].ind])) {
                        val[mat[i][posis[f].ind]] = (sum_c[posis[f].ind] - total) / q;
                        x = mat[i][posis[f].ind];
                        break;
                    }
            }

            bool cont_l[110], cont_c[110];
            for (int i = 0; i < 110; i++) {
                cont_l[i] = false;
                cont_c[i] = false;
            }

            for (int i = 0; i < l; i++)
                for (int j = 0; j < c; j++)
                    if (mat[i][j] == x) {
                        cont_l[i] = true;
                        cont_c[j] = true;
                    }

            for (int i = 0; i < l+c; i++) {
                if (posis[i].t == 1 && cont_l[posis[i].ind]) posis[i].num--;
                if (posis[i].t == 2 && cont_c[posis[i].ind]) posis[i].num--;
            }

            sort(posis, posis+l+c, comp);
        }

        for (map < string, int >::iterator it = val.begin(); it != val.end(); it++)
            cout << it->first << " " << it->second << "\n";
    }
    return 0;
}
