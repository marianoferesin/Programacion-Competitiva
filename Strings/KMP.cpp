//Encontrar patron t en s (muestra indices)
void kmp(const string &s,const string &t){
	int n = s.size(),m = t.size();
	vector<int> v(m);
	//Preprocesamiento
	int i=1,j=0;
	while(i<m){
		if(t[i]==t[j]){
			v[i] = j+1;
			i++; j++;
		}
		else{
			if(j)
				j = v[j-1];
			else{
				v[i] = 0;
				i++;
			}
		}
	}
	//KMP
	i = 0; j = 0;
	while(i<n){
		if(s[i]==t[j])
			j++;
		else
			j = j ? v[j-1] : 0;
		i++;
		if(j==m){
			cout<<"ans: "<<i-m+1<<endl;//pos del patron
			j = 0;
		}
	}
}
