const int a = 100'000'081;
const int mod = 400000091; 
int h[400'000'100]; // suma de hashings
int pota[100'0100]; //potencias de a en mod
int inv[100'0100]; //inversos de las potencias de a

//necesario para calcular los inversos de las potencias de a
long long pot(long long b,long long e){
    if(e==0)
        return 1;
    else{
        if(e&1){
            return (b* pot(b,e-1))%mod;
        }
        else{
            long long aux = pot(b,e/2);
            return (aux*aux)%mod;
        }
    }
}
 
 
int get(int l,int r){
	if(l==0) return h[r]; 
	return ((long long)(h[r] - h[l-1] + mod)%mod * (long long)inv[l])%mod;
}

//preprocesamiento

	//llamar al string s
	int n = s.size();

	//potencias de a
	pota[0] = 1;
	for(int i = 1; i<1000'005; i++) 
		pota[i] = ((long long)pota[i-1] * (long long)a)%mod;

	//inversos de las potencias de a
	forn(i,100'0005) inv[i] = pot(pota[i],mod-2);

	//hashing en rangos
	h[0] = (int)s[0];
	for(int i = 1; i<n; i++)
		h[i] = ((long long)h[i-1] + (long long)(pota[i] * (long long)s[i])%mod)%mod;
