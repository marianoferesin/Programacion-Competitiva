// Crear hashing de la siguiente manera DobleHash hash_s(s);
// get() funciona de la manera [l,r]
unsigned long long pott(unsigned long long b,unsigned long long e, unsigned long long mod){
    if(e==0)
        return 1;
    else{
        if(e&1){
            return (b* pott(b,e-1,mod))%mod;
        }
        else{
            unsigned long long aux = pott(b,e/2,mod);
            return (aux*aux)%mod;
        }
    }
}

struct DobleHash{
	string s;
	int n;
	const static unsigned long long A = 131,B = 400'000'091,C = 53,D = 100'000'081;
	
	vector <unsigned long long> h_0_31;
	vector <unsigned long long> h_32_63;
	vector <unsigned long long> pot_A; //Inicializar con n;
	vector <unsigned long long> pot_C;
	vector <unsigned long long> inv_pot_A;
	vector <unsigned long long> inv_pot_C;
	
	DobleHash() {}
	
	DobleHash(string aux) : s{aux} {
		n = s.size();
		h_0_31.resize(n+20);
		h_32_63.resize(n+20);
		pot_A.resize(n+20);
		pot_C.resize(n+20);
		inv_pot_A.resize(n+20);
		inv_pot_C.resize(n+20);
		
		pot_A[0] = 1;
		for(int i = 1; i<n+10; i++) pot_A[i] = (pot_A[i-1] * A)%B;
		
		pot_C[0] = 1;
		for(int i = 1; i<n+10; i++) pot_C[i] = (pot_C[i-1] * C)%D;
	
		for(int i = 0; i<n+10; i++) inv_pot_A[i] = pott(pot_A[i],B-2,B);
		
		for(int i = 0; i<n+10; i++) inv_pot_C[i] = pott(pot_C[i],D-2,D);
		
		h_0_31[0] = s[0]%B;
		for(int i = 1; i<n; i++) h_0_31[i] = (h_0_31[i-1] + ( pot_A[i] * s[i] )%B )%B;
		
		h_32_63[0] = s[0]%D;
		for(int i = 1; i<n; i++) h_32_63[i] = (h_32_63[i-1] + ( pot_C[i] * s[i] )%D )%D;
	}
	
	unsigned long long get(int l, int r){
		if(l==0)
			return ((h_32_63[r] << 32LL) | h_0_31[r]);
		
		unsigned long long p_0_31 = (((h_0_31[r] - h_0_31[l-1] + B)%B) * inv_pot_A[l])%B;
		 
		unsigned long long p_32_63 = (((h_32_63[r] - h_32_63[l-1] + D)%D) * inv_pot_C[l])%D; 
	
		return ((p_32_63 << 32LL) | p_0_31);
	}
	
};
