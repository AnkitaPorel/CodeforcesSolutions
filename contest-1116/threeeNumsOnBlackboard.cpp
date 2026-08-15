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
        vector<int> a(3);

        cin >> a[0] >> a[1] >> a[2];

        sort(a.begin(), a.end());

        cout << min(a[1], a[2] - a[0]) << "\n";
    }
    
    return 0;
}