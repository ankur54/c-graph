#include <bits/stdc++.h>
using namespace std;

int getMinVal(vector<int> ans, vector<bool> vis) {
    int minVal = INT_MAX, minIdx = -1, n = ans.size();
    for(int i = 0; i < n; i++)
        if(ans[i] <= minVal && !vis[i]) minVal = ans[i], minIdx = i;
    return minIdx;
}


int networkDelayTime(vector<vector<int>> &times, int n, int k) {
    unordered_map<int, vector<pair<int, int>>> graph;
    for(auto x : times) graph[x[0]].push_back({x[1], x[2]});

    vector<int> ans(n + 1, INT_MAX);
    vector<bool> vis(n + 1, false);
    ans[k] = 0;

    for(int i = 0; i < n; i++) {
        int node = getMinVal(ans, vis);
        vis[node] = true;
        for(auto nei : graph[node]) 
            if(!vis[nei.first] && ans[node] != INT_MAX) 
                ans[nei.first] = min(ans[nei.first], ans[node] + nei.second);
    }

    int res = INT_MIN;
    for(int i = 1; i <= n; i++) res = max(res, ans[i]);
    return res;
}


int main(int argc, char const *argv[])
{
    int e, n, k;
    cin >> e;
    vector<vector<int>> edges(e, vector<int>(3, 0));
    for(int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
    }
    cin >> n >> k;
    cout << networkDelayTime(edges, n, k) << endl;
    return 0;
}
