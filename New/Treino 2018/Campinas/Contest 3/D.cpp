#include <bits/stdc++.h>

using namespace std;

int n;
long long val;
string op, code;

map < string, long long > vals;
map < string, int > id;
string cd[100100];

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

typedef tree<
long long,
int,
greater < long long >,
rb_tree_tag,
tree_order_statistics_node_update> map_t;

map_t lista;

int main() {
    scanf("%d", &n);

    int lst = 0;
    for (int i = 0; i < n; i++) {
        cin >> op;
        if (op[0] == 'I') {
            cin >> code;
            if (vals.count(code)) {
                cout << "EXISTS " << id[code] << " " << vals[code] << '\n';
            }
            else {
                vals[code] = 0;
                id[code] = lst;
                lista.insert(make_pair(100001 - lst, lst));
                cd[lst++] = code;

                cout << "CREATED " << id[code] << " 0" << '\n';
            }
        }
        else if (op[0] == 'D') {
            cin >> code;
            if (vals.count(code)) {
                cout << "OK " << id[code] << " " << vals[code] << '\n';
                lista.erase(vals[code] * 100002 + (100001 - id[code]));
                vals.erase(code);
            }
            else {
                cout << "BAD REQUEST" << '\n';
            }
        }
        else if (op[0] == 'R') {
            cin >> code >> val;
            if (vals.count(code)) {
                lista.erase(vals[code] * 100002 + (100001 - id[code]));
                vals[code] += val;
                lista.insert(make_pair(vals[code] * 100002 + (100001 - id[code]), id[code]));

                cout << "OK " << id[code] << " " << vals[code] << '\n';
            }
            else {
                cout << "BAD REQUEST" << '\n';
            }
        }
        else {
            scanf("%lld", &val);

            if (!vals.empty()) {
                val = min((long long)vals.size()-1, val);
                int ans = lista.find_by_order(val)->second;
                cout << "OK " << cd[ans] << " " << ans << " " << vals[cd[ans]] << '\n';
            }
            else {
                cout << "EMPTY" << '\n';
            }
        }
    }

    return 0;
}

/*
17
ISSUE aaa
FIND 10
ISSUE bbb
ISSUE ccc
RELIABILITY aaa 10
RELIABILITY bbb 30
RELIABILITY ccc 20
RELIABILITY xxx 20
FIND 1
FIND 2
FIND 0
ISSUE eee
ISSUE fff
FIND 3
FIND 111
DELETE bbb
FIND 0
*/
