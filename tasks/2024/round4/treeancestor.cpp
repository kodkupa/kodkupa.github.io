#include <iostream>
#include <vector>

using namespace std;

int n, k, ans[1000002];
vector<vector<int> > tree;
vector<int> vertexes;

void dfs(int parent, int node)
{
    vertexes.push_back(node);
    
    if((int) vertexes.size() > k)
        ans[node] = vertexes[(int) vertexes.size() - k - 1];
    for(int i = 0; i < (int) tree[node].size(); i++)
    {
        int nxt = tree[node][i];
        if(nxt == parent)
            continue;
        dfs(node, nxt);
    }
    vertexes.pop_back();
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> k;
    tree.resize(n);
    for(int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    
    for(int i = 0; i < n; i++)
        ans[i] = -1;
    
    dfs(-1, 0);
    
    for(int i = 0; i < n; i++)
        cout << ans[i] << " ";
    cout << '\n';
    return 0;
}
