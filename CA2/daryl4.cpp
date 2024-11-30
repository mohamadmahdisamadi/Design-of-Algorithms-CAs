#include <iostream>
#include <vector>
using namespace std;

const int RICK = 0;
// it's been here for the previous problems, so why not now?
const int nuh_uh = 0;

int main() {
    int n; cin >> n;
    vector<int> v;

    // push back and push front 1 to the vector of values to ensure the boundary cases are handled
    v.push_back(1);
    for (int i=0; i<n; i++) {
        int value; cin >> value;
        v.push_back(value);
    }
    v.push_back(1);

    // by adding two 1's, the size of values increases by two
    int m = n+2;

    // dp[s][e] means the most values we can extract from s'th statue to the e'th one
    vector<vector<int>> dp (m, vector<int> (m, 0));
    
    /*
        the trick is to fill each dp based on little dp's that start and end within its range
        to do that, we need to fill each dp after all the smaller dp's are calculated
    */
    
    // note that the intervals are open-open
    for (int length=2; length<m; length++) {
    
        for (int start=0; start < (m - length); start++) {

            // calculate the end index by going forward from the start index by a step of length 
            int end = start + length;

            // 'mx' is the maximum value we can get from range (start, end)
            int mx = -1;

            for (int middle_ind=start+1; middle_ind < end; middle_ind++) {

                /*
                    assume we have solved the problem for ranges (start, middle_ind) and (middle_ind, end)
                    therefore all the statues are broken except for the middle_ind'th statue
                    the value we get is sum of these values:
                        1. value of the left interval.
                        2. value of breaking the middle_ind'th statue
                        3. value of the right interval.
                    we know that nearest statues to the middle_ind'th statue are the start'th and end'th statues
                    because all the other statues in between are already broken 
                */

                int daryl = v[start] * v[middle_ind] * v[end] + dp[start][middle_ind] + dp[middle_ind][end];

                // updating 'mx' if the new value is greater than its previous value
                if (daryl > mx) mx = daryl;
            }

            dp[start][end] = mx;
        
        }
    
    }

    // remember that the dp intervals are open-open
    // [1, v1, v2, ..., vn,   1]
    // [0,  1,  2, ...,  n, n+1]
    // therefore the answer for numbers from index 1 to index n is in dp[0][n+1]. we know that m = n+2 --> n+1 = m-1
    cout << dp[0][m-1] << endl;
    return RICK;
}