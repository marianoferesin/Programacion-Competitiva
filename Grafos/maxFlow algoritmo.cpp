#include <bits/stdc++.h>
using namespace std;
 
typedef long long tint;
vector<vector<int>> g;
vector<vector<tint>> cap;
vector<int> p;
int n,m;
tint bfs(int source,int sink){
	p.assign(n,-1);
	p[source] = source;
	queue<pair<int,tint>> q;
	q.push({source,1e18+7});
	while(q.size()){
		int u = q.front().first;
		tint flow = q.front().second;
		q.pop();
		for(int y: g[u]){
			if(p[y]==-1 and cap[u][y]){
				p[y] = u;
				tint newFlow = min(flow,cap[u][y]);
				if(y == sink)
					return newFlow;
				q.push({y,newFlow});
			}
		}
	}
	return 0;
}
tint maxFlow(int source,int sink){
	tint maxFlow=0,newFlow;
	while((newFlow = bfs(source,sink))){
		maxFlow += newFlow;
		int u = sink;
		while(u != source){
			int y = p[u];
			cap[y][u] -= newFlow;
			cap[u][y] += newFlow;
			u = y;
		}
	}
	return maxFlow;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>m;
	g.resize(n);
	cap.assign(n,vector<tint>(n));
	for(int i=0;i<m;i++){
		int a,b;
		tint w;
		cin>>a>>b>>w;
		a--;b--;
		if(cap[a][b]==0){
			cap[a][b] = w;
			//cap[b][a] = 0;
			g[a].push_back(b);
			g[b].push_back(a);	
		}
		else
			cap[a][b] += w;
	}
	tint ans = maxFlow(0,n-1);
	cout<<ans<<endl;
	return 0;
}