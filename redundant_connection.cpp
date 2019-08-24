#include <bits/stdc++.h>
using namespace std;

typedef struct node {
    int rank, parent;
} subset;

int find(vector<subset> &subsets, int x) {
    if(subsets[x].parent != x) subsets[x].parent = find(subsets, subsets[x].parent);
    return subsets[x].parent;
}

void Union(vector<subset> &subsets, int i, int j) {
    int parent_i = find(subsets, i);
    int parent_j = find(subsets, j);
    
    if(subsets[parent_i].rank > subsets[parent_j].rank) subsets[parent_j].parent = parent_i;
    else if(subsets[parent_i].rank < subsets[parent_j].rank) subsets[parent_i].parent = parent_j;
    else {
        subsets[parent_j].parent = parent_i;
        subsets[parent_i].rank++;
    }

    find(subsets, i);
    find(subsets, j);
}

vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    int n = edges.size();
    vector<subset> subsets(n + 1);
    vector<int> ans = {};
    
    for(int i = 0; i <= n; i++) subsets[i] = {0, i};
    vector<int> vis(n + 1, 0);
    for(auto x:edges) {
        if(!vis[x[0]] || !vis[x[1]]) vis[x[0]] = vis[x[1]] = 1;
        // cout << x[0] << ": " << subsets[x[0]].parent << ", " << x[1] << ": " << subsets[x[1]].parent << endl;
        if(find(subsets, x[0]) != find(subsets, x[1])) Union(subsets, x[0], x[1]);
        else ans = x;
        // cout << x[0] << ": " << subsets[x[0]].parent << ", " << x[1] << ": " << subsets[x[1]].parent << endl;
    }
    return ans;
}

int main(int argc, char const *argv[])
{
    int e;
    cin >> e;
    vector<vector<int>> edges(e, vector<int>(2, 0));
    for(int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        edges[i] = {u, v};
    }

    vector<int> ans = findRedundantConnection(edges);
    cout << ans[0] << " " << ans[1] << endl;
    return 0;
}
