#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

// this function extracts the most number of groups with a fixed given size from teh 'cnt' array.
ll form_groups(ll group_size, vector<ll> cnt, int k) {
    ll numof_formed_groups = 0;
    for (int i=1; i<cnt.size(); i++) {
        // Shows the number of people to from the groups with age i and i-1.
        ll curr_available_people = cnt[i] + cnt[i-1];

        // Checking if we can form at least a full group of people using i and rem i - 1 people.
        if (curr_available_people >= group_size) {
            int most_numof_groups_to_form = curr_available_people / group_size;
            // add number of new groups to the count.
            numof_formed_groups += most_numof_groups_to_form;

            // remove the used people from their age count.
            int people_used_from_age_i_and_i_minus_one = (curr_available_people - (curr_available_people % group_size)); 
            int people_used_from_age_i = people_used_from_age_i_and_i_minus_one - cnt[i-1];

            /*
                the greedy choice is to pick as mush people as we can at each step.
                therefore cnt[i-1] is less than group_size. if not, it means we havn't pick enough in teh previous step.
                it's better to pick people first from cnt[i-1] to have the most possible cnt[i] for the next step .
            */
            cnt[i-1] = 0;
            cnt[i] -= people_used_from_age_i;
        }
    }
    return numof_formed_groups;
}

int main() {
    int t; cin >> t;
    vector<ll> answers;
    while (t--) {
        int n, k; cin >> n >> k;
        vector<ll> cnt (n+2, 0);
        ll sum = 0;
        for (int i=1; i<=n; i++) {
            cin >> cnt[i];
            sum += cnt[i];
        }

        /*
            We must check all the possible group sizes.
            smallest groups are of size 1.
            largest groups are of size (sum / k).
            so we'll perform a binary search on teh group sizes.
            for each group size:
                - if the number of formed groups is less than k, it means that we must use less group size to reach k groups.
                - if not, it means that we can possibly choose a larger group size.
            the final answer is in the 'left' variable.
        */
        ll l = 1, r = (sum / k) + 1;
        ll max_ans = -1;
        ll group_size;
        while (true) {
            if ((l+1) >= r) break;
            group_size = (l + r) / 2;
            ll numof_formed_groups = form_groups(group_size, cnt, k);
            if (numof_formed_groups >= k) {
                l = group_size;
            } else {
                r = group_size;
            }
        }

        answers.push_back(l * k);
    }
    for (int i=0; i<answers.size(); i++) {
        cout << answers[i] << endl;
    }
}