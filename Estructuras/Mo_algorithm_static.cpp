#include <bits/stdc++.h>
using namespace std;

const int bloque = 500; //sqrt(n) aprox
int n,q;
struct Query{// [l,r)
	int l,r,i;
	bool operator<(const Query &o) const{
		if (l/bloque != o.l/bloque)
			return l<o.l;
		return (l/bloque) & 1 ? (r < o.r) : (r > o.r);
	}
};
struct Data{
	int freq[200000]={};
	int cant;
	Data(){ cant = 0; }
};
vector<Query> queries;
vector<int> v;
void add(Data& data,int id){
	if(++data.freq[v[id]]==1)
		data.cant++;
}
void remove(Data& data,int id){
	if(--data.freq[v[id]]==0)
		data.cant--;
}
int getAns(Data& data){
	return data.cant;
}
void mo(){
	vector<int> ans(q);
	int l=0,r=0;
	Data data;
	sort(queries.begin(),queries.end());
	for(const Query& query: queries){
		while(l>query.l) add(data,--l);
		while(r<query.r) add(data,r++);
		while(l<query.l) remove(data,l++);
		while(r>query.r) remove(data,--r);
		ans[query.i] = getAns(data);
	}
	for(int x: ans)
		cout<<x<<'\n';
}
//Ejemplo Mo's Algorithm para https://cses.fi/problemset/task/1734/
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>q;
	v.resize(n);
	queries.resize(q);
	map<int,int> mp;//index compression
	int aux = 0;
	for(int i=0;i<n;i++){
		cin>>v[i];
		if(mp.count(v[i]))
			v[i] = mp[v[i]];
		else{
			mp[v[i]] = aux;
			v[i] = aux++;
		}
	}
	for(int i=0;i<q;i++){
		cin>>queries[i].l>>queries[i].r;
		queries[i].l--;queries[i].i = i;
	}
	mo();
	return 0;
}