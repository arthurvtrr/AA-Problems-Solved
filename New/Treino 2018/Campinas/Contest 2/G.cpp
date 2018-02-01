#include <bits/stdc++.h>

#define INF 4000000000000000000LL
#define ll long long
#define EPS 1e-9

using namespace std;
typedef long double T;

int cmp(T x, T y = 0) {
	return (x <= y + EPS) ? (x + EPS < y) ? -1 : 0 : 1;
}

struct point {
    T x, y;
    int idx;

    point(T x = 0, T y = 0, int idx = -1): x(x), y(y), idx(idx) {}

    point operator + (point b) { return point(x + b.x, y + b.y); }
    point operator - (point b) { return point(x - b.x, y - b.y); }
    bool operator < (const point b) const { return pair<T, T>(x, y) < pair<T, T>(b.x, b.y); }
};

struct point1 {
    ll x, y;
    point1(ll x = 0, ll y = 0): x(x), y(y) {}
};

point mid_point(point a, point b) {
    return point((a.x + b.x) / 2, (a.y + b.y) / 2);
}

inline T distPoints(point a) {
    return sqrt(a.x * a.x + a.y * a.y);
}

inline T escalar(point a, point b) {
    return a.x * b.x + a.y * b.y;
}

inline T vetorial(point a, point b) {
    return a.x * b.y - a.y * b.x;
}

int ccw(point p, point q, point o) {
	return cmp(vetorial(p - o, q - o));
}

T angle(point p, point q, point o) {
	point u = p - q, v = o - q;
	return atan2(vetorial(u, v), escalar(u, v));
}

ll polygon_area(vector <point1> &points){
    if (points.size() < 3) return 0;

    ll area = 0;
    for (int i = 0; i < (int)points.size(); i++)
        area += points[i].x * points[(i+1)%points.size()].y - points[(i+1)%points.size()].x * points[i].y;

    return abs(area);
}

point pivot;
bool polar_cmp(point a , point b) {
    T cross = vetorial(a - pivot, b - pivot);
    return cmp(cross) == 1 || (cmp(cross) == 0 && cmp(distPoints(pivot - a), distPoints(pivot - b)) == -1);
}

vector<point> convex_hull(vector<point> p) {
    if(p.size() <= 2) return p;

    int pi = 0;
    for(int i = 1; i < p.size(); i++)
        if(p[i] < p[pi]) pi = i;

    swap(p[0], p[pi]); pivot = p[0];
    sort(p.begin()+1, p.end(), polar_cmp);

    vector<point> s;
    s.push_back(p.back()); s.push_back(p[0]); s.push_back(p[1]);

    for(int i = 2; i < p.size();) {
        int j = s.size()-1;
        if(s.size() == 2 || ccw(s[j], p[i], s[j-1]) == 1) s.push_back(p[i++]);
        else s.pop_back();
    } s.pop_back();
    return s;
}

T perimeter(vector<point> p) {
    if(p.size() < 2) return 0;

    T per = distPoints(p[0] - p.back());
    for(int i = 1; i < p.size(); i++) {
        per += distPoints(p[i] - p[i-1]);
    }
    return per;
}

int n, x, y;
vector<point> p, ch1;
vector < point1 > in, ch;

ll dp[5050][5], cost[5050][5050];

void solve(int ini, int fim, int mini, int maxi, int lvl) {
    if (ini > fim) return;

    int mid = (ini + fim) / 2;

    int ind = mini;
    for (int i = mini; i < min(maxi+1, mid); i++) {
        if (dp[mid][lvl] > dp[i][lvl-1] + cost[i][mid]) {
            ind = i;
            dp[mid][lvl] = dp[i][lvl-1] + cost[i][mid];
        }
    }

    solve(ini, mid-1, mini, ind, lvl);
    solve(mid+1, fim, ind, maxi, lvl);
}

ll areaTriangle(const point1 &a, const point1 &b, const point1 &c) {
    return (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
}

int main() {
    scanf("%d", &n);
    for(int i = 0 ; i < n; i++) {
        scanf("%d %d", &x, &y);
        p.push_back(point(x, y, i + 1));
        in.push_back(point1(x, y));
    }
    ch1 = convex_hull(p);
    for (int i = 0; i < ch1.size(); i++)
        ch.push_back(in[ch1[i].idx-1]);

    for (int i = 0; i < ch.size(); i++) {
        ll c = 0;

        for (int j = i+2; j < i+ch.size(); j++) {
            c += abs(areaTriangle(ch[i], ch[(j-1)%ch.size()], ch[j%ch.size()]));
            cost[i][j%ch.size()] = c;
        }
    }

    ll ans = 0;

    for (int i = 0; i < ch.size(); i++) {
        ll aux = polygon_area(ch);

        for (int j = 0; j < ch.size(); j++)
            for (int k = 0; k < 5; k++)
                dp[j][k] = INF;

        for (int j = 0; j < i; j++)
            dp[j][0] = cost[i][j];

        for (int j = 1; j < 4; j++)
            solve(0, (int)ch.size()-1, 0, (int)ch.size()-1, j);

        aux -= dp[i][3];
        ans = max(ans, aux);
    }

    long double p = ans; p /= 2.0;
    printf("%.1Lf\n", p);

    return 0;
}
