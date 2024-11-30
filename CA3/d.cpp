#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 200001;

/*
    The greedy choice is to assign values only to the leaves.
    We choose the maximum element as root of the tree.
*/

// decided to nam all the variables after TWD characters for no reason
bool turned_into_walker[maxn]; // the 'visited' array to use in dfs
bool is_judith[maxn]; // whether a node is leaf or not
ll daryl[maxn]; // max value of leaves in a node's sub-tree
vector<ll> alexandria (maxn, 0); // initial heights
vector<vector<int>> carol(maxn+1, vector<int> (0)); // adjacency list
int rick; // the root
bool rick_has_only_carl = false; // whether the root has only one child or not
ll rosita = 0; // result

void dfs(int v) {
    turned_into_walker[v] = true;

    /*
        dead end in dfs is when we reach a leaf.
        we assign its value to its height.
        if needed, we'll update it later.
    */
    if (is_judith[v]) {
        rosita += alexandria[v];
        daryl[v] = alexandria[v];
    }

    /*
        if not a leaf, we need to find greatest value among the leaves of its sub-tree
        if the mantioned value can't handle this node, we need to increase it
        so far we've fixed one endpoint of the path for this node
        what about the other one? you'll see later
    */
    else {
        for (auto u : carol[v])
            if (!turned_into_walker[u])
                dfs(u);

        daryl[v] = 0;
        for (auto u : carol[v]) {
            if (daryl[u] > daryl[v]) {
                daryl[v] = daryl[u];
            }
        }
        if (alexandria[v] > daryl[v]) {
            rosita += alexandria[v] - daryl[v];
            daryl[v] = alexandria[v];
        }
    }
}

int main() {
    vector<int> bruh = {1, 2};
    daryl[0] = 0;
    int n; cin >> n;
    for (int i=1; i<n+1; i++) cin >> alexandria[i];
    for (int i=0; i<n-1; i++) {
        int u, v; cin >> u >> v;
        carol[u].push_back(v);
        carol[v].push_back(u);
    }

    for (int i=0; i<n+1; i++) if (alexandria[i] > alexandria[rick]) rick = i;

    for (int i=1; i<n+1; i++)
        if (carol[i].size() == 1)
            if (i != rick) is_judith[i] = true;
            else rick_has_only_carl = true;

    dfs(rick);

    /*
        in this case, the root has more than one child.
        since it has the maximum height and we already fixed one endpoint of its path, we need to find another one.
        in order to achive the minumum cost, we'll find the second maximum leaf and change it to value of the root.
    */
    if (!rick_has_only_carl) {
        vector<int> oceanside;
        for (auto u : carol[rick]) oceanside.push_back(daryl[u]);
        int carl = 0, judith = 0;

        for (int i=0; i<oceanside.size(); i++)
            if (oceanside[i] > oceanside[carl])
                carl = i;
        if (carl == 0) judith = 1;
        for (int i=0; i<oceanside.size(); i++)
            if (i != carl)
                if (oceanside[i] > oceanside[judith])
                    judith = i;
        rosita += alexandria[rick] - oceanside[judith];        
    }
    
    /*
        in this case, the root has exactly one child. it's a leaf then.
        so we have to set a value to the root itself.
    */
    else {
        daryl[rick] = alexandria[rick];
        rosita += alexandria[rick];
    }

    /*
        since root has the maximum height, by fixing its other endpoint, we've fixed the other endpoint of all other nodes too.
        because all of the nodes have a path to the root and the root has a path to the second endpoint.
    */

    cout << rosita << endl;
}