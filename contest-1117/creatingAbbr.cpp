#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    int t;

    cin >> t;

    while(t--)
    {
        int n, m;
        cin >> n >> m;

        vector<string> w(n), a(m);

        for(int i = 0; i < n; i++)
            cin >> w[i];
        for(int i = 0; i < m; i++)
            cin >> a[i];

        vector<int> mp(26);

        for(auto &s: w)
            mp[s[0] - 'a'] = 1;

        bool ok = 1;

        for(auto &s: a)
        {
            for(char &ch: s)
                ok &= mp[ch - 'A'];
        }

        cout << ((ok) ? "YES" : "NO") << "\n";
    }

    return 0;
}