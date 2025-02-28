#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;
typedef long long ll;

const ll maxn = 1007;
const ll INF = 1e8;
const int num_kingdoms = 3;
struct cord { int x; int y; };
vector<vector<int>> grid(maxn, vector<int> (maxn, 0));
const int ROAD = -1;
const int WALL = -2; 
int n, m;
// manh_dist[i][j][k] is the minimum needed roads to go to kingdom 'k' from i'th row and j'th column of the grid
ll manh_dist[maxn][maxn][num_kingdoms];

/*
    we'll use two queues in each bfs.
    first one for the nodes that are added without any road from their parent.
    second one for the nodes that has cost us a road to reach them.
    obviously nodes of the first queue are always preferred over the other one
*/
class two_queues {
    private:
        queue<cord> q[2];
    public:
        two_queues() {}
        bool check_emptiness() { return q[0].empty() and q[1].empty(); }
        void push(int queue_num, cord cd) { q[queue_num].push(cd); }
        cord pop() {
            int queue_num = q[0].empty();
            cord cd = q[queue_num].front();
            q[queue_num].pop();
            return cd;
        }
};

int k; // shows current kingdom
bool visited[maxn][maxn]; // visited array to use in graph traversal
void reset_visited() { for (int i=0; i<maxn; i++) for (int j=0; j<maxn; j++) { visited[i][j] = false; } }
bool is_inside_borders(int i, int j) { return i<n and i>-1 and j<m and j>-1; } // check if the given cordinate is inside the grid
int bfs() {
    two_queues q;
    // first of all we'll add nodes of the current kingdom to their queue
    for (int i=0; i<n; i++) for (int j=0; j<m; j++) if (grid[i][j] == k) { q.push(0, {i, j}); };
    int ni, nj;
    while (!q.check_emptiness()) {
        cord node = q.pop(); // take a node from the first queue if possible, otherwise take it from the second one
        visited[node.x][node.y] = true; // mark this node as visited
        // these two nested loops are to create all possible directions to go from current node
        for (int di=-1; di!=2; di++) {
            for (int dj=-1; dj!=2; dj++) {
                // we can move in exactly one direction at a time
                if (!(abs(di) ^ abs(dj))) continue;
                ni = node.x + di; nj = node.y + dj;

                /*
                    checking necessary conditions:
                    1. new cordinate is inside the grid
                    2. new node is not previously visited
                    3. new node is not a '#'
                    4. new node doesn't belong to kingdom 'k'. because if it does, we've already added it to the queue
                */ 
                if (is_inside_borders(ni, nj) and !visited[ni][nj] and grid[ni][nj] != WALL and grid[ni][nj] != k) {
                    bool is_road = grid[ni][nj] == ROAD;
                    visited[ni][nj] = true; // mark this node as visited
                    manh_dist[ni][nj][k] = manh_dist[node.x][node.y][k] + is_road; // update dist for new node
                    cord new_node; new_node.x = ni; new_node.y = nj;
                    q.push(is_road, new_node); // add this node to its queue
                }
            }
        }
    }
    // returning 17 for no reason
    return 17;
}

int main() {
    cin >> n >> m;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            /*
                initializing manh_dist array for grid cells.
                each cell that belonges to kingdom 'k', has distance zero to kingdom 'k'.
            */
            for (int k=0; k<num_kingdoms; k++) { manh_dist[i][j][k] = INF; }
            char ch; cin >> ch;
            if (ch == '.') { grid[i][j] = ROAD; }
            else if (ch == '#') { grid[i][j] = WALL;}
            else { grid[i][j] = (int)(ch - '1'); manh_dist[i][j][(int)(ch - '1')] = 0; }
        }
    }

    // using three bfs traversals, we'll fill manh_dist array.
    for (k=0; k<num_kingdoms; k++) { reset_visited(); bfs(); }

    // finding cell with minimum number of needed roads to connect all kingdoms to one another
    ll min_roads = INF;
    ll new_dist;
    bool found_a_way = false;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            new_dist = 0;
            bool has_a_way_to_all_kingdoms = true; // shows if this cell of grid has a way to all kingdoms
            bool is_road = (grid[i][j] == ROAD);
            for (k=0; k<num_kingdoms; k++) {
                if (manh_dist[i][j][k] == INF) { has_a_way_to_all_kingdoms = false; }
                else if (is_road) { new_dist += manh_dist[i][j][k] - 1; } // if it's a road, don't count the road itself each time. we'll ad it once at the end
                else { new_dist += manh_dist[i][j][k]; }
            }
            // if it's a road, it'll cost us one more to pass through it
            if (is_road) new_dist++;
            found_a_way = found_a_way || has_a_way_to_all_kingdoms;
            // update min_roads if the new cell is valid and needs less roads to reach all kingdoms than the previous answer
            if ((has_a_way_to_all_kingdoms) and (new_dist < min_roads)) { min_roads = new_dist; }
        }
    }

    if (found_a_way) cout << min_roads;
    else cout << -1;
    cout << endl;
    return 0;
}