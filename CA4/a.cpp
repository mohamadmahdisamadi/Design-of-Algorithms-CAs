#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> visited;
vector<vector<int>> highway_to_hell; // non-air edges
vector<vector<int>> stairway_to_heaven; // air edges

void dfs(int n) {
    visited[n] = 1;
    for (auto& u : stairway_to_heaven[n]) if (!visited[u]) dfs(u);
}

int main() {
    int n, m; cin >> n >> m;

    // initialize 2D vectors
    for (int i=0; i<n+1; i++) {
        highway_to_hell.push_back({});
        stairway_to_heaven.push_back({});
        visited.push_back(0);
    }

    // store non-air edges
    for (int i=0; i<m; i++) {
        int u, v; cin >> u >> v;
        highway_to_hell[u].push_back(v);
        highway_to_hell[v].push_back(u);
    }

    // check if a node has no airway edge
    for (int i=1; i<n+1; i++) {
        if (highway_to_hell[i].size() == 0) {
            cout << 0 << endl;
            return 0;
        }
    }
    
    // sort each adjacency list to form the adjacency lists of transposed adjacency matrix more efficient
    for (auto& highway : highway_to_hell)
        sort(highway.begin(), highway.end());

    // loop over all nodes
    for (int i=1; i<n+1; i++) {
        // p is the pointer that we use to iterate the sorted adjacency list with
        int p = 0;

        // loop over all nodes except for i
        for (int j=1; j<n+1; j++) {
            if (i == j) continue;

            // check if p has reached its max limit
            if (p == highway_to_hell[i].size()) {
                stairway_to_heaven[i].push_back(j); 
                continue;
            }

            // if the element that p point to is equal to the index j, we need to increment p
            // otherwise, the edge does not exist in the transposed graph, so we add it here 
            if (highway_to_hell[i][p] == j) {
                p++;                
            } else {
                stairway_to_heaven[i].push_back(j);
            }
        }

        // just to prevent reaching memory limits (happened in the fourth test case for me)
        highway_to_hell[i].erase(highway_to_hell[i].begin(), highway_to_hell[i].end());
    }

    // it was a part of the song i was listening to while writing the code
    // it also shows number of connected components (not important)
    int how_little_i_acomplished_all_my_plans_in_life = 0;
    for (int i=1; i<n+1; i++) {
        if (!visited[i]) {
            dfs(i);
            how_little_i_acomplished_all_my_plans_in_life++;
        }
    }

    // if the graph has 'c' components, we can connect them using 'c' - 1 non-air edges, that's all
    cout << how_little_i_acomplished_all_my_plans_in_life - 1 << endl;
    return 0;
}