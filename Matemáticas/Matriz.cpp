#include <bits/stdc++.h>
using namespace std;

typedef long long tint;
const int mod = 1e9+7;
struct Matriz{
	int n,m;
	vector<vector<tint>> v;
	Matriz(int _n,int _m){ n = _n; m = _m; v.assign(n,vector<tint>(m)); }
	Matriz(const vector<vector<tint>> &_v) { n = _v.size(); m = n?_v[0].size():0; v = _v; }
	Matriz operator+(const Matriz& o){ assert(n==o.n and m==o.m);
		Matriz ret = Matriz(n,m);
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				ret[i][j] = (v[i][j]+o.v[i][j])%mod;
		return ret;
	}
	Matriz operator-(const Matriz& o){ assert(n==o.n and m==o.m);
		Matriz ret = Matriz(n,m);
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				ret[i][j] = (v[i][j]-o.v[i][j]+mod)%mod;
		return ret;
	}
	Matriz operator*(const Matriz& o){ assert(m==o.n);
		Matriz ret = Matriz(n,o.m);
		for(int i=0;i<n;i++)
			for(int j=0;j<o.m;j++)
				for(int k=0;k<m;k++)
					ret[i][j] = (ret.v[i][j]+v[i][k]*o.v[k][j]%mod)%mod;
		return ret;
	}
	void pot(tint k){ assert(n==m);
		Matriz ret = Matriz(n,n),aux = v;
		ret.identidad();
		while(k){
			if(k&1)
				ret = ret*aux;
			aux = aux*aux;
			k >>= 1;
		}
		*this = ret;
	}
	void identidad(){ assert(n==m);
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				v[i][j] = i==j;
	}
	vector<tint>& operator[](int i){ return v[i]; }
	bool operator==(const Matriz& o){ return v == o.v; }
  	bool operator!=(const Matriz& o){ return v != o.v; }
};

int main() {
	//https://cses.fi/problemset/result/3051595/
	ios::sync_with_stdio(false);
	cin.tie(0);
	vector<vector<tint>> aux={{1,1},{1,0}};
	vector<vector<tint>> aux2={{1},{0}};
	Matriz m(aux),v0(aux2);
	tint n;
	cin>>n;
	if(n==0)
		cout<<0<<'\n';
	else{
		m.pot(n);
		Matriz ans = m*v0;
		cout<<ans[1][0]<<'\n';
	}
	return 0;
}