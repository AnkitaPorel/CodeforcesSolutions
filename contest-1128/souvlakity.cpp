#include <iostream>
#include <string>

using namespace std;

int main()
{
    int t;
    cin >> t;

    while(t--)
    {
        int n;
        cin >> n;

        string s;
        cin >> s;

        int max_ele = INT_MIN, min_ele = INT_MAX;

        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            if(s[i] == '1')
            {
                max_ele = max(max_ele, i + 1);
                min_ele = min(min_ele, i + 1);

                cnt++;
            }
        }

        if (cnt == 1)
            cout << 0 << "\n";
        else if (cnt == 2)
            cout << 1 << "\n";
        else
            cout << max_ele - min_ele << "\n";
    }

    return 0;
}