#include <iostream>
#include <vector>
using namespace std;

const int maxn = 1000;
vector<vector<int>> map(maxn, vector<int> (maxn, 0));
const int ROAD = -1;
const int WALL = -2; 
const int CITY = 0;
int cnt = CITY+1;
int n, m;

bool has_kingdom[4];
struct city {
    vector<pair< int, int>> connected_cities;
    int label;
    bool has_1;
    bool has_2;
    bool has_3;
};
int belongs_to_component[maxn];

// dfs traversal of the graph to label connected componetns
void dfs(int x, int y, vector<pair<int, int>>& connected_cities) {
    map[x][y] = cnt;
    has_kingdom[map[x][y]] = true;
    connected_cities.push_back({x, y});
    if ((x > 0) and (map[x-1][y] == CITY)) {
        dfs(x-1, y, connected_cities);
    } else if ((x < n-1) and (map[x+1][y] == CITY)) {
        dfs(x+1, y, connected_cities);
    } else if ((y > 0) and (map[x][y-1] == CITY)) {
        dfs(x, y-1, connected_cities);
    } else if ((y < m-1) and (map[x][y+1] == CITY)) {
        dfs(x, y+1, connected_cities);
    }
}

void print_matrix() {
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

vector<city> cities;
int main() {
    cin >> n >> m;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            char ch; cin >> ch;
            if (ch == '.') {
                map[i][j] = ROAD;
            } else if (ch == '#') {
                map[i][j] = WALL;
            } else {
                map[i][j] = ch - '0';
            }
        }
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (map[i][j] == CITY) {
                for (int k=1; k<4; k++) has_kingdom[k] = false;
                vector<pair<int, int>> connected_cities;
                dfs(i, j, connected_cities);
                city c;
                c.connected_cities = connected_cities;
                c.label = cnt;
                c.has_1 = has_kingdom[1];
                c.has_2 = has_kingdom[2];
                c.has_3 = has_kingdom[3];
                cities.push_back(c);
                cnt++;
            }
        }
    }
    cout << -1 << endl;
    return 0;
}