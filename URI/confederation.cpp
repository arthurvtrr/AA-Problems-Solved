#include <stdio.h>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

struct plane {
	int A;
	int B;
	int C;
	int D;
} planes[550];

struct planet {
	int x;
	int y;
	int z;
} planets[11000];

int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) != EOF) {
		map < string, int > regions;
		for (int i = 0; i < n; i++)
			scanf("%d %d %d %d", &planes[i].A, &planes[i].B, &planes[i].C, &planes[i].D);
		for (int i = 0; i < m; i++)
			scanf("%d %d %d", &planets[i].x, &planets[i].y, &planets[i].z);

		int sol = 0;
		for (int i = 0; i < m; i++) {
            string s = "";
			for (int j = 0; j < n; j++)
				if (planes[j].A * planets[i].x + planes[j].B * planets[i].y + planes[j].C * planets[i].z >= planes[j].D)
					s += '1';
                else
                    s += '0';
			regions[s]++;
			if (regions[s] > sol) sol = regions[s];
		}

		printf("%d\n", sol);
	}

	return 0;
}
