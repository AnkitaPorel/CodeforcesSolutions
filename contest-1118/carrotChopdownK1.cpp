#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n, m;
        cin >> n >> m;

        vector<int> arr(n);

        map<int, int> mp;

        for(int i = 0; i < n; i++)
        {
            cin >> arr[i];
            mp[arr[i]]++;
        }
        
        vector<int> cnt(m + 1);
        cnt[m] = mp[m];

        for(int i = m - 1; i >= 0; i--)
            cnt[i] = cnt[i+1] + mp[i];

        int ans = 0;

        for(int i = 1; i <= m; i++)
            ans = max(ans, cnt[i] + mp[2 * i]);

        cout << ans << "\n";
    }
    

    return 0;
}