#include <iostream>
#include <vector>

using namespace std;

void dfs(int cur, int par, vector<int> &dp, vector<vector<int>> &g)
{
    if(par != -1)
        dp[cur] = 1 + dp[par];
    
    for(auto &x:g[cur])
    {
        if(x == par)
            continue;
        dfs(x, cur, dp, g);
    }
}

int main()
{
    int t;
    cin >> t;

    while(t--)
    {
        int n;
        cin >> n;

        vector<vector<int>> g(n);

        for(int i = 1; i < n; i++)
        {
            int x;
            cin >> x;

            --x;
            g[i].push_back(x);
            g[x].push_back(i);
        }

        vector<int> dp(n);

        int m;
        cin >> m;

        vector<int> ans;
        for(int i = 0; i < m; i++)
        {
            int x;
            cin >> x;
            --x;
            ans.push_back(x);
        }

        dfs(0, -1, dp, g);

        int mn = ans.front();
        for(auto &x:ans)
        {
            if(dp[x] < dp[mn])
                mn = x;
        }

        cout << m - 1 << ' ';

        for(int x:ans)
        {
            if(x != mn)
                cout << x + 1 << ' ';
        }
        cout << "\n";
    }

    return 0;
}