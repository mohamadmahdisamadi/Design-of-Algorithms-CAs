#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

typedef long long ll;
const ll maxn = 100007;
struct edge { int u; int v; int w; int i; };

int par[maxn];
vector<int> child[maxn];
vector<int> real_child[maxn];
int depth[maxn];
vector<edge> edges;
map<pair<int, int>, edge> vertoedge;
int ans[maxn];
enum { DARYL, ALL, SOME, NONE };

map<int, string> int_answer_to_str = {
    {SOME, "at least one"},
    {ALL, "any"},
    {NONE, "none"}
};

int find(int u) {
    int cur = u;
    while (par[cur] != cur) cur = par[cur];
    return cur;
}

void join_sets(int u, int v, int ru, int rv) {
    if (depth[ru] > depth[rv]) {
        // cout << "put " << rv << " as child of " << ru << endl;
        par[rv] = ru;
        child[ru].push_back(rv);
    } else if (depth[ru] < depth[rv]) {
        // cout << "put " << ru << " as child of " << rv << endl;
        par[ru] = rv;
        child[rv].push_back(ru);
    } else {
        // cout << "put same depth " << rv << " as child of " << ru << endl;
        par[rv] = ru;
        child[ru].push_back(rv);
        depth[ru]++;
    }
    real_child[u].push_back(v);
    real_child[v].push_back(u);
}

bool compare_edges(edge a, edge b) {
    return a.w < b.w;
}

int target, count_similars;
int in_sar, oon_sar;

void dfs(int n, int par) {
    // cout << "entered dfs for " << n << " with par " << par << endl;

    if (par != n) {
        edge e = vertoedge[{par, n}];
        if (e.w == target) {
            // cout << "found same weight in cycle. edge: " << e.u << "--" << e.v << " w:" << e.w << endl;
            count_similars++;
            ans[e.i] = SOME;
        }
    }

    for (auto u : real_child[n]) {
        if (u != par) {
            dfs(u, n);
        }
    }
}

int main() {
    ll n, m; cin >> n >> m;
    for (int i=0; i<m; i++) {
        int u, v, w; cin >> u >> v >> w;
        edge e;
        e.u = u; e.v = v; e.w = w; e.i = i;
        edges.push_back(e);
        vertoedge[{u, v}] = e;
        vertoedge[{v, u}] = e;
    }
    sort(edges.begin(), edges.end(), compare_edges ); 
    // for (int k=0; k<(int)edges.size(); k++) {
       // cout << edges[k].w << "  ";
    // }
    // cout << endl;
    for (int i=1; i<n+1; i++) {
        par[i] = i; depth[i] = 1;
    }

    int cnt = 0;
    int i = 0;
    int maxw = 0;
    for (i; i<(int)edges.size(); i++) {
        edge e = edges[i];
        // cout << "EDGE: " << e.u << " -- " << e.v << "  w: " << e.w << "  i: " << e.i << endl;
        if ((cnt == n-1) and e.w > maxw) break;
        int ru = find(e.u), rv = find(e.v);
        if (ru == rv) {
            target = e.w;
            count_similars = 0;
            // cout << "starting dfs from " << ru << " to find same wights as " << e.u << "--" << e.v << endl;
            dfs(ru, par[ru]);
            // cout << "ending dfs from " << ru << " found similars " << count_similars << endl;
            if (count_similars) {
                ans[e.i] = SOME;
            } else {
                ans[e.i] = NONE;
            }
        } else {
            join_sets(e.u, e.v, ru, rv);
            cnt++;
            maxw = e.w;
        }
    }

    for (int j=0; j<i; j++) {
        if (ans[edges[j].i] == DARYL)
            ans[edges[j].i] = ALL;
    }

    for (i; i<(int)edges.size(); i++) {
        ans[edges[i].i] = NONE;
    }

    for (int i=0; i<m; i++) {
        cout << int_answer_to_str[ans[i]] << endl;
    }

    return 0;
}