#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    int t;
    cin >> t;
    
    while(t--)
    {
        int n, k;
        cin >> n >> k;

        string s;

        cin >> s;

        int totalPlayers = 2 * n;

        vector<int> arr(totalPlayers, 0);

        if(k == 0)
        {
            for(int i = 0; i < totalPlayers; i++)
                arr[i] = s[i] - '0';
        }
        else
        {
            for(int i = 0; i < totalPlayers; i++)
            {
                if(s[i] == '1')
                {
                    int idx = (i + 1) % totalPlayers;

                    if(s[idx] == '0')
                        arr[idx] = 1;
                    else
                        arr[i] = 1;
                }
            }
        }

        int redTeam = 0, blueTeam = 0;

        for(int i = 0; i < totalPlayers; i++)
        {
            if(arr[i] == 1)
            {
                if((i + 1) % 2 == 0)
                    redTeam++;
                else
                    blueTeam++;
            }
        }

        cout << redTeam << " " << blueTeam << "\n";
    }

    return 0;
}