#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long ll;
struct edge { int u; int v; int i; }; // u and v are two end-points of the edge. i is the index of the edge
struct adj  { int u; int i; }; // u is the adjacent node. i is the index of the edge that connects two nodes together

const int MAX_WEIGHT = 1e6 + 7;
const int MAX_VER = 1e5 + 7;

vector<edge> edges[MAX_WEIGHT]; // edges[w] shows the set of edges with weight equal to 'w'
vector<adj> adjs[MAX_VER]; // adjacency list
int par[MAX_VER]; // par[u] shows parent of 'u' in DSU
bool visited[MAX_VER]; // used in dfs algorithm
int disc[MAX_VER]; // discovery time in tarjan's algorithm
int low[MAX_VER]; // lowest time in tarjan's algorithm
int ans[MAX_VER]; // answer of each edge

// set of possible answers as integers
enum { NONE, SOME, ALL };
// map from integer form of answers to the desired string form
map<int, string> int_answer_to_str = { {SOME, "at least one"}, {ALL, "any"}, {NONE, "none"} };

// function to recursively find the parent in DSU and update parent of all nodes along its path
int find(int u) {
    if (u == par[u]) {return u; }
    else { par[u] = find(par[u]); return par[u]; }
}

// caller of the root is -1
// keep in mind that Kruskal algorithm adds edges in ascending order based on their weights and avoids cycles at the same time
// we call dfs starting from an end-point of edge 'e' after we've took as much edges with the same weight as 'e' as possible.
void dfs(int n, int caller_id, int time) {
    visited[n] = true; disc[n] = time; low[n] = time;
    for (int j=0; j<adjs[n].size(); j++) {
        int i = adjs[n][j].i; int u = adjs[n][j].u;
        if (!visited[u]) {
            dfs(u, i, time+1);

            /*
                backedges from nodes in sub-tree rooted with 'n' are handled here
                update low[n] if needed
            */
            if (low[u] < low[n]) { low[n] = low[u]; }

            /*
                meaning that no node in sub-tree rooted with u has a backedge
                in other words n is an articulation node in the current MST
            */
            if (low[u] > disc[n]) { ans[i] = ALL; }
        } else if (i != caller_id) {
            /*
                backedges from 'n' are handled here
                update low[n] if needed
            */
            if (low[u] < low[n]) { low[n] = low[u]; }
        }
    }
}

void print_parents(int n, int w) {
    cout << "w: " << w << " par: ";
    for (int i=1; i<=n; i++) {
        cout << i << "(" << par[i] << ")  ";
    }
    cout << endl;
}

void print_adjs(int n) {
    int aaa = 0;
    for (int i=1; i<=n; i++) {
        if (adjs[i].size() > 0) aaa++;
    }

    if (aaa) cout << "printing adjs: ";

    for (int i=1; i<=n; i++) {
        if (adjs[i].size() > 0) { cout << i << " ("; }
        for (int j=0; j<adjs[i].size(); j++) { cout << adjs[i][j].u; if (j < adjs[i].size()-1) cout << " "; }
        if (adjs[i].size() > 0) { cout << "), "; }
    }
    if (aaa) cout << endl;
}

int main() {
    ll n, m; cin >> n >> m;
    int u, v, w, maxw;
    for (int i=1; i<m+1; i++) {
        cin >> u >> v >> w;
        edge e; e.u = u; e.v = v; e.i = i;
        if (w > maxw) { maxw = w; }
        edges[w].push_back(e);
    }

    for (int i=1; i<n+1; i++) { par[i] = i; }

    for (int w=1; w<maxw+1; w++) {
        if (edges[w].size() == 0) { continue; }

        /*
            first of all we'll take as much 'w' weighted edges as possible.
            two end-points of each new edge are not in the same tree yet.
            so we'll put each one's root as an adjacent of the other one's.
            changing visited values makes it possible to pass from visited nodes of previous dfs calls.
        */
        for (int j=0; j<edges[w].size(); j++) {
            int u = edges[w][j].u; int v = edges[w][j].v; int i = edges[w][j].i;
            if (find(u) != find(v)) {
                adj invari = {find(v), i}; adj onvari = {find(u), i};
                adjs[find(u)].push_back(invari); adjs[find(v)].push_back(onvari);
                visited[find(u)] = 0; visited[find(v)] = 0;
                ans[i] = SOME;
            }
        }
        // print_adjs(n);

        /*
            keep in mind that nodes which are only connected to edges with weights less than 'w', are already visited because of previous dfs calls
            and their status did not change. hence they won't participate in these dfs calls.
            also nodes that are only connected to edges with weights greater than 'w', are not in the adjacency lists yet.
        */
        for (int j=0; j<edges[w].size(); j++) {
            int u = edges[w][j].u; int v = edges[w][j].v; int i = edges[w][j].i;

            /*
                in dfs tree, a vertex u is an articulation point if one of the following two conditions is true. 
                u is the root of the DFS tree and it has at least two children or u is not the root of the dfs tree
                and it has a child v such that no vertex in the subtree rooted with v has a backedge to one of the ancestors in DFS tree of u.
            */
            if (!visited[find(u)]) { dfs(find(u), -1, 0); }

            // we don't need these edges anymore. that's because they're marked as visited and can't participate in future dfs calls.
            adjs[find(u)].clear(); adjs[find(v)].clear();
            // joining two sets by making par[v] also the parent of root(u)
            par[find(u)] = par[v];
        }
        // print_parents(n, w);
    }

    for (int i=1; i<m+1; i++) { cout << int_answer_to_str[ans[i]] << endl; }
    return 0;
}
