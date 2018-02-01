#include <bits/stdc++.h>

using namespace std;

#define ll long long

struct point {
    ll x, y;
    point() { x = y = 0; }
    point(ll x, ll y) : x(x), y(y) {}
    bool operator < (point other) const {
        if (y != other.y) return y < other.y;
        return x < other.x;
    }
};

int n, a, b;
vector < point > pol;

bool comp(point a, point b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

double dist(point a, point b) {
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

void closestPair() {
    point closest[2];

    double minDist = 5000000000LL;

    sort(pol.begin(), pol.end(), comp);
    int lIndex = 0;
    set < point > aux;

    for (point current : pol) {
        while (current.x - pol[lIndex].x >= minDist) {
            aux.erase(pol[lIndex]);
            lIndex++;
        }

        point head = point(current.x, current.y - minDist + 1);
        point tail = point(current.x, current.y + minDist - 1);

        set < point >::iterator it = aux.lower_bound(head);

        while (it != aux.end()) {
            point p = *it;
            if (tail < p) break;

            double distance = dist(current, p);

            if (distance < minDist) {
                minDist = distance;
                closest[0] = current;
                closest[1] = p;
            }
            it++;
        }

        aux.insert(current);
    }

    printf("%lld %lld\n", closest[0].x, closest[0].y);
    printf("%lld %lld\n", closest[1].x, closest[1].y);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &a, &b);
        pol.push_back(point(a, b));
    }
    closestPair();
    return 0;
}
