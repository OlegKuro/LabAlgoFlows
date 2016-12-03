#include <queue>
#include <vector>
#include <fstream>
#define NMAX  1006
using namespace std;
 
ifstream fin("maxflow.in");
ofstream fout("maxflow.out");
const int INF = 0x3f3f3f3f;
 
int n, m;
int rez[NMAX][NMAX];
vector<int> g[NMAX];
int prev1[NMAX];
int totalFlow;
 
void read() {
 
    fin >> n >> m;
 
    for (int i = 1; i <= m; ++i) {
        int x, y, c;
        fin >> x >> y >> c;
        g[x].push_back(y);
        g[y].push_back(x);
        rez[x][y] += c;
    }
}
 
bool bfs(int s, int d) {
 
    int viz[NMAX];
    memset(viz, 0, sizeof(viz));
 
    queue<int> q;
    viz[s] = 1;
    q.push(s);
    prev1[s] = s;
 
    while (q.empty() == false) {
 
        int node = q.front();
 
        for (int x : g[node])
            if (viz[x] == 0 && rez[node][x] > 0) {
 
                viz[x] = 1;
 
                if (x == d) continue;
 
                q.push(x);
                prev1[x] = node;
            }
 
        q.pop();
    }
 
    return viz[d];
}
 
void solve() {
 
    int s = 1;
    int d = n;
 
    while (bfs(s, d)) {
 
        for (int node : g[d]) {
 
            int maxFlow = INF;
            prev1[d] = node;
 
            for (int i = d; i != prev1[i]; i = prev1[i])
                maxFlow = min(maxFlow, rez[prev1[i]][i]);
 
            totalFlow += maxFlow;
 
            for (int i = d; i != prev1[i]; i = prev1[i]) {
 
                rez[prev1[i]][i] -= maxFlow;
                rez[i][prev1[i]] += maxFlow;
            }
        }
    }
 
    fout << totalFlow << '\n';
 
}
 
int main() {
 
    read(); solve();
    return 0;
}