#include <iostream>
#include <string>

using namespace std;
using ll = long long;

ll ext_gcd(ll m, ll n, ll &x, ll &y)
{
    if(n == 0)
    {
        x = 1;
        y = 0;
        return m;
    }

    ll x1, y1;

    ll g = ext_gcd(n, m % n, x1, y1);

    x = y1;

    y = x1 - (m / n) * y1;

    return g;
}

ll modinv(ll m, ll n)
{
    m %= n;

    if(m < 0)
        m += n;
    
    ll x, y;

    ext_gcd(m, n, x, y);

    x %= n;

    if(x < 0)
        x += n;

    return x;
}

int main()
{
    string image[805];

    string mode;

    cin >> mode;

    bool isFirst = (mode == "first");

    int t;
    cin >> t;

    while(t--)
    {
        int n;
        cin >> n;

        for(int i = 0; i < n; i++)
            cin >> image[i];

        int rx = 0, cx = 0;
        
        if(isFirst)
            cin >> rx >> cx;

        ll w = 0;

        for(int i = 0; i < n; i++)
            for(int j = 0; j < n ; j++)
                if(image[i][j] == '#')
                    w++;
        
        ll total = (ll)n * n;

        bool blackMinority = (w * 2 < total);

        ll m = blackMinority ? w : total - w;

        char markedChar = blackMinority ? '#' : '.';

        ll sumR = 0, sumC = 0;

        ll mm = m % n;

        ll minv = modinv(mm, n);

        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if(image[i][j] == markedChar)
                {
                    sumR += i;
                    sumC += j;
                }

        ll Rc = ((sumR % n) * minv) % n;
        ll Cc = ((sumC % n) * minv) % n;

        if(isFirst)
        {
            int xr0 = rx - 1, xc0 = cx - 1;
            ll diffR = ((xr0 - Rc) % n + n) % n;
            ll diffC = ((xc0 - Cc) % n + n) % n;

            ll Dr = (diffR * mm) % n;
            ll Dc = (diffC * mm) % n;

            if(Dr == 0 && Dc == 0)
                cout << "1 1 1 1\n";
            else
            {
                int pr = -1, pc = -1, qr = -1, qc = -1;
                for(int i = 0; i < n && pr == -1; i++)
                {
                    for(int j = 0; j < n; j++)
                    {
                        if(image[i][j] == markedChar)
                        {
                            int rr = (int)((i + Dr) % n);
                            int cc = (int)((j + Dc) % n);
                            if(image[rr][cc] != markedChar)
                            {
                                pr = i;
                                pc = j;
                                qr = rr;
                                qc = cc;
                                break;
                            }
                        }
                    }
                }
                cout << pr + 1 << ' ' << pc + 1 << ' ' << qr + 1 << ' ' << qc + 1 << "\n";
            }
        }
        else
            cout << Rc + 1 << ' ' << Cc + 1 << "\n";
    }

    return 0;
}