#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll maxn = 500007; // max number of vertexes
const ll maxm = 500007; // max number of edges
const ll maxw = 500007; // max weight of all edges
const ll maxq = 500007; // max number of query edges

struct edge { ll u; ll v; ll w; }; // it stores info about an edge
struct query_edge { edge e; ll qid; }; // it stores some info about a query edge
struct depth_info { ll u; ll du; }; // it stores informations of depth to recover after unions
edge edges[maxw]; // array to store input edges
vector<query_edge> we, wq; // we is set of all input edges and wq is set of all query edges
vector<ll> unique_weights; // vector to store all distinct edge weights

ll par[maxm], depth[maxm]; // are beign used on DSU
ll ans[maxq]; // stores final answers of each query
vector<int> parent_backup; // saves parent of nodes used in unions
vector<depth_info> depth_backup; // saves depth of nodes used in unions
bool need_to_save_backup; // indicates whether to store parent and depth info or not
vector<string> answers = {"NO\n", "YES\n"}; // set of possible answers

/*
    function to recursively find the parent in DSU and update parent of all nodes along its path
    actually it doesn't. it was because of this that the fourth test case was wrong answer all this time
    is just returns the parent and doesn't change anything
*/
ll find(ll u) {
    if (u == par[u]) {return u; }
    else { return find(par[u]); }
}

// saves da fukin backup if needed
void save_da_fukin_backup(ll u, ll v) {
    parent_backup.push_back(u);
    depth_backup.push_back({v, depth[v]});
}

// recovers info if it was even stored
void recover_data() {
    while (parent_backup.size()) {
        par[parent_backup[parent_backup.size()-1]] = parent_backup[parent_backup.size()-1];
        parent_backup.pop_back();
    }
    while (depth_backup.size()) {
        depth[depth_backup[depth_backup.size()-1].u] = depth_backup[depth_backup.size()-1].du;
        depth_backup.pop_back();
    }
}

// function to join two DSU's and save info if needed
void union_sets(ll u, ll v) {
    if (depth[u] < depth[v]) { par[u] = v; if(need_to_save_backup) { save_da_fukin_backup(u, v); } }
    else if (depth[u] > depth[v]) { par[v] = u; if(need_to_save_backup) { save_da_fukin_backup(v, u); } }
    else { par[v] = u; if(need_to_save_backup) { save_da_fukin_backup(v, u); } depth[u]++; }
}
/*
    compare function to use in sorting edges.
    first it compares them based on weight. if two edges have the same weight, it checks their id
*/
bool compare_edges(const query_edge& a, const query_edge& b) {
    if (a.e.w == b.e.w) { return a.qid < b.qid; }
    else { return a.e.w < b.e.w; }
}

int main() {
    for (ll i=0; i<maxq; i++) { ans[i] = 1; } // all answers are "YES" by defualt. we'll cahnge them if needed
    ll n, m;
    cin >> n >> m;
    bool has_weight[maxn];
    for (ll i=0; i<maxn; i++) { has_weight[i] = false; }
    for (ll i=0; i<m; i++) {
        ll u, v, w; cin >> u >> v >> w;
        edges[i+1].u = u; edges[i+1].v = v; edges[i+1].w = w;
        we.push_back({edges[i+1], i+1});
        has_weight[edges[i+1].w] = true;
    }

    // store distinct edges in a vector
    for (ll i=1; i<maxw; i++) { if (has_weight[i]) { unique_weights.push_back(i); } }

    ll q; cin >> q;
    for (ll i=0; i<q; i++) {
        ll k, idx; cin >> k;
        for (ll j=1; j<k+1; j++) {
            cin >> idx;
            wq.push_back({edges[idx], i+1});
        }
    }

    sort(we.begin(), we.end(), compare_edges);
    sort(wq.begin(), wq.end(), compare_edges);

    for (ll i=0; i<n+1; i++) { par[i] = i, depth[i] = 1; }

    /*
        qp: pointer of the wq vector
        wp: pointer of the unique_weights vector
        ep: pointer of the eq vector
        w: current w. starting from 1 and ending at max(unique_weights)
    */
    ll qp = 0, ep = 0, wp = 0;
    ll w = 0;
    while(w < maxw) {
        if (w > unique_weights[unique_weights.size() - 1]) { break; } // there is no other edge of weight equal to or greater than 'w'.
        else if (unique_weights[wp] != w) { w++; continue; } // there is no edge of weight equal to 'w'. increment 'w' and continue to the next round of iteration 
        need_to_save_backup = true; // we need to store current state to recover it after checking all query edges of weight 'w'
        while(qp < wq.size() and wq[qp].e.w == w) { // at each iteration, all query edges of weight 'w' are covered
            ll id = wq[qp].qid;
            while(qp < wq.size() and wq[qp].qid == id and wq[qp].e.w == w) { // at each iteration, all query edges of weight 'w' and qid 'id' are covered
                ll ru = find(wq[qp].e.u); ll rv = find(wq[qp].e.v);
                /*
                    here is the tricky part. if edges of weight 'w' for query with qid 'id' cause an cycle, it means this query can't be done.
                    all other present edges on the cycle are strictly less weighted than 'w' for sure.
                    in other words we can't remove one of them and use this edge. that is against the greedy nature of Kruskal algorithm. 
                */
                if (ru == rv) { ans[wq[qp].qid] = 0; }
                else { union_sets(ru, rv); }
                qp++;
            }
            recover_data(); // data is recovered after covering all query edges of weight 'w' and qid 'id'
        }
        need_to_save_backup = false; // this time we actually wanna perform next step of Kruskal algorithm and the data does not need to be saved 
        while (ep < we.size() and we[ep].e.w == w) {
            ll ru = find(we[ep].e.u); ll rv = find(we[ep].e.v);
            if (ru == rv) {}
            else { union_sets(ru, rv); }
            ep++;
        }
        w++; wp++;
    }
    for (ll i=1; i<q+1; i++) { cout << answers[ans[i]]; }
    return 0;
}