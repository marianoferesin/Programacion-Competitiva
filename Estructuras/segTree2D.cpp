#include <bits/stdc++.h>
using namespace std;

//https://cses.fi/problemset/task/1739
typedef long long tint;
const int mxn = 1025, mxm = 1025;
struct Data{
	tint s;
	Data(tint _s=0){
		s = _s;
	}
	void merge(const Data& l,const Data& r){
		s = l.s+r.s;
	}
};
int vec[mxn][mxm];
struct segTree2D{
	int n,m; //1025
	Data st[2*mxn][2*mxm];
	void build(int _n,int _m){//O(n*m)
		n = _n;	m = _m;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				st[i+n][j+m] = vec[i][j];
		for(int i=0;i<n;i++)
			for(int j=m-1;j>=0;j--)
				st[i+n][j].merge(st[i+n][j<<1],st[i+n][j<<1|1]);
		for(int i=n-1;i>=0;i--)
			for(int j=0;j<2*m;j++)
				st[i][j].merge(st[i<<1][j],st[i<<1|1][j]);
	}
	void update(int x,int y,Data v){//O(logn*logm)
		st[x+n][y+m] = v;
		for(int j=y+m;j>1;j>>=1)
			st[x+n][j>>1].merge(st[x+n][j],st[x+n][j^1]);
		for(int i=x+n;i>1;i>>=1)
			for(int j=y+m;j>0;j>>=1)
				st[i>>1][j].merge(st[i][j],st[i^1][j]);
	}
	Data query(int x0,int y0,int x1,int y1){//O(logn*logm)
		// [x0,y0] , [x1+1,y1+1];
		Data ret = Data();
		for(int i0=x0+n,i1=x1+n; i0<i1 ;i0>>=1,i1>>=1){
			int t[4],q=0;
			if(i0&1) t[q++] = i0++;
			if(i1&1) t[q++] = --i1;
			for(int k=0;k<q;k++){
				for(int j0=y0+m, j1=y1+m; j0<j1; j0>>=1, j1>>=1){
					if(j0&1){
						ret.merge(ret, st[t[k]][j0++]);
					}
					if(j1&1){
						ret.merge(ret, st[t[k]][--j1]);
					}
				}
			}
		}
		return ret;
	}
};
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	segTree2D s;
	int n,q;
	while(cin>>n>>q){
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				cin>>vec[i][j];
		s.build(n,n);
		while(q--){
			int x,y,x2,y2;
			cin>>x>>y;
			s.update(x-1,y-1,Data(1));
			cin>>x>>y>>x2>>y2;
			cout<<s.query(x-1,y-1,x2,y2).s<<'\n';
		}
	}
	return 0;
}