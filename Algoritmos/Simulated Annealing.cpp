#include <bits/stdc++.h>
#define forr(i,a,b) for(int i=(a);i<(b);i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=n-1;i>=0;i--)
#define forall(it,v) for(auto it=v.begin();it!=v.end();it++)
#define sz(c) ((int)c.size())
#define rsz resize
#define pb push_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define fst first
#define snd second

#ifdef NANO
//local
#else
//judge
#endif

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef double T;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const T TIME_LIMIT = 1.99;
const T A = 0.9999;
T temp = 1e9;

T P(int old, int cand){
    if(old < cand) return 1.0;
    return exp((old-cand)/temp);
}


int main() {
	#ifdef NANO
		freopen("input.in", "r", stdin);
		//freopen("output.out","w", stdout);
	#endif
	
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	//FINDING MIN VAL IN ARRAY WITH SIMULATED ANNEALING
	
	std::uniform_real_distribution<double> unif(0, 1);
	
	int n;
	cin>>n;
	vector<int> v(n);
	forn(i,n) cin>>v[i];
	
	auto neighbour = [&](int x){
		if(n == 1) return 0;
		if(x == 0) return 1;
		if(x == n-1) return n-1;
		vector<int> aux = {1,-1};
		return x + aux[rng()%2];
	};
	
	int now =  rng() % n; // Take a random state
	int best = now;
	
	while (clock() / (double) CLOCKS_PER_SEC <= TIME_LIMIT){
		if(v[now] < v[best]) best = now;
		
		int next = neighbour(now);
		
		if(P(v[now], v[next]) >=  unif(rng)) now = next;
		
		temp *= A;
	}
	
	cout<<v[best]<<' '<<best<<endl;
	cout<<*min_element(v.begin(),v.end())<<endl;
	
	return 0;
}
