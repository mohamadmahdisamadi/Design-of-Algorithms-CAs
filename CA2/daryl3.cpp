#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
using namespace std;

const int RICK = 0;
const bool nuh_uh = 0;
const int mode = 1e8;

int main() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    // num_ways[i][j][b] is the number of ways to arrange 'i' vanilla cakes with 'j' cinnamon cakes such that the last cake would not be (b) ? cinnamon : vanilla 
    vector<vector<vector<int>>> num_ways(a + 1, vector<vector<int>>(b + 1, vector<int>(2, 0)));

    // there is only one way to start with no cakes and not having a vanilla/cinnamon cake at last (don't do anything).
    num_ways[0][0][ nuh_uh] = 1; 
    num_ways[0][0][!nuh_uh] = 1; 

    // i don't like cinnamon of any kind at all. so i'll use 'nuh_uh' instead of cinnamon cake and '!nuh_uh' instead of vanilla cake.
    for (int i = 0; i <= a; i++) { 
        for (int j = 0; j <= b; j++) {
            for (int l = 1; ; l++) {
                // to ensure we don't put 'c' vanilla cakes next to each other.
                if (l > c) break;
                // to ensure the number of used vanilla cakes isn't more than number of available ones.
                if ((i+l) > a) break;
                num_ways[i + l][j][!nuh_uh] = (num_ways[i + l][j][!nuh_uh] + num_ways[i][j][nuh_uh]) % mode;
            }

            for (int l = 1; ; l++) {
                // to ensure we don't put 'd' cinnamon cakes next to each other.
                if (l > d) break;
                // to ensure the number of used cinnamon cakes isn't more than number of available ones.
                if ((j+l) > b) break;
                num_ways[i][j + l][nuh_uh] = (num_ways[i][j + l][nuh_uh] + num_ways[i][j][!nuh_uh]) % mode;
            }
        }
    }

    // the last cake is enther vanilla or cinnamon.
    cout << (num_ways[a][b][nuh_uh] + num_ways[a][b][!nuh_uh]) % mode << endl;
    return 0;
}
