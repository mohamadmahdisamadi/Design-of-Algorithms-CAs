#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>
#include <cmath>

using namespace std;
const int maxn = 13000;
const int inf = 1e9;
int n, S, T;

struct edge {
    int to, capacity, flow;
    edge* rev;
};

pair<int, int> basicesh_ine[maxn];
pair<int, int> bugesh_ine[maxn];
vector<edge*> adj[maxn];
int level[maxn], work[maxn];

void addEdge(int u, int v, int cap) {
    edge* uv = new edge{v, cap, 0, nullptr};
    edge* vu = new edge{u, 0, 0, uv};
    uv->rev = vu;
    adj[u].push_back(uv);
    adj[v].push_back(vu);
}

// translates 2d cordinates into 1d
// i and j are zero based
// output is also zero based
int c2i_in(int i, int j) {
    return 2*((j*(n-1)) + i);
}
int c2i_out(int i, int j) {
    return 2*((j*(n-1)) + i) + 1;
}

bool bfs() {
    memset(level, -1, sizeof(level));
    queue<int> q;
    q.push(S);
    level[S] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (edge* e : adj[u]) {
            int v = e->to;
            if (level[v] == -1 && e->capacity > e->flow) {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return level[T] != -1;
}

int dfs(int u, int flow) {
    if (u == T) return flow;
    for (int& i = work[u]; i < adj[u].size(); ++i) {
        edge* e = adj[u][i];
        int v = e->to;
        if (level[v] == level[u] + 1 && e->capacity > e->flow) {
            int minFlow = min(flow, e->capacity - e->flow);
            int result = dfs(v, minFlow);
            if (result > 0) {
                e->flow += result;
                e->rev->flow -= result;
                return result;
            }
        }
    }
    return 0;
}

int maxFlow() {
    int totalFlow = 0;
    while (bfs()) {
        memset(work, 0, sizeof(work));
        while (int flow = dfs(S, inf)) {
            totalFlow += flow;
        }
    }
    return totalFlow;
}

int main() {
    cin >> n;
    S = 2 * (n-1) * (n-1) + 2;
    T = 2 * (n-1) * (n-1) + 3;
    char A[2*n][2*n];
    for (int i=1; i<2*n; i++) for (int j=1; j<2*n; j++) cin >> A[i][j];

    for (int i=1; i<n; i++) {
        for (int j=1; j<n; j++) {
            int ii = 2*i, jj = 2*j;
            bool free_to_go_right = A[ii][jj+1] == '.';
            bool free_to_go_left = A[ii][jj-1] == '.';
            bool free_to_go_up = A[ii-1][jj] == '.';
            bool free_to_go_down = A[ii+1][jj] == '.';
            int cap = (int)(free_to_go_left) + (int)(free_to_go_right) +
                      (int)(free_to_go_down) + (int)(free_to_go_up) - 1;
            bool niggruh = (i + j) % 2 == 0;
            int x = j-1; int y = i-1;

            addEdge(c2i_in(x, y), c2i_out(x, y), cap);

            if (niggruh) { addEdge(c2i_out(x, y), T, 7); }
            else { addEdge(S, c2i_in(x, y), 7); }
            
            if (!niggruh) {
                if (free_to_go_left and j > 1) { addEdge(c2i_out(x, y), c2i_in(x-1, y), 1); }
                if (free_to_go_right and j < n-1) { addEdge(c2i_out(x, y), c2i_in(x+1, y), 1); }
                if (free_to_go_up and i > 1) { addEdge(c2i_out(x, y), c2i_in(x, y-1), 1); }
                if (free_to_go_down and i < n-1) { addEdge(c2i_out(x, y), c2i_in(x, y+1), 1); }
            }

            int pointesh_ine = 0;
            if (free_to_go_left and j == 1) pointesh_ine++;
            if (free_to_go_right and j == n-1) pointesh_ine++;
            if (free_to_go_up and i == 1) pointesh_ine++;
            if (free_to_go_down and i == n-1) pointesh_ine++;

            if (pointesh_ine) {
                if (niggruh) { addEdge(S, c2i_in(x, y), pointesh_ine); }
                else { addEdge(c2i_out(x, y), T, pointesh_ine); }
            }
            
        }
    }

    int ans = maxFlow();
    cout << ans << endl;

    return 0;
}