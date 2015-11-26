#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define N 1001

char str[N];
int len, gap, pos[N];

bool comp(int i, int j) {
	if(pos[i] != pos[j]) return pos[i] < pos[j];
	i += gap, j += gap;
	return (i < len && j < len) ? pos[i] < pos[j] : i > j;
}

void run() {
	scanf("%s", str);
	len = strlen(str);

	int sa[len], lcp[len], tmp[len];

	for (int i = 0; i < len; i++) {
		sa[i] = i, pos[i] = str[i];
		lcp[i] = tmp[i] = 0;
	}

	for (gap = 1; tmp[len-1] != len-1; gap <<= 1) {
		sort(sa, sa+len, comp);
		for (int i = 0; i < len-1; i++)
            tmp[i+1] = tmp[i] + comp(sa[i], sa[i+1]);
		for (int i = 0; i < len; i++)
            pos[sa[i]] = tmp[i];
	}

	for (int i = 0; i < len; i++)
        pos[sa[i]] = i;

	for (int i = 0, k = 0; i < len; i++)
        if (pos[i] != 0) {
            int j = sa[pos[i]-1];
            while (str[i+k] == str[j+k]) k++;
            lcp[pos[i]] = k, k = max(0, k-1);
        }
}
