#include <iostream>
#include <vector>
#include <algorithm>

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
        for(int i = 0; i < n; i++)
            cin >> a[i];
        
        int max_ele = *max_element(a.begin(), a.end());

        int ans = max_ele;
        
        for (auto it : a)
        {
            if (it < max_ele)
            {
                int bit = 31 - __builtin_clz(it ^ max_ele);
                ans = max(ans, max_ele | (1 << (bit + 1)) - 1);
            }
        }

        cout << ans << "\n";
    }

    return 0;
}