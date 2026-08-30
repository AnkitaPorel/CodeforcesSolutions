#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

int main()
{
    int t;
    cin >> t;

    while(t--)
    {
        ll s;
        int q;
        cin >> s >> q;

        vector<ll> factors;

        for(ll i = 1; i * i <= s; i++)
        {
            if(s % i == 0)
            {
                factors.push_back(i);
                if(i * i != s)
                    factors.push_back(s / i);
            }
        }

        int n = factors.size();

        sort(factors.begin(), factors.end());

        vector<ll> w(n), h(n), preWidth(n + 1, 0), preArea(n + 1, 0);

        for(int i = 0; i < n; i++)
        {
            w[i] = factors[i] - (i > 0 ? factors[i - 1] : 0);
            h[i] = s / factors[i];

            preWidth[i + 1] = preWidth[i] + w[i];
            preArea[i + 1] = preArea[i] + w[i] * h[i];
        }

        while(q--)
        {
            ll x, y;
            cin >> x >> y;

            int index = lower_bound(factors.begin(), factors.end(), x) - factors.begin();

            ll l = 0, r = index - 1, pos = -1;

            while(l <= r)
            {
                ll mid = (l + r) / 2ll;
                
                if(h[mid] >= y)
                {
                    pos = mid;
                    l = mid + 1;
                }
                else
                    r = mid - 1;
            }

            ll ans = preWidth[pos + 1] * y  + (preArea[index] - preArea[pos + 1]);

            ll prev = (index == 0 ? 0 : factors[index - 1]);

            ans += (x - prev) * min(h[index], y);

            cout << ans << "\n";
        }
    }

    return 0;
}