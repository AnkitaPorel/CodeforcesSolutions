#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    int t;

    cin >> t;

    vector<string> patterns = {"0011", "0110", "1001", "1100"};

    while(t--)
    {
        int n;

        cin >> n;

        string s;

        cin >> s;

        int cnt = 0;

        for(auto &it:patterns)
        {
            bool flag = true;
            for(int i = 0; i < n; i++)
            {
                if(s[i] != '?' && s[i] != it[i % 4])
                {
                    flag = false;
                    break;
                }
            }

            if(flag)
                cnt++;
        }

        cout << cnt << "\n";
    }

    return 0;
}