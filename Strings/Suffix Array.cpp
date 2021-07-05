//Devuelve el suffix array del string s -- s[0] es el sufijo que empieza en '$'
// $ debe ser un caracter menor que cualquier otro caracter posible
//O(NlogN)
vector <int> suffix_array(string s){
	s.push_back('$');
	int n = s.size();
	
	vector <pair<char, int>> a;
	
	for(int i = 0; i<n; i++) a.push_back({s[i],i});
	sort(a.begin(),a.end());
	
	vector <int> p(n), c(n);
	for(int i = 0; i<n; i++) p[i] = a[i].second;
	c[0] = 0;
	for(int i = 1 ; i<n; i++)
		c[p[i]] = (a[i-1].first == a[i].first ) ? c[p[i-1]] : c[p[i-1]]+1;
	
	int k = 0;
	while((1<<k) < n){
		vector <pair<pair<int,int>,int>> a(n);
		int t = (1<<k);
		  
		for(int i = 0; i<n; i++)
			a[i] = {{c[ (p[i]-t+n)%n  ],c[ p[i] ]},(p[i]-t+n)%n };
		
		vector <int> count(n,0),pos(n);
		for(auto e: a) count[e.first.first]++;
		pos[0] = 0;
		for(int i = 1; i<n; i++) pos[i] = pos[i-1] + count[i-1];
	
		vector <pair<pair<int,int>,int>> aux(n);
		for(int i = 0; i<n; i++){
			aux[pos[a[i].first.first]] = a[i];
			pos[a[i].first.first]++;
		}
	
		for(int i = 0; i<n; i++)
			p[i] = aux[i].second;
		
		for(int i = 1 ; i<n; i++)
			c[p[i]] = (aux[i-1].first == aux[i].first ) ? c[p[i-1]] : c[p[i-1]]+1;		
		
		k++;
	}
	return p;
}
 
