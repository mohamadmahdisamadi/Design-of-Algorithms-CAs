#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>
#include <cmath>

using namespace std;
int cnt;
const int maxn = 101;
int n, m;

class Graph {
    int V;
    vector<vector<int>> capacity;
    vector<vector<int>> cap2;
    vector<vector<int>> adj;
    vector<vector<int>> flow;
public:
    Graph(int V);
    void addEdge(int u, int v, int cap);
    int edmondsKarp(int source, int sink);
    string create_ans();
    bool check_flows(int source, int sink);

private:
    int bfs(int source, int sink, vector<int>& parent);
};

Graph::Graph(int V) : V(V), capacity(V, vector<int>(V, 0)), cap2(V, vector<int>(V, 0)), adj(V), flow(V, vector<int>(V, 0)) {}

void Graph::addEdge(int u, int v, int cap) {
    // cout << "adding edge from " << u << " to " << v << " cap: " << cap << endl;
    capacity[u][v] = cap;
    cap2[u][v] = cap;
    adj[u].push_back(v);
    adj[v].push_back(u);
}

int Graph::bfs(int source, int sink, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[source] = -2;
    queue<pair<int, int>> q;
    q.push({source, INT_MAX});

    while (!q.empty()) {
        int curr = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[curr]) {
            if (parent[next] == -1 && capacity[curr][next]) {
                parent[next] = curr;
                int new_flow = min(flow, capacity[curr][next]);
                if (next == sink) {
                    return new_flow;
                }
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int Graph::edmondsKarp(int source, int sink) {
    int max_flow = 0;
    vector<int> parent(V);
    int new_flow;

    while (new_flow = bfs(source, sink, parent)) {
        max_flow += new_flow;
        int curr = sink;

        while (curr != source) {
            int prev = parent[curr];
            capacity[prev][curr] -= new_flow;
            capacity[curr][prev] += new_flow;
            flow[prev][curr] += new_flow;
            flow[curr][prev] -= new_flow;
            curr = prev;
        }
    }

    return max_flow;
}

bool Graph::check_flows(int source, int sink) {
    for (int i=1; i<n+1; i++) { if (abs(flow[source][i] - cap2[source][i]) > 1e-9) { return false; } }
    for (int i=n+1; i<n+m+1; i++) { if (abs(flow[i][sink] - cap2[i][sink]) > 1e-9) { return false; } }
    return true;
}


string Graph::create_ans() {
    string s = "";
    for (int u = 1; u < n+1; u++) {
        for (int v=n+1; v<n+m+1; v++) {
            if (flow[u][v] >= 0.5) { s += "1"; }
            else { s += "0"; }
            if (v < n+m) { s += " "; }
            else { s += "\n"; }
        }
    }
    return s;
}

int stof7(string s) {
    bool is_neg = s[0] == '-';
    int k = (int)is_neg;
    int res = 0;
    for (k; k<s.size(); k++) {
        if (s[k] == '.') continue;
        res = res * 10 + (int)(s[k] - '0');
    }
    return res;
}


string bruh() {
    cin >> n >> m;
    int A[maxn][maxn];

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            string s; cin >> s;
            int res = stof7(s);
            int frac;
            if (s[0] == '-') { frac = 1000 - (res % 1000); }
            else { frac = (res % 1000); }
            A[i][j] = frac;
        }
    }

    Graph g(n+m+2);
    int source = 0; int sink = n+m+1;

    int row_sum = 0, col_sum = 0;
    for (int i=0; i<n; i++) {
        int sum = 0;
        for (int j=0; j<m; j++) { sum += A[i][j]; }
        if ((sum % 1000) == 0) { g.addEdge(source, i+1, (int)((sum+500)/1000)); }
        else { return "NO\n"; }
        row_sum += sum;
    }

    for (int j=0; j<m; j++) {
        int sum = 0;
        for (int i=0; i<n; i++) { sum += A[i][j]; }
        if ((sum % 1000) == 0) { g.addEdge(j+n+1, sink, (int)((sum+500)/1000)); }
        else { return "NO\n"; }
        col_sum += sum;
    }

    if (row_sum != col_sum) { return "NO\n"; }

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (A[i][j] == 0) { g.addEdge(i+1, j+n+1, 0); }
            else  { g.addEdge(i+1, j+n+1, 1); }
        }
    }

    g.edmondsKarp(source, sink);

    if (!g.check_flows(source, sink)) {
        return "NO\n";
    } else {
        string s = "YES\n";
        s += g.create_ans();
        return s;
    }
}

int main() {
    int t; cin >> t;
    string s = "";
    while (t--) { cnt++; s += bruh(); }
    cout << s;
    return 0;
}