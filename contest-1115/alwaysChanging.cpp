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
        string s;
        cin >> n >> s;

        auto solve = [&](char start) -> long long {
            int numZeroDel = 0, numOneDel = 0;
            int f = -1, l = -1;
            int d = 0;

            for(int i = 0; i < n; i++)
            {
                char expected = (d % 2 == 0) ? start : (start == '0' ? '1' : '0');
                if(s[i] == expected)
                {
                    if(f == -1)
                        f = expected - '0';
                    else
                        l = expected - '0';
                    d++;
                }
                else if(s[i] == '0')
                    numZeroDel++;
                else
                    numOneDel++;
            }

            int extraZero = 0, extraOne = 0;

            if(start == '0')
            {
                if(f != -1)
                    extraZero++;
            }
            else
            {
                if( f != -1)
                    extraOne++;
            }

            if(l == 0)
                extraZero++;
            if(l == 1)
                extraOne++;

            long long ans = LLONG_MAX;

            if(abs(numZeroDel - numOneDel) <= 1)
                ans = min(ans, (long long)(numZeroDel + numOneDel));

            if(numZeroDel > numOneDel && numZeroDel - numOneDel - extraOne <= 1)
                ans = min(ans, (long long)(numZeroDel + numOneDel + extraOne));
            
            if(numOneDel > numZeroDel && numOneDel - numZeroDel - extraZero <= 1)
                ans = min(ans, (long long)(numOneDel + numZeroDel +extraZero));
        };

        long long a = solve('0');
        long long b = solve('1');
        long long ans = min(a, b);

        cout << (ans == LLONG_MAX ? -1 : ans) << "\n";
    }

    return 0;
}