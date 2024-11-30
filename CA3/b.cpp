#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

string ch2s(char ch) {
    return (ch == 'H') ? "H" : "P";
}

int main() {
    int t; cin >> t;
    string ans;
    while (t--) {
        int H, P, HP, PH; cin >> H >> P >> HP >> PH;
        string s; cin >> s;

        if ((H + P + 2*HP + 2*PH) != s.length()) {
            ans += "NO\n";
            continue;
        }

        int PH_cnt = 0, HP_cnt = 0, P_cnt = 0, H_cnt = 0;

        string prev = ch2s(s[0]);
        if (s[0] == 'P') P_cnt++;
        else H_cnt++;

        for (int i=1; i<s.length(); i++) {
            prev += ch2s(s[i]);
            if (prev == "PH") PH_cnt++;
            if (prev == "HP") HP_cnt++;

            if (s[i] == 'P') P_cnt++;
            else H_cnt++;

            prev = "";
            prev += s[i];
        }

        int total_H = H + HP + PH, total_P = P + PH + HP;

        if ((H_cnt != total_H) || (P_cnt != total_P)) {
            ans += "NO\n";
            continue;
        }

        if ((HP_cnt < HP) || (PH_cnt < PH)) {
            ans += "NO\n";
            continue;
        }
    
        int rem_HP = HP - min(HP_cnt, HP);
        int rem_PH = PH - min(PH_cnt, PH);

        if ((rem_HP > 0) || (rem_PH > 0)) {
            ans += "NO\n";
            continue;
        }
        
        ans += "YES\n";

    }
    cout << ans;
}
    
    
    
