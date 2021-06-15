vector<int> prefixFunction(const string &s){
	int n = s.size();
	vector<int> p(n);
	for (int i = 1; i < n; i++) {
		int borde = p[i - 1];
		while(borde>0 and s[i]!=s[borde])
			borde = p[borde - 1];
		p[i] = borde + (s[i] == s[borde]);
	}
	return p;
}
