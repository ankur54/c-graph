#include <bits/stdc++.h>
using namespace std;

vector<int> shortestAlternatingPaths(int n, vector<vector<int>> red_edges, vector<vector<int>> blue_edges) {
    vector<vector<vector<int>>> graph(2, vector<vector<int>>(n));
    for(auto r: red_edges) graph[0][r[0]].push_back(r[1]);
    for(auto b: blue_edges) graph[1][b[0]].push_back(b[1]);

    vector<vector<int>> ans(2, vector<int>(n, 2*n));
    ans[0][0] = ans[1][0] = 0;
    queue<pair<int, int>> q;
    q.push({0, 0});
    q.push({0, 1});

    while(!q.empty()) {
        int node = q.front().first;
        int color = q.front().second;
        for(auto neigh : graph[color ^ 1][node]) {
            if(ans[neigh][color ^ 1] == n*2) {
                ans[neigh][color ^ 1] = ans[node][color] + 1;
                q.push({neigh, color ^ 1});
            }
        }
        q.pop();
    }

    vector<int> res(n);
    for(int i = 0; i < n; i++) {
        int temp = min(ans[0][i], ans[1][i]);
        res[i] = (temp == n*2) ? -1 : temp;
    }
    return res;
}

int main(int argc, char const *argv[])
{
    
    return 0;
}
