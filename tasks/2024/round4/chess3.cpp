#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    for(; t; t--)
    {
        char mat[9][9];
        for(int i = 0; i <= 7; i++)
            for(int j = 0; j <= 7; j++)
                cin >> mat[i][j];
        
        bool underThreat = 0;
        for(int i = 0; i <= 7; i++)
            for(int j = 0; j <= 7; j++)
            {
                if(mat[i][j] == 'P') // pawn
                {
                    if(j > 0 && i > 0 && mat[i-1][j-1] == 'q')
                        underThreat = 1;
                    if(j < 7 && i > 0 && mat[i-1][j+1] == 'q')
                        underThreat = 1;
                }
                if(mat[i][j] == 'N') // knight
                {
                    for(int dirx = -2; dirx <= 2; dirx++)
                        for(int diry = -2; diry <= 2; diry++)
                        {
                            if(abs(dirx) + abs(diry) == 3)
                            {
                                if(i + dirx >= 0 && i + dirx <= 7 && j + diry >= 0 && j + diry <= 7)
                                {
                                    if(mat[i + dirx][j + diry] == 'q')
                                        underThreat = 1;
                                }
                            }
                        }
                }
                if(mat[i][j] == 'B' || mat[i][j] == 'Q') // bishop or queen
                {
                    for(int dirx = -1; dirx <= 1; dirx++)
                        for(int diry = -1; diry <= 1; diry++)
                        {
                            if(abs(dirx) + abs(diry) == 2)
                            {
                                int xa = i + dirx;
                                int ya = j + diry;
                                while(xa >= 0 && xa <= 7 && ya >= 0 && ya <= 7)
                                {
                                    if(mat[xa][ya] == 'q')
                                    {
                                        underThreat = 1;
                                        break;
                                    }
                                    if(mat[xa][ya] != '.')
                                        break;
                                    xa += dirx;
                                    ya += diry;
                                }
                            }
                        }
                }
                if(mat[i][j] == 'R' || mat[i][j] == 'Q') // rook or queen
                {
                    for(int dirx = -1; dirx <= 1; dirx++)
                        for(int diry = -1; diry <= 1; diry++)
                        {
                            if(abs(dirx) + abs(diry) == 1)
                            {
                                int xa = i + dirx;
                                int ya = j + diry;
                                while(xa >= 0 && xa <= 7 && ya >= 0 && ya <= 7)
                                {
                                    if(mat[xa][ya] == 'q')
                                    {
                                        underThreat = 1;
                                        break;
                                    }
                                    if(mat[xa][ya] != '.')
                                        break;
                                    xa += dirx;
                                    ya += diry;
                                }
                            }
                        }
                }
            }
        if(underThreat)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}

