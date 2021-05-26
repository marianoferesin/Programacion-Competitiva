#include <bits/stdc++.h>
#define forn(i,n) for(int i = 0; i<n; i++)
using namespace std;

int main(int argc, char *argv[]) {
	
	int a[2] = {1,2};
	
	auto [x,y] = a; // creates e[2], copies a into e, then x refers to e[0], y refers to e[1]
	auto& [xr, yr] = a; // xr refers to a[0], yr refers to a[1]
	
	
	cout<<x<<y<<endl;
	return 0;
}



