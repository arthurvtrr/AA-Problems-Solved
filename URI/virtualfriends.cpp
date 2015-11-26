#include <stdio.h>
#include <iostream>
#include <string>
#include <map>

using namespace std;

map < string, int > friends;
int t, f, people[210000], total[210000];
string x, y;


int find(int n) {
    if (people[n] == n)
        return n;
    return people[n] = find(people[n]);
}

int main() {
    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        scanf("%d", &f);
        friends.clear();
        int id = -1;

        for (int j = 0; j < f; j++) {
            cin >> x >> y;

            if (friends.find(x) == friends.end()) {
                friends[x] = ++id;
                people[id] = id;
                total[id] = 1;
            }
            if (friends.find(y) == friends.end()) {
                friends[y] = ++id;
                people[id] = id;
                total[id] = 1;
            }

            int a = find(friends[x]);
            int b = find(friends[y]);

            if (a != b) {
                people[a] = b;
                total[b] += total[a];
            }

            printf("%d\n", total[b]);
        }
    }

    return 0;
}
