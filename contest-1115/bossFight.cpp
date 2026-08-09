#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main()
{
    int t;
    cin >> t;

    while(t--)
    {
        int n;
        cin >> n;

        vector<int> a(n);

        int ans = 0;

        unordered_map<int,int> mp;

        for(int i=0;i<n;i++)
        {
            cin >> a[i];
            ans += a[i];
            mp[a[i]]++;
        }
        int fmax = 0, mx = 0;
        for(auto &it: mp)
        {
            if(it.second > fmax)
            {
                fmax = it.second;
                mx = it.first;
            }
        }

        if(fmax > n - fmax)
        {
            int res = max(0, fmax - (n - fmax) -2);

            res *= mx;

            ans -= res;
        }

        cout << ans <<"\n";
    }

    return 0;
}