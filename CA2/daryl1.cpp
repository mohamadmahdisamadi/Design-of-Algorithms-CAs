#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

const int RICK = 1;
typedef long long ll;
const ll inf = 1e17;
const bool hell_nuh = false;

string reverse_string(string s) {
    stack<char> stack;
    for (int i=0; i<s.size(); i++) {
        stack.push(s[i]);
    }
    string rev_s;
    while (!stack.empty()) {
        rev_s.push_back(stack.top());
        stack.pop();
    }
    return rev_s;
}

ll find_minimum(ll a, ll b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

int main() {
    ll n; cin >> n;
    ll costs[n];
    for (int i=0; i<n; i++) cin >> costs[i];
    string strings[n], rev_strings[n];
    for (int i=0; i<n; i++) cin >> strings[i];
    for (int i=0; i<n; i++) rev_strings[i] = reverse_string(strings[i]);

    // min_cost[i][b]: min cost of sorting all strings up to the i'th one if the last one is (b) ? reversed : not reversed
    pair<ll, ll> min_cost[n];
    for (int i=0; i<n; i++) {
        min_cost[i] = {inf, inf};
    }

    // base cases
    min_cost[0].first = 0;
    min_cost[0].second = costs[0];

    for (int i=1; i<n; i++) {
        bool can_sort_ascending_til_index_i = hell_nuh;
        if (strings[i] == strings[i-1]) {
            min_cost[i].first = min_cost[i-1].first; 
            can_sort_ascending_til_index_i = true;
        }
        if (strings[i] > strings[i-1]) {
            if (min_cost[i].first == inf) {
                min_cost[i].first = min_cost[i-1].first;
            } else if (min_cost[i-1].first < min_cost[i].first) {
                min_cost[i].first = min_cost[i-1].first;
            }
            can_sort_ascending_til_index_i = true;
        }
        if (strings[i] == rev_strings[i-1]) {
            if (min_cost[i].first == inf) {
                min_cost[i].first = min_cost[i-1].second;
            } else if (min_cost[i-1].second < min_cost[i].first) {
                min_cost[i].first = min_cost[i-1].second;
            }
            can_sort_ascending_til_index_i = true;
        }
        if (strings[i] > rev_strings[i-1]) {
            if (min_cost[i].first == inf) {
                min_cost[i].first = min_cost[i-1].second;
            } else if (min_cost[i-1].second < min_cost[i].first) {
                min_cost[i-1].second = min_cost[i].first;
            }
            can_sort_ascending_til_index_i = true;
        }
        if (rev_strings[i] == strings[i-1]) {
            min_cost[i].second = min_cost[i-1].first + costs[i];
            can_sort_ascending_til_index_i = true;
        }
        if (rev_strings[i] > strings[i-1]) {
            if (min_cost[i].second == inf) {
                min_cost[i].second = min_cost[i-1].first + costs[i];                
            } else if (min_cost[i-1].first + costs[i] < min_cost[i].second) {
                min_cost[i].second = min_cost[i-1].first + costs[i];
            }
            can_sort_ascending_til_index_i = true;
        }
        if (rev_strings[i] == rev_strings[i-1]) {
            if (min_cost[i].second == inf) {
                min_cost[i].second = min_cost[i-1].second + costs[i];
            } else if ((min_cost[i-1].second + costs[i]) < min_cost[i].second) {
                min_cost[i].second = min_cost[i-1].second + costs[i];
            }
            can_sort_ascending_til_index_i = true;
        }
        if (rev_strings[i] > rev_strings[i-1]) {
            if (min_cost[i].second == inf) {
                min_cost[i].second = min_cost[i-1].second + costs[i];
            } else if ((min_cost[i-1].second + costs[i]) < min_cost[i].second) {
                min_cost[i].second = min_cost[i-1].second + costs[i];
            }
            can_sort_ascending_til_index_i = true;
        }
        if (can_sort_ascending_til_index_i == hell_nuh) {
            cout << -1 << endl;
            return RICK;
        }
    }
    if (min_cost[n-1].first < min_cost[n-1].second) {
        cout << min_cost[n-1].first << endl;
    } else {
        cout << min_cost[n-1].second << endl;
    }
    return RICK;
}