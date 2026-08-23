#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int t;
    cin >> t;

    while(t--)
    {
        int n, m;
        cin >> n >> m;

        vector<int> a(n), b(m);

        for(int i = 0; i < n; i++)
            cin >> a[i];
        for(int i = 0; i < m; i++)
            cin >> b[i];

        int bea = 0, ver = 0;

        for(int i = 0; i < n - 1; i++)
            bea += (a[i] - a[i + 1] + 1);
        
        bea += a[n - 1];

        for(int i = 0; i < m - 1; i++)
            ver += (b[i] - b[i + 1] + 1);

        ver += b[m - 1];

        cout << (bea >= ver ? 1 : 2) << "\n";
    }

    return 0;
}