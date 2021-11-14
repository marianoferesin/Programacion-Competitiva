#include <bits/stdc++.h>
using namespace std;

typedef long long tint;
int LIS(vector<int> &v){
	int n = v.size();
	vector<int> w;
	for(int i=0;i<n;i++){
		auto it = lower_bound(w.begin(),w.end(),v[i]);
		if(it==w.end())
			w.push_back(v[i]);
		else
			*it = v[i];
	}
	return w.size();
}
//https://www.beecrowd.com.br/judge/es/problems/view/2919
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	while(cin>>n){
		vector<int> v(n);
		for(int i=0;i<n;i++){
			cin>>v[i];
		}
		cout<<LIS(v)<<'\n';
	}
	return 0;
}