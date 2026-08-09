#include <climits>
#include <iostream>
#include <vector>

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

        if(n%2)
        {
            cout << "NO\n";

            continue;
        }

        int maxi = INT_MIN, mini = INT_MAX;

        for(int i = 0; i < n; i++)
        {
            if(i % 2)
                maxi = max(maxi, a[i]);
            else
                mini = min(mini, a[i]);
        }

        if(mini - maxi >= 2)
        {
            cout << "YES\n";
        }
        else
            cout << "NO\n";
    }

    return 0;
}