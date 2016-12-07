#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
 
#define N 20
#define maxstate 1050000
int n;
int m;
int w[N];
bool state[maxstate];
 
void state_set(int x) {
    state[x] = true;
    if (x == ((1 << n) - 1))
        return;
    for (int i = 0; i < n; i++) {
        if ((x & (1 << i)) == 0 && !state[x + (1 << i)]) {
            state_set(x + (1 << i));
        }
    }
}
 
 
int main() {
    freopen("cycles.in", "r", stdin);
    freopen("cycles.out", "w", stdout);
    cin.sync_with_stdio(0);
    cout.sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    for (int mask = 0; mask < (1 << n); mask++) {
        state[mask] = false;
    }
    for (int i = 0; i < m; i++) {
        int c;
        cin >> c;
        int temp = 0;
        for (int j = 0; j < c; j++) {
            int k;
            cin >> k; k--;
            temp += (1 << k);
        }
        state_set(temp);
    }
    int ans = 0;
    int msize = 0;
    for (int mask = 0; mask < (1 << n); mask++) 
        if (!state[mask]) {
            int c = 0;
            int sum = 0;
            for (int k = 0; k < n; k++) if ((mask & (1 << k)) > 0) {
                sum += w[k];
                c++;
            }
        if (c > msize) {
            ans = 0;
            msize = c;
        }
        ans = max(ans, sum);
    }
    cout << ans;
    return 0;
}