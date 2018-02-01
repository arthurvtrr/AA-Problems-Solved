#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <stack>

using namespace std;

struct point {
     long long x,y;
} C[100010];


long long areaTriangle(const point &a, const point &b, const point &c) {
    return (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
}

//Check if point is inside of a convex polygon in O(log(n))
bool inConvexPoly(const vector < point > &convPoly, point p) {
    long long start = 1, last = (int) convPoly.size() - 1;

    while (last - start > 1) {
        long long mid = (start + last) / 2;
        if (areaTriangle(convPoly[0], convPoly[mid], p) < 0) last = mid;
        else start = mid;
    }

    long long r0 = abs(areaTriangle(convPoly[0], convPoly[start], convPoly[last]));

    long long r1 = abs(areaTriangle(convPoly[0], convPoly[start], p));
    long long r2 = abs(areaTriangle(convPoly[0], convPoly[last], p));
    long long r3 = abs(areaTriangle(convPoly[start], convPoly[last], p));

    // if you need strictly inside
    long long r4 = areaTriangle(convPoly[0], convPoly[1], p);
    long long r5 = areaTriangle(convPoly[0], convPoly[convPoly.size() - 1], p);

    // if you need strictly inside, add '&& r3 != 0 && r4 != 0 && r5 != 0' to return
    return r0 == (r1 + r2 + r3);
}

int main() {

    return 0;
}
