#include <bits/stdc++.h>
using namespace std;

struct DSU{
	vector<int> parent,size;
	int cantS;
	DSU(int n){
		cantS = n;
		parent.resize(n);
		size.resize(n,1);
		iota(parent.begin(),parent.end(),0);
	}
	int find(int x){//en que conjunto esta x
		if(x == parent[x])
			return x;
		return parent[x] = find(parent[x]);
	}
	bool same(int a,int b){//T - Si estan en el mismo conjunto
		return find(a)==find(b);
	}
	bool unite(int a,int b){//T - si estaban en la misma componente
		a = find(a);
		b = find(b);
		if(a==b)
			return true;
		cantS--;
		if(size[a]<size[b])
			swap(a,b);
		size[a] += size[b];
		parent[b] = a;
		return false;
	}
};

//https://codeforces.com/group/gXivUSZQpn/contest/336660/problem/M
int main(){
	int n;
	cin>>n;
	vector<string> v(n);
	DSU D(26);
	for(int i=0;i<n;i++){
		cin>>v[i];
		int m = v[i].size();
		for(int j=1;j<m;j++){
			D.unite(v[i][0]-'a',v[i][j]-'a');
		}
	}
	set<char> st;
	for(string s: v){
		st.insert(D.find(s[0]-'a'));
	}
	cout<<st.size()<<'\n';
	return 0;
}