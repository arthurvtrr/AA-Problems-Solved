#include <bits/stdc++.h>

using namespace std;

#define PI acos(-1)
#define EPS 1e-9

int x, y, z, pow6[10];
vector < int > points[10][6], nxt;

struct point {
    double x, y, z;
    point(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
};

double dist(point a, point b) {
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z));
}

double dot(point a, point b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

double norm(point v) { return v.x * v.x + v.y * v.y + v.z * v.z; }

double angle(point a, point o, point b) {
    point oa = point(a.x - o.x, a.y - o.y, a.z - o.z), ob = point(b.x - o.x, b.y - o.y, b.z - o.z);
    return acos(dot(oa, ob) / sqrt(norm(oa) * norm(ob))) * 180.0 / PI;
}

point to_use[10];

int main() {
    for (int i = 0; i < 8; i++) {
        scanf("%d %d %d", &x, &y, &z);
        vector < int > aux = {x, y, z};
        sort(aux.begin(), aux.end());

        int ind = 0;
        do {
            points[i][ind++] = aux;
        } while (next_permutation(aux.begin(), aux.end()));
    }

    pow6[0] = 1;
    for (int i = 1; i < 10; i++)
        pow6[i] = 6 * pow6[i-1];

    int cont = 0;
    for (int i = 0; i < pow6[8]; i++) {
        bool valid = true;

        for (int j = 0; j < 8; j++) {
            vector < int > &aux = points[j][(i % pow6[j+1]) / pow6[j]];
            if (aux.empty()) { valid = false; break; }

            to_use[j] = point(aux[0], aux[1], aux[2]);
        }

        if (!valid) continue;

        double d = 1000000000.0;
        for (int j = 0; j < 8; j++)
            for (int k = j+1; k < 8; k++)
                d = min(d, dist(to_use[j], to_use[k]));

        if (abs(d) < EPS) continue;

        bool found = true;

        for (int j = 0; j < 8; j++) {
            nxt.clear();
            for (int k = 0; k < 8; k++)
                if (k != j && abs(dist(to_use[j], to_use[k]) - d) < EPS)
                    nxt.push_back(k);

            if (nxt.size() != 3) { found = false; break; }

            for (int k = 0; k < 3; k++)
                for (int l = k+1; l < 3; l++)
                    if (abs(angle(to_use[nxt[k]], to_use[j], to_use[nxt[l]]) - 90.0) > EPS)
                        found = false;
        }

        if (found) {
            printf("YES\n");
            for (int j = 0; j < 8; j++)
                printf("%.0f %.0f %.0f\n", to_use[j].x, to_use[j].y, to_use[j].z);
            exit(0);
        }
    }

    printf("NO\n");

    return 0;
}
