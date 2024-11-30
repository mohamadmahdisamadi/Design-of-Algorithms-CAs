#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

// a function to find the nearest shorter book on the right of every book
vector<int> calc_nearest_shorter_on_the_right(vector<ll> h) {
    int n = (int)h.size();
    vector<int> v (n, 0);
    v[n-1] = n;
    for (int i=n-2; i>-1; i--) {
        int j = i+1;
        while ((j < n) && (h[j] >= h[i])) j = v[j];
        v[i] = j;
    }
    return v;
}

// a function to find out if there is any ugly index or not 
bool is_any_ugly(vector<int> v, int k) {
    for (int i = 0; i < v.size(); i++) if ((v[i] - i) > k) return true;
    return false;
}

// a function to find all the ugly indices
vector<int> find_ugly_indices(vector<int> v, int k) {
    vector<int> ugly;
    for (int i = 0; i < v.size(); i++) if ((v[i] - i) > k) ugly.push_back(i);
    return ugly;
}

// a function to swap heights
void swap_heights(vector<ll>&h, int i, int j) {
    ll temp = h[i];
    h[i] = h[j];
    h[j] = temp;
}

// le main function
int main() {
    // get the inputs
    int n, k; cin >> n >> k;
    vector<ll> h (n, 0);
    for (int i=0; i<n; i++) cin >> h[i];

    // calc distances and find ugly indices
    vector<int> v = calc_nearest_shorter_on_the_right(h);
    vector<int> uglies = find_ugly_indices(v, k);
        
    // if there isn't any ugly book, we sure can make them beatiful with at most one move (do nothing)
    if (uglies.empty()) {
        cout << "YES\n";
        return 0;
    }

    // we'll check all the possible swaps
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            // if the book on the left is higher than the book on the right, we can swap them
            if (h[j] < h[i]) {
                swap_heights(h, i, j);
                // calculate distances again after swapping two books
                vector<int> vv = calc_nearest_shorter_on_the_right(h);
                // check if the new arrangment of the books is beatiful
                bool ligma = is_any_ugly(vv, k);
                if (!ligma) {
                    cout << "YES\n";
                    return 0;
                }
                // swap the two books back to their iriginal place
                swap_heights(h, i, j);
            }
        }
    }

    cout << "NO\n";
    return 0;
}