#include <iostream>
#include <string>
using namespace std;
char grille[4][10][10];
int n;
bool vis[10][10];
char ans[10][10];
string s;

int numhole=0;

int main()
{
    cin >> n;
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
        {
            cin >> grille[0][i][j];
            if (grille[0][i][j]=='.')
                numhole++;
        }
    cin >> s;
    if (n%2!=0)
    {cout << "invalid grille" << endl;
        return 0;
        
    }
    if (4*numhole!=n*n)
    {
        cout << "invalid grille" << endl;
        return 0;}
    for (int k=1; k<4; k++)
    {
        for (int i=0; i<n; i++)
        {for (int j=0; j<n; j++)
        {
            grille[k][i][j]=grille[k-1][n-1-j][i];
            //cout << grille[k][i][j];
        }
            //cout << endl;
        }
        //cout << endl;
    }
    int cnt=0;
    for (int k=0; k<4; k++)
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
            {
                if (grille[k][i][j]=='.')
                {
                    ans[i][j]=s[cnt];
                    cnt++;
                    vis[i][j]=true;
                    //if (cnt>=s.length())
                        //cnt--;
                }
            }
    
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            if (vis[i][j]==false)
            {
                cout << "invalid grille" << endl;
                return 0;
            }
    
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            cout << ans[i][j];
    cout << endl;
                
}