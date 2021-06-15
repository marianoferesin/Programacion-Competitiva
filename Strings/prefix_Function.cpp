// p[i] es el tamaño del mayor prefijo s[0..i] que empieza en el substring i.
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
