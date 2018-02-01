#include <stdio.h>
#include <algorithm>
#include <vector>
#include <limits.h>
using namespace std;

#define range(i, n) for(int i=0; i<n; ++i)

struct Icon {
	int x, y;
	bool remove;
};

int main()
{
	int r, c, n, m;
	scanf("%d %d %d %d", &r, &c, &n, &m);

	vector<Icon> icons;

	range(i, n) {
		int x, y;
		scanf("%d %d", &x, &y);
		icons.push_back({x, y, true});
	}

	range(i, m) {
		int x, y;
		scanf("%d %d", &x, &y);
		icons.push_back({x, y, false});
	}

	int answer = INT_MAX;

	for(Icon A : icons) for(Icon B : icons) {

		if(A.x < 0 or r <= A.x or A.y < 0 or c <= A.y) continue;
		if(B.x < 0 or r <= B.x or B.y < 0 or c <= B.y) continue;

		if(A.x <= B.x and A.y <= B.y) {
            if ((B.x - A.x + 1) * (B.y - A.y + 1) < n) continue;

			int partial = 0;

			for(Icon C : icons) {
				if(A.x <= C.x and C.x <= B.x and A.y <= C.y and C.y <= B.y) {
					if(C.remove == false) partial += 1;
				} else if(C.remove == true) partial += 1;
			}

			answer = min(partial, answer);
		}
		if(A.x <= B.x and A.y >= B.y) {
            if ((B.x - A.x + 1) * (A.y - B.y + 1) < n) continue;

			int partial = 0;

			for(Icon C : icons) {
				if(A.x <= C.x and C.x <= B.x and B.y <= C.y and C.y <= A.y) {
					if(C.remove == false) partial += 1;
				} else if(C.remove == true) partial += 1;
			}

			answer = min(partial, answer);
		}
	}

	printf("%d\n", n == 0? 0 : answer);
	return 0;
}
