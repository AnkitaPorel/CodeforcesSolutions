#include <iostream>
#include <string>
#include <vector>

using namespace std;
using ll = long long;

const ll MOD = 998244353;

ll binexpo(ll a, ll b, ll mod = MOD)
{
    ll res = 1;
    a %= mod;

    while(b)
    {
        if(b & 1)
            res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }

    return res;
}

class Comb {
public:
    vector<ll> fact, ifact;

    ll mod;

    Comb(int n, ll mod = MOD) : mod(mod)
    {
        fact.assign(n + 1, 1);
        ifact.assign(n + 1, 1);

        for(int i = 1; i <= n; i++)
            fact[i] = fact[i - 1] * i % mod;
        
        ifact[n] = binexpo(fact[n], mod - 2, mod);

        for(int i = n; i > 0; i--)
            ifact[i - 1] = ifact[i] * i % mod;
    }

    ll nCr(ll n, ll r)
    {
        if(r > n || r < 0)
            return 0;
        return fact[n] * ifact[r] % mod * ifact[n - r] % mod;
    }
};

int main()
{
    Comb comb(1000005);

    int t;
    cin >> t;

    while(t--)
    {
        int n;
        cin >> n;

        string s;
        cin >> s;

        ll zeros = 0, ones = 0;
        ll seg0 = 0, seg1 = 0;

        for(int i = 0; i < n; i++)
        {
            if(s[i] == '0')
            {
                zeros++;

                if(i == 0 || s[i-1] != '0')
                    seg0++;
            }
            else
            {
                ones++;

                if(i == 0 || s[i-1] != '1')
                    seg1++;
            }
        }

        ll ways0 = (seg0 > 0)? comb.nCr(zeros - 1, seg0 - 1) : 1;
        ll ways1 = (seg1 > 0)? comb.nCr(ones - 1, seg1 - 1) : 1;

        ll ans = (ways0 * ways1) % MOD;

        cout << ans << "\n";
    }

    return 0;
}