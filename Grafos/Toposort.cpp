//topological sort -- detecta ciclos :D
int n; // number of vertices
vector<vector<int>> adj; // adjacency list of graph
vector<int> color; //visited->0 - on stack->1 - ready->2
vector<int> ans;

bool dfs(int v) {
    bool acyclic = true;
    color[v] = 1;
    for (int u : adj[v]) {
	if (color[u]==1) return false; // has a cycle
        if (color[u]==0)
            acyclic = min(dfs(u), acyclic);
    }
    color[v] = 2;
    ans.push_back(v);
    return acyclic;
}

bool topological_sort() { //false if there is a cylcle otherwise toposort is in ans
    color.assign(n, 0);
    ans.clear();
    bool acyclic = true;
    for (int i = 0; i < n; ++i) {
        if (color[i]==0)
            acyclic = min(dfs(i),acyclic);
    }
    reverse(ans.begin(), ans.end());
    return acyclic;
}
