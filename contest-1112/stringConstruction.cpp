#include <iostream>
#include <string>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n, k;
        cin >> n >> k;
        if(k > n - 2)
        {
            cout << "-1\n";
            continue;
        }
        int diff = n - k - 2;

        int oneCount = n / 2;
        int zeroCount = n - oneCount;

        string ans;

        for(int i = 0; i < diff; i++)
        {
            if(i % 2)
            {
                ans += "1";
                oneCount--;
            }
            else
            {
                ans += "0";
                zeroCount--;
            }
        }

        if(diff % 2 == 0)
        {
            for(int i = 0; i < zeroCount; i++)
                ans += "0";
            for(int i = 0; i < oneCount; i++)
                ans += "1";
        }
        else
        {
            for(int i = 0; i < oneCount; i++)
                ans += "1";
            for(int i = 0; i < zeroCount; i++)
                ans += "0";
        }

        cout << ans << "\n";
    }

    return 0;
}