#include <iostream>
#include <vector>
#include <map>
#include <bits/stdc++.h>
using namespace std;

// third time wasn't the charm but 12'th time will be
// this time let's calculate the Pascal's triangle formula using dp and not recursively

// define a constant number to represent NULL value
// since all nodes are from 1 to N, 0 isn't one of them
const int NO = 0;
int ans;
const long long maxn = 1001;
map<int, int> father, l_ch, r_ch, tree_size, answer;
vector<vector<long long>> all_combs;

long long mode = 1000000007;


vector<vector<long long>> calc_all_combs() {
    // combs[i][j] is the number of ways to choose i items from j items
    vector<vector<long long>> combs (maxn ,vector<long long> (maxn));

    // 1 way to choose i things from i things (choose them all)
    for (int i=1; i<maxn; i++)
        combs[i][i] = 1;
    // i different ways to choose 1 thing from i things
    for (int i=1; i<maxn; i++)
        combs[1][i] = i;
    // 1 way to choose nothing from a number of things (don't choose)
    for (int i=1; i<maxn; i++)
        combs[0][i] = 1;
    // choosing a number of things from a less number of things is impossible
    for (int i=1; i<maxn; i++)
        for (int j=1; j<i; j++) 
            combs[i][j] = 0;
    // dynamically calculate all the other combinations
    for (int i=1; i<maxn; i++)
        for (int j=i+1; j<maxn; j++)
            combs[i][j] = (combs[i-1][j-1] + combs[i][j-1]) % mode;

    return combs;
}

int count_childs(int node) {
    // base case: we reach an empty node
    if (node == NO) {
        return 0;
    }

    int l = l_ch[node], r = r_ch[node];

    int tree_size_l = 0, tree_size_r = 0;

    tree_size_l = count_childs(l);    
    tree_size_r = count_childs(r);
    
    tree_size[node] = tree_size_l + tree_size_r + 1;

    return tree_size[node];
}

long long bruh(int node) {
    if (node == NO) {
        return 1;
    }
    if (tree_size[node] == 1) {
        answer[node] = 1;
        return 1;
    }

    int l = l_ch[node], r = r_ch[node];
    long long ans_l = bruh(l) % mode, ans_r = bruh(r) % mode;

    int len_l = tree_size[l];
    int len_r = tree_size[r];

    // there are comb different ways to insert nodes and get the exact same tree 
    long long comb = all_combs[min(len_l, len_r)][len_l+len_r] % mode;
    // ans_l and ans_r are the different ways to swap the nodes of each sub-tree without changing the final tree
    long long nuh = (ans_l * ans_r) % mode;
    answer[node] = (comb * nuh) % mode;
    return answer[node]; 
}

int main() {
    // get inputs
    int n;
    cin >> n;
    vector<int> v;
    for (int i=0; i<n; i++) {
        int bruh; cin >> bruh;
        v.push_back(bruh);
    }

    // store inputs in a nore meaningful way (as a binary search tree)
    int root = v[0];
    father[root] = NO;
    l_ch[root] = NO;
    r_ch[root] = NO;

    for (int i=1; i<size(v); i++) {
        int daryl = v[i];
        int cur = root;
        while (true) {
            if (daryl < cur) {
                // the new node belonges somewhere in the left sub-tree
                if (l_ch[cur] == NO) {
                    // place the new node
                    father[daryl] = cur;
                    l_ch[daryl] = NO;
                    r_ch[daryl] = NO;
                    l_ch[cur] = daryl;
                    break;
                } else {
                    // go left
                    cur = l_ch[cur];
                }
            } else {
                // the new node belonges somewhere in the right sub-tree
                if (r_ch[cur] == NO) {
                    // place the new node
                    father[daryl] = cur;
                    l_ch[daryl] = NO;
                    r_ch[daryl] = NO;
                    r_ch[cur] = daryl;
                    break;
                } else {
                    // go right
                    cur = r_ch[cur];
                }
            }
        }
    }
   
    count_childs(root);
    all_combs = calc_all_combs();
    cout << bruh(root) - 1 << endl; 
    return 0;
}