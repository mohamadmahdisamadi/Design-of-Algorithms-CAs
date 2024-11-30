// a whole new approach
// let's try not creating an array of size 2^n and just storing the k inputs 

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool print_stuff = false;
ll n, k, A, B;

// simple binary search on sorted array
// if the target exists, it will return index of the nearest greater element
// if the target does not exist in there, it will return index of the nearest greater element
int search_in_sorted(vector<ll> &a, int s, int e, int target) {
    while (s != e) {
        int m = (s + e) / 2;
        if (target < a[m]) {
            e = m;
        } else {
            s = m+1;
        }
    }
    return e;
}

// a is the k_people input array
// sk and ek are start and end indices of the k_people array
// sq and eq are start and end indices of the actual queue
ll divide_and_conquer(vector<ll> &a, ll start_q, ll end_q, ll start_k, ll end_k) {
    // the case where we only got one stage left with N people in it (N is a non-negative integer)
    // dealing with them will cost N*1*B if any people exists there
    // but if it's empty, Mr. Amini will just spend A energy to deal with no people (so weird)
    if ((start_q + 1) >= end_q) {
        if (print_stuff) {
            cout << start_q << " " << end_q << "   " << start_k << " " << end_k << "  [";
            for (int i=start_k; i<end_k; i++) cout << a[i] << ((i < (end_k - 1)) ? ", " : "");
            cout << "]" << endl;
            cout << "ye khoone queue " << max(B * (end_k - start_k), A) << endl << endl;
        }
        return max(A, B * (end_k - start_k));
    }

    // there is no one in this part of the queue
    // if Mr. Amini wants to directly handle these people, He would have to pay A cost
    // if he divides it into two parts, he will have to pay (2^k)*A (where k is a natural number) at some point
    // since 2 > 1, the cost will exponentially grow with each divide 
    // so it's only logical to get rid of them now
    if (start_k >= end_k) {
        if (print_stuff) {
            cout << start_q << " " << end_q << "   " << start_k << " " << end_k << "  [";
            for (int i=start_k; i<end_k; i++) cout << a[i] << ((i < (end_k - 1)) ? ", " : "");
            cout << "]" << endl;
            cout << "khali " << A << endl << endl;
        }
        return A;
    }
    
    // the middle index to use to divide the queue
    ll middle_q = (start_q + end_q) / 2;
    ll middle_k = search_in_sorted(a, start_k, end_k, middle_q-1);
    if (print_stuff) {
        cout << endl << "q: " << start_q << " " << end_q << " --> " << middle_q;
        cout << "    k: " << start_k << " " << end_k << " --> " << middle_k << endl << endl;
    }

    ll handle_now_energy = (end_k - start_k) * B * (end_q - start_q);
    if (print_stuff) {
        cout << start_q << " " << end_q << "   " << start_k << " " << end_k << "  [";
        for (int i=start_k; i<end_k; i++) cout << a[i] << ((i < (end_k - 1)) ? ", " : "");
        cout << "]" << endl;
        cout << "directly " << handle_now_energy << endl << endl;
    }

    // amount of spent energy if he divides the queue at this time
    ll left_plus_right_energy = 0;
    left_plus_right_energy += divide_and_conquer(a, start_q, middle_q, start_k, middle_k);
    left_plus_right_energy += divide_and_conquer(a, middle_q, end_q, middle_k, end_k);

    if (print_stuff) {
        cout << start_q << " " << end_q << "   " << start_k << " " << end_k << "  [";
        for (int i=start_k; i<end_k; i++) cout << a[i] << ((i < (end_k - 1)) ? ", " : "");
        cout << "]" << endl;
        cout << "divide " << left_plus_right_energy << endl << endl;
    }

    return min(handle_now_energy, left_plus_right_energy);
}


int main() {
    // get 4 first inputs
    cin >> n >> k >> A >> B;
    ll len_queue = (1 << n);
    vector<ll> k_people;

    // get k next inputs
    int person;
    for (int i=0; i<k; i++) {
        cin >> person; k_people.push_back(person-1);
    }

    // sort the k inputs
    sort(k_people.begin(), k_people.end());
    k_people.push_back(-1);

    ll ans = divide_and_conquer(k_people, 0, len_queue, 0, size(k_people)-1);

    cout << ans << endl;
    return 0;
}