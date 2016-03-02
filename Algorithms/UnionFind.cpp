#include <stdio.h>
#include <algorithm>

using namespace std;

#define N 110000

struct subset {
    int parent;
    int _rank;
} subsets[N];

int _find(struct subset subsets[], int i) {
    // find root and make root as parent of i (path compression)
    if (subsets[i].parent != i)
        subsets[i].parent = _find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

// A function that does union of two sets of x and y
void Union(struct subset subsets[], int x, int y) {
    int xroot = _find(subsets, x);
    int yroot = _find(subsets, y);

    // Attach smaller rank tree under root of high rank tree
    // (Union by Rank)
    if (subsets[xroot]._rank < subsets[yroot]._rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot]._rank > subsets[yroot]._rank)
        subsets[yroot].parent = xroot;

    // If ranks are same, then make one as root and increment
    // its rank by one
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot]._rank++;
    }
}
