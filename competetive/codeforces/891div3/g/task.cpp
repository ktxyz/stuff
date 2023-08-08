#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#define M 998244353
using namespace std;

int find(int x, vector<int>& rep) {
    if (rep[x] == x) return x;
    rep[x] = find(rep[x], rep);
    return rep[x];
}

void union_sets(int x, int y, vector<int>& rep, vector<int>& sz) {
    x = find(x, rep);
    y = find(y, rep);
    if (x == y) return;
    if (sz[x] < sz[y]) swap(x, y);
    rep[y] = x;
    sz[x] += sz[y];
}

long long pow_fast(long long a, long long b, long long mod) {
    if (b == 0) return 1;
    if (b == 1) return a % mod;
    long long v = pow_fast(a, b / 2, mod) % mod;
    v = (v * v) % mod;
    if (b % 2 == 1) v = (v * a) % mod;
    return v;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t, n, S;
    cin >> t;
    while (t--) {
        cin >> n >> S;

        vector<int> rep(n + 1);
        vector<int> sz(n + 1, 1);
        for (int i = 0; i <= n; i++) rep[i] = i;

        vector<tuple<int, int, int>> edges;
        for (int i = 0; i < n - 1; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            edges.push_back(make_tuple(w, u, v));
        }
        sort(edges.begin(), edges.end());

        long long ans = 1;
        for (const auto& e : edges) {
            long long szu = sz[find(get<1>(e), rep)];
            long long szv = sz[find(get<2>(e), rep)];
            ans = (ans * pow_fast(S - get<0>(e) + 1, szu * szv - 1, M)) % M;
            union_sets(get<1>(e), get<2>(e), rep, sz);
        }

        cout << ans << "\n";
    }
    return 0;
}
