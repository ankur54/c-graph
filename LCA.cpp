#include <bits/stdc++.h>
using namespace std;

int findLowestCommonAncestor(int n, vector<int> tree[], int u, int v) {
    vector<vector<int>> parent(n, vector<int>(32, -1));
    vector<bool> vis(n, false);
    vector<int> depth(n, 0);

    function<void(int)> dfs = [&] (int node) {
        vis[node] = true;
        for(int nei : tree[node]) {
            if(!vis[nei]) {
                parent[nei][0] = node;
                depth[nei] = depth[node] + 1;
                dfs(nei);
            }
        }
    };

    dfs(0);
    for(int j = 1; j < 31; j++)
        for(int i = 0; i < n; i++) 
            parent[i][j] = (parent[i][j - 1] != -1) ? parent[parent[i][j - 1]][j - 1] : -1;
    

    auto lca = [&] () {
        if(depth[u] < depth[v]) u = u^v, v = u^v, u = u^v;
        int diff = depth[u] - depth[v];
        for(int i = 0; i < 32; i++) 
            if((diff >> i)&1) u = parent[u][i];
        
        if(u == v) return u;

        for(int i = 31; i >= 0; i--) 
            if(parent[u][i] != parent[v][i]) u = parent[u][i], v = parent[v][i];
        
        return parent[u][0];
    };

    return lca();
}

int main(int argc, char const *argv[])
{
    int e;
    cin >> e;
    vector<int> tree[e + 1];
    for(int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        tree[u - 1].push_back(v - 1);
        tree[v - 1].push_back(u - 1);
    }

    int x, y;
    cin >> x >> y;
    cout << findLowestCommonAncestor(e + 1, tree, x - 1, y - 1) + 1 << endl;
    return 0;
}