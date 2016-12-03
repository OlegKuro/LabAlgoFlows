#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
 
using namespace std;
 
#define N 300
#define INF 1000000010
 
struct edge {
    int to, c, from;
    edge() {}
    edge(int h, int u, int i) {
        to = h;
        c = u;
        from = i;
    }
};
 
queue<int> q;
int n, m;
vector<edge> g[N];
int level[N];
int p[N];
int s, t;
vector<edge> verticles;
 
bool bfs(int s) {
    for (int i = 0; i < N; i++) level[i] = INF;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < (int)g[v].size(); i++) {
            if (g[v][i].from == g[v][i].c) continue;
            int to = g[v][i].to;
            if (level[to] > level[v] + 1) {
                level[to] = level[v] + 1;
                q.push(to);
            }
        }
    }
    return level[t] != INF;
}
 
int dfs(int v, int flow) {
    if (flow == 0) return 0;
    if (v == t) return flow;
    for (int i = p[v]; i < (int)g[v].size(); i++) {
        int to = g[v][i].to;
        if (level[to] != level[v] + 1) continue;
        int n_flow = dfs(to, min(flow, g[v][i].c - g[v][i].from));
        if (n_flow != 0) {
            g[v][i].from += n_flow;
            for (int j = 0; j < (int)g[to].size(); j++) if (g[to][j].to == v) {
                g[to][j].from -= n_flow;
                break;
            }
            return n_flow;
        }
        p[v]++;
    }
    return 0;
 
}
 
void init() {
    for (int i = 0; i < n; i++) {
        p[i] = 0;
    }
}
 
int dinic() {
    int res = 0;
    while (bfs(s)) {
        init();
        int tmp = dfs(s, INF);
        while (tmp > 0) {
            res += tmp;
            tmp = dfs(s, INF);
        }
    }
    return res;
}
 
int main() {
    freopen("circulation.in", "r", stdin);
    freopen("circulation.out", "w", stdout);
    cin.sync_with_stdio(0);
    cout.sync_with_stdio(0);
    cin >> n >> m;
    s = n;
    t = n + 1;
    n += 2;
    for (int i = 0; i < m; i++) {
        int a, h, l, c;
        cin >> a >> h >> l >> c;
        a--;
        h--;
        g[s].push_back(edge(h, l, 0));
        g[h].push_back(edge(s, 0, 0));
 
        g[a].push_back(edge(h, c - l, 0));
        verticles.push_back(edge(a, h, l));
        g[h].push_back(edge(a, 0, 0));
 
        g[a].push_back(edge(t, l, 0));
        g[t].push_back(edge(a, 0, 0));
    }
    int sum = 0;
    for (int i = 0; i < (int)g[s].size(); i++) 
        sum += g[s][i].c;
    int flow = dinic();
    if (flow < sum) 
        cout << "NO" << endl;
    else {
        cout << "YES" << endl;
        for (int i = 0; i < m; i++) {
            int in = verticles[i].to;
            int to = verticles[i].c;
            for (int j = 0; j < (int)g[in].size(); j++) {
                if (g[in][j].to == to) cout << g[in][j].from + verticles[i].from << endl;
            }
        }
    }
 
    return 0;
}