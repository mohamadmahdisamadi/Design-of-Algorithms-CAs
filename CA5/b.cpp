#include <bits/stdc++.h>
using namespace std;

const int maxn = 501, maxm = 1001;
int n, m;
int p[maxn];
bool is_edge[maxn][maxn];
bool visited[maxm];
vector<int> adj[maxn];
struct eg { int u; int i; };
vector<eg> edges[maxn];
stack<stack<int>> found_paths;

int bfs() {
    for (int i=1; i<n+1; i++) p[i] = -1;
    int queue_size = 0;
    queue<int> queue;
    queue.push(1); queue_size++;
    while(queue_size){
        int u = queue.front();
        queue.pop(); queue_size--;
        for(int i=0; i<adj[u].size(); i++) {
            if(p[adj[u][i]] == -1 && is_edge[u][adj[u][i]]){
                p[adj[u][i]] = u;
                if(adj[u][i] == n) return 1;
                queue.push(adj[u][i]); queue_size++;
            }
        }
    }
    return 0;
}

void edmonds_karp() {
    while (bfs()) {
        stack<int> s;
        int u = n;
        while(u != 1) {
            if (u == n) s.push(u);
            s.push(p[u]);
            is_edge[p[u]][u] -= 1; is_edge[u][p[u]] += 1;
            u = p[u];
        }
        found_paths.push(s);
    }
    return;
}

int main() {
    cin >> n >> m;
    int i=0, u, v;
    while (m--) {
        cin >> u >> v;
        edges[u].push_back({v, i});
        adj[u].push_back(v); adj[v].push_back(u);
        is_edge[u][v] = 1; i++;
    }

    edmonds_karp();
    cout << found_paths.size() << endl;
    while (!found_paths.empty()) {
        stack<int> s = found_paths.top(); found_paths.pop();
        cout << s.size() << endl;
        while (7) {
            cout << s.top(); s.pop();
            if (s.empty()) { cout << endl; break; }
            else { cout << " "; }
        }
    }
    return 0;
}