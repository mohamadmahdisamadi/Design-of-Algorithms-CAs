#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

const int RICK = 0;
const int nuh_uh = 0;

/*
    i submited the same code with small changes over and over and each time the result got a little better but never 100.
    so i asked copilot what could possibly be wrong and it said to check cases of high n, m and k values.
    when i checked some of them, i saw some strange things like negative or more than one probabilities.
    so i thought it might be because of underflowing or sth.
    that's why i check if the probs are less than zero or higher than one at the end of the code.
*/

int main() {
    int n, m, k; cin >> n >> m >> k;

    /*
        this is a tricky case. when 'm' is zero, no matter how many times we roll the dice, every single result is within the range of [m, n]
        we know than 'n' isn't less than 'm' and teh elsesection is useless. but what's the harm?
    */
    if (m == 0) {
        if (n >= 0) {
            cout << 1 << endl;
            return RICK;;
        } else {
            cout << 0 << endl;
            return RICK;
        }
    }

    // dp[i] is the probability of having sum 'i' at some point.
    vector<double> dp(n+1);

    // base case: there is a one hundred percent chance that we have a 0 sum at some point (the starting point)
    dp[0] = (double)1;

    // 'ws' is window sum that stores sum of probabilities of the last k states.
    double ws = dp[0];

    for (int sum=1; sum <= n; sum++) {
        /*
            dp[sum] is sum of all its k existing previous probs.
            the 1/k term is because we roll teh dice one more time to get here.
        */
        dp[sum] = ws / double(k);
        if (dp[sum] < 0) dp[sum] = 0.0;

        // if sum exceeds 'm', the game is over and it cannot be used in further dice rollings.
        if (sum < m)  ws += dp[sum];

        // is dp[sum-k] exists and was already added to teh window sum, it must be removed now because the window sum cannot contain probs farther than 'k' steps
        if (sum >= k) ws -= dp[sum - k];
        if (ws < 0) ws = 0.0;
    }

    double sum = 0;
    for (int i=m; i<=n; i++) {
        sum += dp[i];
    }

    if (sum > 1) sum = 1.0;

    cout << sum << endl;
    return RICK;
}