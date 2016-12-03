#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#define ll long long
 
using namespace std;
 
#define N 111
#define INF 10000000000010
 
struct edge {
    int to;
    ll c, from, cost;
    edge() {}
    edge(int b, ll d, ll e, ll j) {
        to = b;
        c = d;
        from = e;
        cost = j;
    }
};
 
int n, m;
vector<edge> g[N];
int s, t;
ll d[N];
ll fun[N];
bool used[N];
pair<int, int> p[N];
priority_queue< pair<int, ll> > q; //for dijkstra
 
void ford(int st) {
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++)
            for (size_t j = 0; j < g[k].size(); j++) {
                if (g[k][j].c == g[k][j].from) continue;
                int in = k, to = g[k][j].to;
                ll w = g[k][j].cost;
                if (fun[in] < INF) {
                    if (fun[to] > fun[in] + w) {
                        fun[to] = max(-INF, fun[in] + w);
                    }
                }
            }
    }
}
 
 
void dijkstra(int st) {
    d[st] = 0;
    q.push(make_pair(st, 0));
    while (!q.empty()) {
        int v = q.top().first;
        q.pop();
        for (size_t i = 0; i < g[v].size(); i++) {
            if (g[v][i].c == g[v][i].from) continue;
            int to = g[v][i].to;
            ll w = g[v][i].cost;
            if (d[to] > d[v] + w + fun[v] - fun[to]) {
                d[to] = d[v] + w + fun[v] - fun[to];
                p[to] = make_pair(v, i);
                q.push(make_pair(to, d[to]));
            }
        }
    }
}
 
ll mincostmaxflow() {
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        used[i] = false;
        fun[i] = INF;
    }
    fun[s] = 0;
    ford(s);
    while (true) {
        for (int i = 0; i < n; i++) {
            d[i] = INF;
            p[i] = make_pair(-1, -1);
        }
        dijkstra(s);
        for (int i = 0; i < n; i++) {
            if (d[i] < INF)
                fun[i] += d[i];
        }
        if (d[t] == INF) break;
        int v = t;
        ll n_flow = INF;
        while (p[v].first != -1) {
            int prev = p[v].first;
            n_flow = min(n_flow, g[prev][p[v].second].c - g[prev][p[v].second].from);
            v = prev;
        }
        v = t;
        if (n_flow != 0) {
            while (p[v].first != -1) {
                int prev = p[v].first;
                g[prev][p[v].second].from += n_flow;
                sum += n_flow * g[prev][p[v].second].cost;
                for (size_t i = 0; i < g[v].size(); i++) {
                    if (g[v][i].to == prev && (g[v][i].from == -(g[prev][p[v].second].from - n_flow)) && (g[v][i].cost == -g[prev][p[v].second].cost)) {
                        g[v][i].from -= n_flow;
                    }
                }
                v = prev;
            }
        }
        else break;
    }
    return sum;
}
 
int main() {
    freopen("mincost.in", "r", stdin);
    freopen("mincost.out", "w", stdout);
    cin.sync_with_stdio(0);
    cout.sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a;
        ll b, c, d;
        cin >> a >> b >> c >> d;
        a--;
        b--;
        g[a].push_back(edge(b, c, 0, d));
        g[b].push_back(edge(a, 0, 0, -d));
    }
    s = 0;
    t = n - 1;
    cout << mincostmaxflow() << endl;
    system("pause");
    return 0;
}