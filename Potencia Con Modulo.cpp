const int mod = 1000000007;
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
