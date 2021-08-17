//Devuelve la posicion de la minima lexicograficamente rotacion de un string
//O(N)
//Posiblemente en mi vida use esto 
int booth(string S){
    //"""Booth's algorithm."""
    S += S;  // Concatenate string to it self to avoid modular arithmetic
    int n = S.size();
    vector<int>f(n,-1);
    int k = 0;  // Least rotation of string found so far
    for (int j = 1; j<n; j++){
        char sj = S[j];
        int i = f[j - k - 1];
        while (i != -1 and sj != S[k + i + 1]){
            if (sj < S[k + i + 1])
                k = j - i - 1;
            i = f[i];
        }
        if (sj != S[k + i + 1]){
            if (sj < S[k])  
                k = j;
            f[j - k] = -1;
        }
        else{
            f[j - k] = i + 1;
        }   
	}
    return k;
}
