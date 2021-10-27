#include <bits/stdc++.h>
using namespace std;

typedef long long tint;
const int mxn = 1<<20;
struct Data{
	tint s;
	Data(tint _s=0){
		s = _s;
	}
	void merge(const Data& l,const Data& r){
		s = l.s+r.s;
	}
};
struct segTree{
	Data data[2*mxn];
	int n;
	Data* init(const int m){
		n = 1<<(32-__builtin_clz(m));
		for(int i=0;i<2*n;i++){
			data[i] = Data();
		}
		return (data+n);
	}
	void build(){
		for(int i=n-1;i>0;i--){
			data[i].merge(data[2*i],data[2*i+1]);
		}
	}
	void update(int pos,const Data& w){update(pos,w,0,n-1,1);}
	void update(int pos,const Data& w,int l,int r,int k){
		if(l==r){
			data[k] = w;
			//data[k].merge(data[k],w);
		}
		else{
			int medio = (l+r)/2;
			if(pos<=medio)
				update(pos,w,l,medio,2*k);
			else
				update(pos,w,medio+1,r,2*k+1);
			data[k].merge(data[2*k],data[2*k+1]);
		}
	}
	Data query(int a,int b){return query(a,b,1,0,n-1);}
	Data query(int a,int b,int k,int l,int r){
		//[l,r] es el rango actual, [a,b] es la query, k posicion del vector
		if(r<a or l>b)
			return Data();
		if(a<=l and r<=b)
			return data[k];
		int medio = (l+r)/2;
		Data ret = Data();
		ret.merge(query(a,b,2*k,l,medio),query(a,b,2*k+1,medio+1,r));
		return ret;
	}
};

//https://cses.fi/problemset/task/1648/
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n,q;
	cin>>n>>q;
	segTree t;
	Data *p = t.init(n);
	for(int i=0;i<n;i++){
		cin>>p[i].s;
	}
	t.build();
	while(q--){
		int a,b,c;
		cin>>a>>b>>c;
		if(a==1){
			t.update(b-1,Data(c));
		}
		else{
			cout<<t.query(b-1,c-1).s<<'\n';
		}
	}
	return 0;
}