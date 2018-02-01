#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <map>
#include <set>
#include <vector>

using namespace std;

long long gcd(long long a, long long b) { return b == 0? a : gcd(b, a % b); }

struct Fraction {
    long long numerator, denominator;

    Fraction() {
        numerator = 0;
        denominator = 1;
    }

    Fraction(long long n, long long d) {
        if (n == 0) {
            numerator = 0;
            denominator = 1;
        }
        else {
            int sign = 1;
            if (n < 0) {
                sign *= -1;
                n *= -1;
            }
            if (d < 0) {
                sign *= -1;
                d *= -1;
            }

            long long tmp = gcd(n, d);
            numerator = n / tmp * sign;
            denominator = d / tmp;
        }
    }

    bool operator == (Fraction other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }

    bool operator < (Fraction other) const {
        return numerator*other.denominator < other.numerator*denominator;
    }

    bool operator > (Fraction other) const {
        return numerator*other.denominator > other.numerator*denominator;
    }
};

Fraction simplify(Fraction f) {
    long long aux = gcd(f.numerator, f.denominator);
    f.numerator /= aux;
    f.denominator /= aux;
    return f;
}

Fraction operator+(const Fraction& lhs, const Fraction& rhs) {
    Fraction tmp(lhs.numerator*rhs.denominator
                +rhs.numerator*lhs.denominator,
                lhs.denominator*rhs.denominator);
    return simplify(tmp);
}

Fraction operator+=(Fraction& lhs, const Fraction& rhs) {
    Fraction tmp(lhs.numerator*rhs.denominator
                +rhs.numerator*lhs.denominator,
                lhs.denominator*rhs.denominator);
    lhs = tmp;
    return simplify(lhs);
}

Fraction operator-(const Fraction& lhs, const Fraction& rhs) {
    Fraction tmp(lhs.numerator*rhs.denominator
                -rhs.numerator*lhs.denominator,
                lhs.denominator*rhs.denominator);
    return simplify(tmp);
}

Fraction operator-=(Fraction& lhs, const Fraction& rhs) {
    Fraction tmp(lhs.numerator*rhs.denominator
                -rhs.numerator*lhs.denominator,
                lhs.denominator*rhs.denominator);
    lhs = tmp;
    return simplify(lhs);
}

Fraction operator*(const Fraction& lhs, const Fraction& rhs) {
    Fraction tmp(lhs.numerator*rhs.numerator,
               lhs.denominator*rhs.denominator);
    return simplify(tmp);
}

Fraction operator*=(Fraction& lhs, const Fraction& rhs) {
    Fraction tmp(lhs.numerator*rhs.numerator,
               lhs.denominator*rhs.denominator);
    lhs = tmp;
    return simplify(lhs);
}

Fraction operator*(int lhs, const Fraction& rhs) {
    Fraction tmp(lhs*rhs.numerator,rhs.denominator);
    return simplify(tmp);
}

Fraction operator*(const Fraction& rhs, int lhs) {
    Fraction tmp(lhs*rhs.numerator,rhs.denominator);
    return simplify(tmp);
}

Fraction operator/(const Fraction& lhs, const Fraction& rhs) {
    Fraction tmp(lhs.numerator*rhs.denominator,
                 lhs.denominator*rhs.numerator);
    return simplify(tmp);
}

struct point {
    Fraction x, y;
    point() {
        x = y = Fraction();
    }
    point(int x_, int y_) {
        x = Fraction(x_, 1);
        y = Fraction(y_, 1);
    }

    bool operator < (point other) const {
        if (x == other.x)
            return y < other.y;
        return x < other.x;
    }
};

struct line { Fraction a, b, c; };

void pointsToLine(point p1, point p2, line &l) {
    if (p1.x == p2.x) {
        l.a = Fraction(1, 1); l.b = Fraction(); l.c = p1.x * -1;
    } else {
        l.a = (p1.y - p2.y) / (p1.x - p2.x) * -1;
        l.b = Fraction(1, 1);
        l.c = ((l.a * p1.x) - p1.y) * -1;
    }
}

bool areParallel(line l1, line l2) {
    return l1.a == l2.a && l1.b == l2.b;
}

bool areSame(line l1, line l2) {
    return areParallel(l1, l2) && l1.c == l2.c;
}

bool areIntersect(line l1, line l2, point &p) {
    if (areParallel(l1, l2)) return false;

    p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);

    if (l1.b > Fraction()) p.y = (l1.a * p.x + l1.c) * -1;
    else p.y = (l2.a * p.x + l2.c) * -1;
    return true;
}

int n, x, y;
point points[1010];
map < point, vector < int > > notVis;
set < int > ways;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);
        points[i] = point(x, y);
    }

    line axis;
    pointsToLine(point(0, 0), point(10, 0), axis);

    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++) {
            line aux;
            pointsToLine(points[i], points[j], aux);
            point p;

            if (areIntersect(axis, aux, p)) {
                if (points[i].y < points[j].y) notVis[p].push_back(j);
                else notVis[p].push_back(i);
            }
        }

    ways.insert(n);

    for (map < point, vector < int > >::iterator it = notVis.begin(); it != notVis.end(); it++) {
        sort((it->second).begin(), (it->second).end());
        unique((it->second).begin(), (it->second).end());
        ways.insert(n - (it->second).size());
    }

    printf("%d\n", ways.size());
    return 0;
}
