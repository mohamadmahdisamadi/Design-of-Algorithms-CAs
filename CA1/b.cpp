#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

typedef long long ll;
ll l, u;

// it is used after the conquer step and before the combine step
// counts the numof sub-arrays starting from i and ending at j that their sum is <= to daryl
ll count_valid_answers(vector<ll> &ps, int s, int m, int e) {
    ll cnt_lower = 0, cnt_upper = 0;
    int i=s, j=m+1;
    while ((i <= m) and (j <= e)) {
        if ((ps[j] - ps[i]) >= l) {
            cnt_lower += (e-j+1);
            i++;
        } else {
            j++;
        }
    }
    i=s; j=m+1;
    while ((i <= m) and (j <= e)) {
        if ((ps[j] - ps[i]) > u) {
            cnt_upper += (e-j+1);
            i++;
        } else {
            j++;
        }
    }
    return (cnt_lower - cnt_upper);
}

// a simple function to merge two sorted arrays
void merge(vector<ll> &ps, int s, int m, int e) {
    vector<ll> sorted;
    // two pointers to iterate through two sorted sub-arrays
    int i=s, j=m+1;
    // at each step, check two elements and choose the min one
    while ((i <= m) and (j <= e)) {
        if (ps[i] < ps[j]) {
            sorted.push_back(ps[i]); i++;
        } else {
            sorted.push_back(ps[j]); j++;
        }
    }

    // push the remaining elements from the left aub-array
    while (i <= m) {
            sorted.push_back(ps[i]); i++;
        }

    // push the remaining elements from the right aub-array
    while (j <= e) {
            sorted.push_back(ps[j]); j++;
        }

    // copy the sorted array back to the original one
    int len_sub_array = e - s + 1;
    for (int k=0; k<len_sub_array; k++) {
        ps[k+s] = sorted[k];
    }
}


ll divide_and_conquer(vector<ll> &ps, int s, int e) {
    // base case: the sub-array contains only 1 element
    if (s >= e) {
        return 0;
    }

    int m = (s + e) / 2;
    // recursively solve the left sub-array
    ll left = divide_and_conquer(ps, s, m);
    // recursively solve the right sub-array
    ll right = divide_and_conquer(ps, m+1, e);

    ll from_left_to_right = count_valid_answers(ps, s, m, e);
    merge(ps, s, m, e);
    return right + left + from_left_to_right;
}

vector<ll> calc_partial_sum(vector<ll> arr) {
    // ps[i] is sum of all elements before ps[i]
    // base case: ps[0] (which correspondes to the first element) is 0
    vector<ll> ps(size(arr)+1, 0);
    for (int i = 1; i <= size(arr); i++)
        ps[i] = ps[i - 1] + arr[i - 1];
    return ps;
}

int main() {
    string line;
    getline(cin, line);

    istringstream st(line);
    vector<ll> arr;
    string num;

    while (st >> num)
        arr.push_back(stoi(num));

    cin >> l >> u;
    vector<ll> ps = calc_partial_sum(arr);
    ll num_subarrays_sum_gl_lower = divide_and_conquer(ps, 0, size(ps)-1);
    cout << num_subarrays_sum_gl_lower << endl;    

    return 0;
}