#include <bits/stdc++.h>

using namespace std;

const int N = 101000;

struct node {
	int next[26];
	int len;
	int sufflink, halfSuff;
	int num;
	int parent;
    int sintCost, halfCost;
};

int len, num, suff;
char s[N];
node tree[N];

vector < int > graph[N];

bool addLetter(int pos) {
	int cur = suff, curlen = 0;
	int let = s[pos] - 'A';

	while (true) {
		curlen = tree[cur].len;
		if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos])
			break;
		cur = tree[cur].sufflink;
	}
	if (tree[cur].next[let]) {
		suff = tree[cur].next[let];
		return false;
	}

	num++;
	suff = num;
	tree[num].len = tree[cur].len + 2;
	tree[num].parent = cur;
	tree[cur].next[let] = num;

	if (tree[num].len == 1) {
		tree[num].sufflink = 2;
		graph[2].push_back(num);
		tree[num].num = 1;
		return true;
	}

	while (true) {
		cur = tree[cur].sufflink;
		curlen = tree[cur].len;
		if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
			tree[num].sufflink = tree[cur].next[let];
			graph[tree[cur].next[let]].push_back(num);
			break;
		}
	}

	tree[num].num = 1 + tree[tree[num].sufflink].num;

	return true;
}

void initTree() {
	num = 2; suff = 2;
	tree[1].len = -1; tree[1].sufflink = 1;
	tree[2].len = 0; tree[2].sufflink = 1;
}

void calcCosts() {
    queue < int > fila;
    for (int i = 0; i < 26; i++) {
        if (tree[1].next[i])
            fila.push(tree[1].next[i]);
        if (tree[2].next[i])
            fila.push(tree[2].next[i]);
    }

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        if (tree[u].len < 3) {
            tree[u].sintCost = tree[u].len;
            tree[u].halfCost = tree[u].len % 2? 1000000 : tree[u].len / 2;
        }
        else {
            if (tree[u].len % 2 == 0) {
                tree[u].halfCost = tree[tree[u].parent].halfCost + 1;
                tree[u].halfCost = min(tree[u].halfCost, tree[tree[u].halfSuff].sintCost + tree[u].len / 2 - tree[tree[u].halfSuff].len);
            }
            else {
                tree[u].halfCost = 1000000;
            }

            tree[u].sintCost = tree[u].halfCost + 1;
            tree[u].sintCost = min(tree[u].sintCost, tree[tree[u].parent].sintCost + 2);
            tree[u].sintCost = min(tree[u].sintCost, tree[tree[u].sufflink].sintCost + tree[u].len - tree[tree[u].sufflink].len);
        }

        for (int i = 0; i < 26; i++)
            if (tree[u].next[i])
                fila.push(tree[u].next[i]);
    }
}

#define pii pair < int, int >

set < pii > pilha;

void dfs(int u) {
    pilha.insert(make_pair(0, 2));

    bool put = false;

    while (pilha.size() > 1) {
        set < pii >::iterator it = pilha.begin();
        it++;

        if ((*it).first > tree[u].len / 2) {
            tree[u].halfSuff = (*pilha.begin()).second;
            put = true;
            break;
        }
        else {
            pilha.erase(pilha.begin());
        }
    }
    if (!put) {
        tree[u].halfSuff = (*pilha.begin()).second;
    }

    pilha.insert(make_pair(tree[u].len, u));

    for (int v : graph[u])
        dfs(v);

    if (pilha.count(make_pair(tree[u].len, u)))
        pilha.erase(make_pair(tree[u].len, u));
}

int t;

int main() {
	scanf("%d", &t);

	while (t--) {
        len = num = suff = 0;
        pilha.clear();
        for (int i = 0; i < N; i++) {
            graph[i].clear();
            tree[i].len = tree[i].num = tree[i].sufflink = 0;
            tree[i].sintCost = tree[i].halfCost = tree[i].parent = tree[i].halfSuff = 0;
            for (int j = 0; j < 26; j++)
                tree[i].next[j] = NULL;
        }

        scanf("%s", s);
        len = strlen(s);

        initTree();

        for (int i = 0; i < len; i++)
            addLetter(i);

        dfs(2);
        tree[1].halfSuff = tree[2].halfSuff = 1;
        calcCosts();

        int ans = len;
        for (int i = 3; i <= num; i++)
            ans = min(ans, tree[i].sintCost + len - tree[i].len);

        printf("%d\n", ans);
    }
	return 0;
}
